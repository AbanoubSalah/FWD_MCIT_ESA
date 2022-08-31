 /**********************************************************************************************************************
 * @file Gpt.h
 * @brief This file is the header file for Port driver
 *
 * @author Abanoub Salah
 * @date August 20, 2022
 * *********************************************************************************************************************/

#ifndef _GPT_H
#define _GPT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "Gpt_Types.h"
#include "Gpt_Cfg.h"

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
 * @brief This function initialize the specified GPT module
 *                                                                             
 * Initialize the specified GPT module. This function is synchronous and non re-entrant
 *
 * @param ConfigPtr Pointer to the GPT config type structure
 *                                        
 * @returns None
 *******************************************************************************/
void Gpt_Init(const Gpt_ConfigType *ConfigPtr);

/******************************************************************************
 * @brief This function gets the elapsed time of the specified GPT channel
 *                                                                             
 * Gets the elapsed time of the specified GPT channel. This function is synchronous and re-entrant
 *
 * @param Channel						Numeric ID of the GPT channel
 *                                        
 * @returns Gpt_ValueType		Elapsed time value in number of ticks
 *******************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);

/******************************************************************************
 * @brief This function gets the remaining time of the specified GPT channel
 *                                                                             
 * Gets the remaining time of the specified GPT channel. This function is synchronous and re-entrant
 *
 * @param Channel						Numeric ID of the GPT channel
 *                                        
 * @returns Gpt_ValueType		Remaining time value in number of ticks
 *******************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);

/******************************************************************************
 * @brief This function starts the timer of the specified GPT channel with a specified time
 *                                                                            
 * Starts the selected timer channel with a defined target time.
 * This function is synchronous and re-entrant
 *
 * @param Channel						Numeric ID of the GPT channel
 * @param Value							Target time in number of ticks
 *                                        
 * @returns None
 *******************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);

/******************************************************************************
 * @brief This function stops the timer of the specified GPT channel with a specified time
 *                                                                             
 * Stops the selected timer channel and resets it.
 * This function is synchronous and re-entrant
 *
 * @param Channel						Numeric ID of the GPT channel
 *                                        
 * @returns None
 *******************************************************************************/
void Gpt_StopTimer(Gpt_ChannelType Channel);
 
/******************************************************************************
 * @brief This function enables the interrupt notification of specified GPT channel
 *
 * Enables the interrupt notification of specified GPT channel.
 * This function is synchronous and re-entrant
 *
 * @param Channel						Numeric ID of the GPT channel
 *
 * @returns None
 *******************************************************************************/
void Gpt_EnableNotification(Gpt_ChannelType Channel);

/******************************************************************************
 * @brief This function disables the interrupt notification of specified GPT channel
 *
 * Disables the interrupt notification of specified GPT channel.
 * This function is synchronous and re-entrant
 *
 * @param Channel						Numeric ID of the GPT channel
 *
 * @returns None
 *******************************************************************************/
void Gpt_DisableNotification(Gpt_ChannelType Channel);

/******************************************************************************
 * @brief This function gets the current predef timer value
 *                                                                             
 * Gets the current predef GPT timer value passed by PredefTimer
 * This function is synchronous and re-entrant
 *
 * @param PredefTimer								GPT Predef Timer
 * @param TimeValuePtr								Pointer to destination for value storage
 *
 * @returns Std_ReturnType						Standad return type E_OK
 *
 *******************************************************************************/
Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32 *TimeValuePtr);


#endif  /* _GPT_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpt.h
 *********************************************************************************************************************/
