/**********************************************************************************************************************
 * @file Dio.c
 * @brief This file is the source file that implements DIO driver for TI microcontroller TM4C123GH6PM
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Dio.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

static const uint32 portBase[] = {
    PORTA_APB_BASE,
    PORTB_APB_BASE,
    PORTC_APB_BASE,
    PORTD_APB_BASE,
    PORTE_APB_BASE,
    PORTF_APB_BASE,
};

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

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelID)
{
	uint8 portNumber = ChannelID / 8;
    uint8 pinPosition = ChannelID % 8;
    Dio_LevelType pinLevel;

    return (Dio_LevelType)GET_BITBAND_ALIAS_ADDRESS((portBase[portNumber] + GPIODATA_ALL_PINS_MASK_OFFSET), pinPosition);
}

void Dio_WriteChannel(Dio_ChannelType ChannelID, Dio_LevelType Level)
{
	uint8 portNumber = ChannelID / 8;
    uint8 pinPosition = ChannelID % 8;

    GET_BITBAND_ALIAS_ADDRESS((portBase[portNumber] + GPIODATA_ALL_PINS_MASK_OFFSET), pinPosition) = Level;

	return ;
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortID)
{
    return (Dio_PortLevelType)GET_ADDRESS_BASE_OFFSET(portBase[PortID], GPIODATA_ALL_PINS_MASK_OFFSET);
}

void Dio_WritePort(Dio_PortType PortID, Dio_PortLevelType Level)
{
	GET_ADDRESS_BASE_OFFSET(portBase[PortID], GPIODATA_ALL_PINS_MASK_OFFSET) = Level;
	
	return ;
}

void Dio_FlipChannel(Dio_ChannelType ChannelID)
{
    uint8 portNumber = ChannelID / 8;
    uint8 pinPosition = ChannelID % 8;

	GET_BITBAND_ALIAS_ADDRESS((portBase[portNumber] + GPIODATA_ALL_PINS_MASK_OFFSET), pinPosition) = (GET_BITBAND_ALIAS_ADDRESS((portBase[portNumber] + GPIODATA_ALL_PINS_MASK_OFFSET), pinPosition) ^ STD_HIGH);
	
	return ;
}

/**********************************************************************************************************************
 *  END OF FILE: Dio.c
 *********************************************************************************************************************/
