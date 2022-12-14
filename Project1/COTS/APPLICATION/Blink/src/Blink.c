/**********************************************************************************************************************
 * @file Blink.c
 * @brief This file is the implementation of the blink application
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Blink.h"
#include "Led.h"
#include "Button.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

static Blink_Status status = Blink_On;
static uint32 onPeriod = 0;
static uint32 offPeriod = 0;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Blink_Cbk(void)
{
#if (1 == USE_SYSTICK)
	Systick_StopTimer();
#elif (1 == USE_GPT)
	Gpt_StopTimer(TIMER_CHANNEL_USED_LED);
#endif
	Blink_Update();
}

void Blink_Init(void)
{
	IntCtrl_init();
#if (1 == USE_GPT)
	Port_Init(Port_Configuration);
	Gpt_Init(Gpt_Configuration);
#elif (1 == USE_SYSTICK)
	Systick_StopTimer();
	Systick_EnableNotification();
#endif
	
	Button_Status sw1Status = Button_isPressed(DIO_CHANNEL_SW1);
	Button_Status sw2Status;
	Button_Status tmpStatus;
	
	while(STD_HIGH)
	{
		tmpStatus = Button_isPressed(DIO_CHANNEL_SW1);
		if(tmpStatus != sw1Status)
		{
			break;
		}
	}
	
	sw2Status = Button_isPressed(DIO_CHANNEL_SW2);
	
	while(STD_HIGH)
	{
		Gpt_StartTimer(TIMER_CHANNEL_USED_SW, WAIT_PERIOD);
		while(0 != Gpt_GetTimeRemaining(TIMER_CHANNEL_USED_SW));
		tmpStatus = Button_isPressed(DIO_CHANNEL_SW2);
		if(tmpStatus != sw2Status)
		{
			++onPeriod;
		}
		else
		{
			break;
		}
	}
	
	while(STD_HIGH)
	{
		tmpStatus = Button_isPressed(DIO_CHANNEL_SW1);
		if(tmpStatus != sw1Status)
		{
			break;
		}
	}
	
	sw2Status = Button_isPressed(DIO_CHANNEL_SW2);
	
	while(STD_HIGH)
	{
		Gpt_StartTimer(TIMER_CHANNEL_USED_SW, WAIT_PERIOD);
		while(0 != Gpt_GetTimeRemaining(TIMER_CHANNEL_USED_SW));
		tmpStatus = Button_isPressed(DIO_CHANNEL_SW2);
		if(tmpStatus != sw2Status)
		{
			++offPeriod;
		}
		else
		{
			break;
		}
	}
	
	while(STD_HIGH)
	{
		tmpStatus = Button_isPressed(DIO_CHANNEL_SW1);
		if(tmpStatus != sw1Status)
		{
			break;
		}
	}
	
	Blink_Update();
}

void Blink_Update(void)
{
	if(Blink_On == status)
	{
		status = Blink_Off;
		Led_Off(DIO_CHANNEL_USED);

#if (1 == USE_SYSTICK)
		Systick_StartTimer(offPeriod);
#elif (1 == USE_GPT)
		Gpt_StartTimer(TIMER_CHANNEL_USED_LED, offPeriod);
#endif
	}
	else if(Blink_Off == status)
	{
		status = Blink_On;
		Led_On(DIO_CHANNEL_USED);

#if (1 == USE_SYSTICK)
		Systick_StartTimer(onPeriod);
#elif (1 == USE_GPT)
		Gpt_StartTimer(TIMER_CHANNEL_USED_LED, onPeriod);
#endif
	}
}

/**********************************************************************************************************************
 *  END OF FILE: Blink.c
 *********************************************************************************************************************/
