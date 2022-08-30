 /**********************************************************************************************************************
 * @file Systick.h
 * @brief This file is the header file for the Systick driver
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/
 
#ifndef _SYSTICK_H
#define _SYSTICK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "Systick_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

extern uint32 SystemCoreClock;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
 
/******************************************************************************
* @brief This function gets the elapsed time of the specified GPT channel
*                                                                             
* Gets the elapsed time of the Systick.
* This function is synchronous and non re-entrant
*
* @param None
*                                        
* @returns Systick_ValueType			Elapsed time value in number of ticks
*******************************************************************************/
Systick_ValueType Systick_GetTimeElapsed(void);

/******************************************************************************
* @brief This function gets the remaining time of the specified GPT channel
*                                                                             
* Gets the remaining time of the Systick.
* This function is synchronous and non re-entrant
*
* @param None
*                                        
* @returns Systick_ValueType			Remaining time value in number of ticks
*******************************************************************************/
Systick_ValueType Systick_GetTimeRemaining(void);

/******************************************************************************
* @brief This function starts the Systick
*                                                                             
* Starts the Systick.
* This function is synchronous and non re-entrant
*
* @param Value							Target time in number of ticks
*                                        
* @returns None
*******************************************************************************/
void Systick_StartTimer(Systick_ValueType period);

/******************************************************************************
* @brief This function stops the timer of the Systick
*                                                                             
* Stops the selected timer channel and resets it.
* This function is synchronous and non re-entrant
*
* @param None
*                                        
* @returns None
*******************************************************************************/
void Systick_StopTimer(void);

/******************************************************************************
* @brief This function enables the interrupt notification of the Systick
*                                                                             
* Enables the interrupt notification of the Systick.
* This function is synchronous and non re-entrant
*
* @param None
*
* @returns None
*******************************************************************************/
void Systick_EnableNotification(void);

/******************************************************************************
* @brief This function disables the interrupt notification of the Systick
*                                                                             
* Disables the interrupt notification of the Systick.
* This function is synchronous and non re-entrant
*
* @param None
*
* @returns None
*******************************************************************************/
void Systick_DisableNotification(void);
 
#endif  /* _SYSTICK_H */

/**********************************************************************************************************************
 *  END OF FILE: Systick.h
 *********************************************************************************************************************/
