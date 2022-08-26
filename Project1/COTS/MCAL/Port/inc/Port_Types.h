/**********************************************************************************************************************
 * @file Port_Types.h
 * @brief This file is the header file for Port driver types  
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

#ifndef _PORT_TYPES_H
#define _PORT_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

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
    PORT_PA0 = 0,
    PORT_PA1,
    PORT_PA2,
    PORT_PA3,
    PORT_PA4,
    PORT_PA5,
    PORT_PA6,
    PORT_PA7,

    PORT_PB0 = 8,
    PORT_PB1,
    PORT_PB2,
    PORT_PB3,
    PORT_PB4,
    PORT_PB5,
    PORT_PB6,
    PORT_PB7,

    PORT_PC0 = 16,
    PORT_PC1,
    PORT_PC2,
    PORT_PC3,
    PORT_PC4,
    PORT_PC5,
    PORT_PC6,
    PORT_PC7,

    PORT_PD0 = 24,
    PORT_PD1,
    PORT_PD2,
    PORT_PD3,
    PORT_PD4,
    PORT_PD5,
    PORT_PD6,
    PORT_PD7,

    PORT_PE0 = 32,
    PORT_PE1,
    PORT_PE2,
    PORT_PE3,
    PORT_PE4,
    PORT_PE5,

    PORT_PF0 = 40,
    PORT_PF1,
    PORT_PF2,
    PORT_PF3,
    PORT_PF4,

}Port_PinType;

typedef enum
{
    PORT_DIR_INPUT,
    PORT_DIR_OUTPUT,

}Port_PinDirectionType;

typedef uint16 Port_PinModeType;

typedef enum
{
   	PORT_ATTACH_PULLUP,
	PORT_ATTACH_PULLDOWN,
	PORT_ATTACH_OPENDRAIN,
    PORT_ATTACH_DEFAULT,	 
}Port_PinInternalAttachType;

typedef enum
{
    PORT_PIN_2mA,
    PORT_PIN_4mA,
    PORT_PIN_8mA,
    PORT_PIN_NA,
}Port_PinOutputCurrentType;


typedef struct
{
    Port_PinType Pin;
    Port_PinModeType PinMode;
    Port_PinDirectionType PinDirection;
    Port_PinInternalAttachType PinAttach;
    Port_PinOutputCurrentType PinCurrent;
}Port_ConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* _PORT_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Port_Types.h
 *********************************************************************************************************************/
