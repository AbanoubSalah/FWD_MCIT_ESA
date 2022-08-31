/**********************************************************************************************************************
 * @file Dio.h
 * @brief This file is the header file for DIO driver
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

#ifndef _DIO_H
#define _DIO_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Dio_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
 * @brief Read a DIO pin
 *
 * Reads a DIO pin. This function is synchronous and re-entrant
 *
 * @param ChannelID			The ID of the pin to be read
 *
 * @returns DIO_LevelType either  DIO_LEVEL_LOW /
 *                                DIO_LEVEL_HIGH                                  
 *******************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelID);

/******************************************************************************
 * @brief Writes to a DIO pin
 *
 * Writes to a DIO pin. This function is synchronous and re-entrant
 *
 * @param ChannelID			The channel ID to write to it
 * @param Level				The pin level to be written to
 *
 * @returns None
 *******************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelID, Dio_LevelType Level);

/******************************************************************************
 * @brief Read an entire port
 *
 * Reads a DIO port. This function is synchronous and re-entrant
 *
 * @param PortID				The ID of the port to be read
 *
 * @returns DIO port level
 *******************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortID);

/******************************************************************************
 * @brief Writes to an entire port                                  
 *
 * Writes to a DIO port. This function is synchronous and re-entrant
 *                                                                             
 * @param PortId			The ID of the port to be written to
 * @param Level				The port level to be written to
 *
 * @returns None
 *******************************************************************************/
void Dio_WritePort(Dio_PortType PortID, Dio_PortLevelType Level);

/******************************************************************************
 * @brief Flips the value of a pin
 *
 * Flips the value of a specific pin. This function is synchronous and re-entrant
 *
 * @param ChannelId   the id of the port to be flipped                
 *
 * @returns None
 *******************************************************************************/
void Dio_FlipChannel(Dio_ChannelType ChannelID);

#endif  /* _DIO_H */

/**********************************************************************************************************************
 *  END OF FILE: Dio.h
 *********************************************************************************************************************/
