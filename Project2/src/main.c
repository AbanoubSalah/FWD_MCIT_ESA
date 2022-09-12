/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"

/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE		( ( unsigned long ) 115200 )

#define TASK1_PERIOD 				50
#define TASK2_PERIOD 				50
#define TASK3_PERIOD 				100
#define TASK4_PERIOD 				20
#define TASK5_PERIOD 				10
#define TASK6_PERIOD 				100
#define TASK1_PRIORITY 				2
#define TASK2_PRIORITY 				2
#define TASK3_PRIORITY 				1
#define TASK4_PRIORITY 				3
#define TASK5_PRIORITY 				4
#define TASK6_PRIORITY 				1
#define QUEUE_SEND_TIMEOUT			0
#define QUEUE_RECIEVE_TIMEOUT		0

#define TASKS_PORTNAME				PORT_0
#define DEBUG_PORTNAME				PORT_0
#define TASK1_PINNUM				PIN0
#define TASK2_PINNUM				PIN1

/* Task Handlers Defs. */
static TaskHandle_t task1_handle;
static TaskHandle_t task2_handle;
static TaskHandle_t task3_handle;
static TaskHandle_t task4_handle;
static TaskHandle_t task5_handle;
static TaskHandle_t task6_handle;

typedef struct
{
	int16_t dataLength;
	int8_t *pData;
} xConsumerMessage;

#if configUSE_TRACE_FACILITY == 1
static xConsumerMessage statsMessage;
static char pcBuffer[STATS_BUFFER_LENGTH];
#endif

static QueueHandle_t xConsumerQueue;

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void task6(void);

#if configUSE_EDF_SCHEDULER == 1
extern BaseType_t xTaskPeriodicCreate( TaskFunction_t pxTaskCode,
									   const char * const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									   const configSTACK_DEPTH_TYPE usStackDepth,
									   void * const pvParameters,
									   UBaseType_t uxPriority,
									   TaskHandle_t * const pxCreatedTask,
									   TickType_t period );
#endif

/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/


/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
	
	/* Initialize Pins State */
	GPIO_write(DEBUG_PORTNAME, TICK_PINNUM, PIN_IS_LOW);
	GPIO_write(DEBUG_PORTNAME, IDLE_PINNUM, PIN_IS_LOW);
	GPIO_write(DEBUG_PORTNAME, T1DBG_PINNUM, PIN_IS_LOW);
	GPIO_write(DEBUG_PORTNAME, T2DBG_PINNUM, PIN_IS_LOW);
	GPIO_write(DEBUG_PORTNAME, T3DBG_PINNUM, PIN_IS_LOW);
	GPIO_write(DEBUG_PORTNAME, T4DBG_PINNUM, PIN_IS_LOW);
	GPIO_write(DEBUG_PORTNAME, T5DBG_PINNUM, PIN_IS_LOW);
	GPIO_write(DEBUG_PORTNAME, T6DBG_PINNUM, PIN_IS_LOW);
	
	/* Create a queue capable of containing 50 xConsumerMessage */
    xConsumerQueue = xQueueCreate( 50, sizeof( xConsumerMessage ) );

    /* Create Tasks here */
	
	#if configUSE_EDF_SCHEDULER == 1
	xTaskPeriodicCreate((TaskFunction_t) task1, ( const char * ) "Button_1_Monitor", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, (xTaskHandle *) &task1_handle, TASK1_PERIOD);
	xTaskPeriodicCreate((TaskFunction_t) task2, ( const char * ) "Button_2_Monitor", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, (xTaskHandle *) &task2_handle, TASK2_PERIOD);
	xTaskPeriodicCreate((TaskFunction_t) task3, ( const char * ) "Periodic_Transmitter", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, (xTaskHandle *) &task3_handle, TASK3_PERIOD);
	xTaskPeriodicCreate((TaskFunction_t) task4, ( const char * ) "Uart_Receiver", configMINIMAL_STACK_SIZE, NULL, TASK4_PRIORITY, (xTaskHandle *) &task4_handle, TASK4_PERIOD);
	xTaskPeriodicCreate((TaskFunction_t) task5, ( const char * ) "Load_1_Simulation", configMINIMAL_STACK_SIZE, NULL, TASK5_PRIORITY, (xTaskHandle *) &task5_handle, TASK5_PERIOD);
	xTaskPeriodicCreate((TaskFunction_t) task6, ( const char * ) "Load_2_Simulation", configMINIMAL_STACK_SIZE, NULL, TASK6_PRIORITY, (xTaskHandle *) &task6_handle, TASK6_PERIOD);
	
	#else
	xTaskCreate((TaskFunction_t) task1, ( const char * ) "Button_1_Monitor", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, (xTaskHandle *) &task1_handle);
	xTaskCreate((TaskFunction_t) task2, ( const char * ) "Button_2_Monitor", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, (xTaskHandle *) &task2_handle);
	xTaskCreate((TaskFunction_t) task3, ( const char * ) "Periodic_Transmitter", configMINIMAL_STACK_SIZE, NULL, TASK3_PRIORITY, (xTaskHandle *) &task3_handle);
	xTaskCreate((TaskFunction_t) task4, ( const char * ) "Uart_Receiver", configMINIMAL_STACK_SIZE, NULL, TASK4_PRIORITY, (xTaskHandle *) &task4_handle);
	xTaskCreate((TaskFunction_t) task5, ( const char * ) "Load_1_Simulation", configMINIMAL_STACK_SIZE, NULL, TASK5_PRIORITY, (xTaskHandle *) &task5_handle);
	xTaskCreate((TaskFunction_t) task6, ( const char * ) "Load_2_Simulation", configMINIMAL_STACK_SIZE, NULL, TASK6_PRIORITY, (xTaskHandle *) &task6_handle);
	
	#endif
	
	vTaskSetApplicationTaskTag(task1_handle, (TaskHookFunction_t)TASK1_TAG);
	vTaskSetApplicationTaskTag(task2_handle, (TaskHookFunction_t)TASK2_TAG);
	vTaskSetApplicationTaskTag(task3_handle, (TaskHookFunction_t)TASK3_TAG);
	vTaskSetApplicationTaskTag(task4_handle, (TaskHookFunction_t)TASK4_TAG);
	vTaskSetApplicationTaskTag(task5_handle, (TaskHookFunction_t)TASK5_TAG);
	vTaskSetApplicationTaskTag(task6_handle, (TaskHookFunction_t)TASK6_TAG);	

	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ; ; );
}
/*-----------------------------------------------------------*/

void task1(void)
{
	TickType_t xLastWakeTimeTask1 = 0;
	const TickType_t xFrequencyTask1 = TASK1_PERIOD;
	pinState_t button1CurrentState, button1State = GPIO_read( TASKS_PORTNAME, TASK1_PINNUM);
	int8_t fallingEdgeMessage[] = "\n\rTask1: Falling Edge Detected.\n\r";
	int8_t risingEdgeMessage[] = "\n\rTask1: Rising Edge Detected.\n\r";
	xConsumerMessage task1Message;
	
	for( ; ; )
	{
		button1CurrentState = GPIO_read( TASKS_PORTNAME, TASK1_PINNUM);		
		
		if( button1CurrentState != button1State )
		{
			if( button1State == PIN_IS_HIGH )
			{
				/* Transitioning from high to low makes a falling edge */
				task1Message.dataLength = sizeof( fallingEdgeMessage);
				task1Message.pData = fallingEdgeMessage;
			}
			else
			{
				/* Transitioning from low to high makes a rising edge */
				task1Message.dataLength = sizeof( risingEdgeMessage );
				task1Message.pData = risingEdgeMessage;
			}
			
			button1State = button1CurrentState;
			xQueueSend( xConsumerQueue, ( void * ) &( task1Message ), ( TickType_t ) QUEUE_SEND_TIMEOUT );
		}
		
		vTaskDelayUntil( &( xLastWakeTimeTask1 ), xFrequencyTask1 );
	}
}

void task2(void)
{
	TickType_t xLastWakeTimeTask2 = 0;
	const TickType_t xFrequencyTask2 = TASK2_PERIOD;
	pinState_t button2CurrentState, button2State = GPIO_read( TASKS_PORTNAME, TASK2_PINNUM);
	int8_t fallingEdgeMessage[] = "\n\rTask2: Falling Edge Detected.\n\r";
	int8_t risingEdgeMessage[] = "\n\rTask2: Rising Edge Detected.\n\r";
	xConsumerMessage task2Message;
	
	for( ; ; )
	{
		button2CurrentState = GPIO_read( TASKS_PORTNAME, TASK2_PINNUM);
		
		if( button2CurrentState != button2State )
		{
			if( button2State == PIN_IS_HIGH )
			{
				/* Transitioning from high to low makes a falling edge */
				task2Message.dataLength = sizeof( fallingEdgeMessage);
				task2Message.pData = fallingEdgeMessage;
			}
			else
			{
				/* Transitioning from low to high makes a rising edge */
				task2Message.dataLength = sizeof( risingEdgeMessage );
				task2Message.pData = risingEdgeMessage;
			}
			
			button2State = button2CurrentState;
			xQueueSend( xConsumerQueue, ( void * ) &( task2Message ), ( TickType_t ) QUEUE_SEND_TIMEOUT );
		}

		vTaskDelayUntil( &( xLastWakeTimeTask2 ), xFrequencyTask2 );
	}
}

void task3(void)
{
	TickType_t xLastWakeTimeTask3 = 0;
	const TickType_t xFrequencyTask3 = TASK3_PERIOD;
	xConsumerMessage task3Message;
	int8_t periodicString[] = "\n\rTask3: Periodic message.\n\r";
	
	task3Message.dataLength = sizeof( periodicString );
	task3Message.pData = periodicString;
	
	for( ; ; )
	{
		xQueueSend( xConsumerQueue, ( void * ) &( task3Message ), ( TickType_t ) QUEUE_SEND_TIMEOUT );
		
		vTaskDelayUntil( &( xLastWakeTimeTask3 ), xFrequencyTask3 );
	}
}

void task4(void)
{
	TickType_t xLastWakeTimeTask4 = 0;
	const TickType_t xFrequencyTask4 = TASK4_PERIOD;
	xConsumerMessage xRxedMessage;

	for( ; ; )
	{
		if( xQueueReceive( xConsumerQueue, &( xRxedMessage ), ( TickType_t ) QUEUE_RECIEVE_TIMEOUT ) == pdPASS )
		{
			vSerialPutString( xRxedMessage.pData, xRxedMessage.dataLength );
		}

		vTaskDelayUntil( &( xLastWakeTimeTask4 ), xFrequencyTask4 );
	}
}

void task5(void)
{
	TickType_t xLastWakeTimeTask5 = 0;
	const TickType_t xFrequencyTask5 = TASK5_PERIOD;
	volatile uint32_t idx;
	
	for( ; ; )
	{
		/* Simulating a load excution time of 5 ms for task5 */
		for(idx = 0; idx <0x48B6; ++idx);

		vTaskDelayUntil( &( xLastWakeTimeTask5 ), xFrequencyTask5 );
	}
}

void task6(void)
{
	TickType_t xLastWakeTimeTask6 = 0;
	const TickType_t xFrequencyTask6 = TASK6_PERIOD;
	volatile uint32_t idx;
	
	#if configUSE_TRACE_FACILITY == 1
	statsMessage.pData = (int8_t *) pcBuffer;
	statsMessage.dataLength = STATS_BUFFER_LENGTH;
	#endif
	
	for( ; ; )
	{
		/* Simulating a load excution time of 12 ms for task6 */
		for(idx = 0; idx < 0xAE9E; ++idx);
		
		/* Note that this code will increase task6 excusion time */
		#if configUSE_TRACE_FACILITY == 1
		vTaskGetRunTimeStats( pcBuffer );
		xQueueSend( xConsumerQueue, ( void * ) &( statsMessage ), ( TickType_t ) QUEUE_SEND_TIMEOUT );
		#endif

		vTaskDelayUntil( &( xLastWakeTimeTask6 ), xFrequencyTask6 );
	}
}

/* Tick Hook Function */
void vApplicationTickHook(void)
{
	GPIO_write(DEBUG_PORTNAME, TICK_PINNUM, PIN_IS_HIGH);
	GPIO_write(DEBUG_PORTNAME, TICK_PINNUM, PIN_IS_LOW);
}

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/
