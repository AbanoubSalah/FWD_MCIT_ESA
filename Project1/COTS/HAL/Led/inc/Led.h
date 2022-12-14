/**********************************************************************************************************************
 * @file Led.h
 * @brief This file is the interface of the LED HAL driver
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

#ifndef _LED_H
#define _LED_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Led_Cfg.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
	Led_NOT_OK,
	Led_OK,
}Led_Status;

 /**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * @brief Turns on the LED
 *
 * Turns on the LED
 *
 * @param channel						Specified channel number
 *
 * @returns Led_Status					Led status Led_OK
 *												   Led_NOT_OK
 *******************************************************************************/
Led_Status Led_On(uint32 channel);

/******************************************************************************
 * @brief Turns off the LED
 *
 * Turns off the LED
 *
 * @param channel						Specified channel number
 *
 * @returns Led_Status					Led status Led_OK
 *												   Led_NOT_OK
 *******************************************************************************/
Led_Status Led_Off(uint32 channel);

#endif  /* _LED_H */

/**********************************************************************************************************************
 *  END OF FILE: Led.h
 *********************************************************************************************************************/