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
#define DIO_CHANNEL_SW1							(DIO_PA1)
#define DIO_CHANNEL_SW2							(DIO_PA2)

#define WAIT_PERIOD								(20)
#define TIMER_CHANNEL_USED_SW					(Gpt_Channel_Timer1)

#if (1 == USE_SYSTICK)
/* On/Off periods are in ticks and are dependent on the MCU clock and it is user provided
 * Note that Systick is a 24 bit counter so maximum achieved time is
 * 16777215 * (1/SystemClock) Seconds with 16777215 maximum tick.
 */
#define ON_PERIOD								(50000)
#define OFF_PERIOD								(5000)
#elif (1 == USE_GPT)
/* On/Off periods are in milli Seconds and it is user provided */
#define TIMER_CHANNEL_USED_LED					(Gpt_Channel_Timer0)
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

void Blink_Cbk(void);
void Blink_Init(void);
void Blink_Update(void);

#endif  /* _BLINK_H */

/**********************************************************************************************************************
 *  END OF FILE: Blink.h
 *********************************************************************************************************************/