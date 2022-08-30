/**********************************************************************************************************************
 * @file Systick.c
 * @brief This file is the implementation for SYSTICK driver for TI microcontroller TM4C123GH6PM
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Systick.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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

Systick_ValueType Systick_GetTimeElapsed(void)
{
	Systick_ValueType value = ((GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, STRELOAD_OFFSET)) - (GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, STCURRENT_OFFSET)) / (SystemCoreClock / 1000));
	return value;
}

Systick_ValueType Systick_GetTimeRemaining(void)
{
	Systick_ValueType value = (GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, STCURRENT_OFFSET) / (SystemCoreClock / 1000));
	return value;
}

void Systick_StartTimer(Systick_ValueType period)
{
	/* Check period within max value of 24 bit counter */
	if((0 >= period) && (16777216 < period))
	{
		while(STD_ON);
	}

	GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, STRELOAD_OFFSET) = period;

	GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, STCTRL_OFFSET) |= ((1 << BIT_2) | (1 << BIT_0));
}

void Systick_StopTimer(void)
{
	GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, STCURRENT_OFFSET) = 0;
	CLEAR_BIT((SYS_PERIPHERALS_BASE_ADDR + STCTRL_OFFSET), BIT_0);
}

void Systick_EnableNotification(void)
{
    SET_BIT(GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, STCTRL_OFFSET), BIT_1);
}

void Systick_DisableNotification(void)
{
    CLEAR_BIT((SYS_PERIPHERALS_BASE_ADDR + STCTRL_OFFSET), BIT_1);
}

/**********************************************************************************************************************
 *  END OF FILE: Systick.c
 *********************************************************************************************************************/
