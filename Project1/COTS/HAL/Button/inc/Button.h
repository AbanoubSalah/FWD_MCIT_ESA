/**********************************************************************************************************************
 * @file Button.h
 * @brief This file is the interface of the Button HAL driver
 *
 * @author Abanoub Salah
 * @date September 22, 2022
 * *********************************************************************************************************************/

#ifndef _BUTTON_H
#define _BUTTON_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Button_Cfg.h"
#include "Std_Types.h"
#include "Dio.h"

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
	Button_Off,
	Button_On,
}Button_Status;

 /**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/******************************************************************************
 * @brief Checks if the Button is pressed
 *
 * Checks if the Button is pressed
 *
 * @param channel						Specified channel number
 *
 * @returns Button_Status				Button status	Button_OFF
 *														Button_ON
 *******************************************************************************/
Button_Status Button_isPressed(Dio_ChannelType channel);

#endif  /* _BUTTON_H */

/**********************************************************************************************************************
 *  END OF FILE: Button.h
 *********************************************************************************************************************/