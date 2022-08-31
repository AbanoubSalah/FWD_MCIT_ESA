/**********************************************************************************************************************
 * @file Blink.h
 * @brief This file is the interface of the blink application
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

#ifndef _BLINK_H
#define _BLINK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Blink_Cfg.h"
#include "IntCtrl.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "Systick.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define USE_SYSTICK								(1)
#define USE_GPT									(0)

#define DIO_CHANNEL_USED						(DIO_PA0)

#if (1 == USE_SYSTICK)
/* On/Off periods are in ticks and are dependent on the MCU clock and it is user provided
 * Note that Systick is a 24 bit counter so maximum achieved time is
 * (2^24) * (1/SystemClock) Seconds with 16777215 maximum tick.
 */
#define ON_PERIOD								(50000)
#define OFF_PERIOD								(5000)
#elif (1 == USE_GPT)
/* On/Off periods are in milli Seconds and it is user provided
 * Maximum time is also dependable on systemclock as follow
 * (2^16) * (1/SystemClock) Seconds for normal timers
 * (2^32) * (1/SystemClock) Seconds for wide timers
 */
#define TIMER_CHANNEL_USED						(Gpt_Channel_Timer0)
#define ON_PERIOD								(500)
#define OFF_PERIOD								(100)
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
	Blink_Off,
	Blink_On,
}Blink_Status;

 /**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
extern const Port_ConfigType Port_Configuration[];
extern const Gpt_ConfigType Gpt_Configuration[];
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * @brief Blink application call back function
 *
 * Stops the timer and calls Blink_Update function
 *
 * @param None
 *
 * @returns None
 *******************************************************************************/
void Blink_Cbk(void);

/******************************************************************************
 * @brief Initiates the blink application
 *
 * Initiates the interrupt controller 
 * Initiates port and gpio if needed
 * systick if needed
 * Calls link_Update function
 *
 * @param None
 *
 * @returns None
 *******************************************************************************/
void Blink_Init(void);

/******************************************************************************
 * @brief Update the blink application status
 *
 * Starts the timer and sets the blink LED status function
 *
 * @param None
 *
 * @returns None
 *******************************************************************************/
void Blink_Update(void);

#endif  /* _BLINK_H */

/**********************************************************************************************************************
 *  END OF FILE: Blink.h
 *********************************************************************************************************************/