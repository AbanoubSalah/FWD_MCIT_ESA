/**********************************************************************************************************************
 * @file Port.c
 * @brief This file is the implementation for port driver for TI microcontroller TM4C123GH6PM
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Port.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

static const uint32 portBaseAddress[] = {
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

void Port_Init(const Port_ConfigType *ConfigPtr)
{
    uint8 portNumber;
    uint8 pinPosition;
    uint8 loopIndex;

    for(loopIndex = 0; loopIndex < PORT_PIN_CFG_SIZE; ++loopIndex)
    {
        portNumber = ConfigPtr[loopIndex].Pin / 8;
        pinPosition = ConfigPtr[loopIndex].Pin % 8;

		/* Enabling the clock to the port */
		if(!(GET_BITBAND_ALIAS_ADDRESS((SYSCTRL_BASE_ADDRESS + PRGPIO_OFFSET), portNumber)))
		{
			GET_BITBAND_ALIAS_ADDRESS((SYSCTRL_BASE_ADDRESS + RCGCGPIO_OFFSET), portNumber) = STD_HIGH;
			while(!(GET_BITBAND_ALIAS_ADDRESS((SYSCTRL_BASE_ADDRESS + PRGPIO_OFFSET), portNumber)));
		}
		
		/* Unlocking D7 or F0 if needed */
		if((ConfigPtr[loopIndex].Pin== PORT_PD7) || (ConfigPtr[loopIndex].Pin== PORT_PF0))
		{
			GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOAFSEL_OFFSET) = GPIO_AFSEL_KEY;
			GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOICR_OFFSET), pinPosition) = STD_HIGH;
		}

		/* Configuring port mode */
		if(PORT_PIN_MODE_DIO == ConfigPtr[loopIndex].PinMode)
		{
			GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOAFSEL_OFFSET), pinPosition) = STD_LOW;
			GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOAMSEL_OFFSET), pinPosition) = STD_LOW;
			GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) &= ~((uint32)0x0000000F << (pinPosition * 4));
			GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODEN_OFFSET), pinPosition) = STD_HIGH;
		}
		else
		{
			GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOAFSEL_OFFSET), pinPosition) = STD_HIGH;
			GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODEN_OFFSET), pinPosition) = STD_HIGH;
			
			switch(ConfigPtr[loopIndex].PinMode)
			{
				case PORT_PIN_MODE_ADC:
					GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODEN_OFFSET), pinPosition) = STD_LOW;
					GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOAMSEL_OFFSET), pinPosition) = STD_HIGH;
					break;
					
				case PORT_PIN_MODE_UART:
					GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOAMSEL_OFFSET), pinPosition) = STD_LOW;
					
					if((PORT_PC4 == ConfigPtr[loopIndex].Pin) || (PORT_PC5 == ConfigPtr[loopIndex].Pin))
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000002 << (pinPosition * 4));
					}
					else
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000001 << (pinPosition * 4));
					}
					break;
					
				case PORT_PIN_MODE_USB:
					GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000008 << (pinPosition * 4));
					break;
					
				case PORT_PIN_MODE_I2C:
					GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOODR_OFFSET), pinPosition) = STD_HIGH;
					GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000003 << (pinPosition * 4));
					break;
					
				case PORT_PIN_MODE_CAN:
					if((PORT_PF0 == ConfigPtr[loopIndex].Pin) || (PORT_PF3 == ConfigPtr[loopIndex].Pin))
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000003 << (pinPosition * 4));
					}
					else
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000008 << (pinPosition * 4));
					}
					break;
					
				case PORT_PIN_MODE_PWM:
					if((PORT_PB4 == ConfigPtr[loopIndex].Pin) || (PORT_PB7 == ConfigPtr[loopIndex].Pin) || (PORT_PC4 == ConfigPtr[loopIndex].Pin) || (PORT_PC5 == ConfigPtr[loopIndex].Pin) || (PORT_PD0 == ConfigPtr[loopIndex].Pin) || (PORT_PD1 == ConfigPtr[loopIndex].Pin) || (PORT_PE4 == ConfigPtr[loopIndex].Pin) || (PORT_PE5 == ConfigPtr[loopIndex].Pin))
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000004 << (pinPosition * 4));
					}
					else
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000005 << (pinPosition * 4));
					}
					break;
					
				case PORT_PIN_MODE_SSI:					
					if((PORT_PD0 == ConfigPtr[loopIndex].Pin) || (PORT_PD1 == ConfigPtr[loopIndex].Pin) || (PORT_PD2 == ConfigPtr[loopIndex].Pin) || (PORT_PD3 == ConfigPtr[loopIndex].Pin))
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000001 << (pinPosition * 4));
					}
					else
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000002 << (pinPosition * 4));
					}
					break;
					
				case PORT_PIN_MODE_QEI:
					GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000006 << (pinPosition * 4));
					break;
					
				case PORT_PIN_MODE_GPT:
					GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000007 << (pinPosition * 4));			
					break;
					
				case PORT_PIN_MODE_NMI:
					GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000008 << (pinPosition * 4));
					break;
					
				case PORT_PIN_MODE_ANALOG_COMP:
					if((PORT_PC4 == ConfigPtr[loopIndex].Pin) || (PORT_PC5 == ConfigPtr[loopIndex].Pin) || (PORT_PC6 == ConfigPtr[loopIndex].Pin) || (PORT_PC7 == ConfigPtr[loopIndex].Pin))
					{
						GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOAMSEL_OFFSET), pinPosition) = STD_HIGH;
						GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODEN_OFFSET), pinPosition) = STD_LOW;
					}
					else
					{
						GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x00000009 << (pinPosition * 4));
					}
					break;
					
				case PORT_PIN_MODE_CORE:
					GET_ADDRESS_BASE_OFFSET(portBaseAddress[portNumber], GPIOPCTL_OFFSET) |= ((uint32)0x0000000E << (pinPosition * 4));
					break;
					
				default:
					break;
			}
		}
		
        /* Configuring pin direction */
        if(PORT_DIR_INPUT == ConfigPtr[loopIndex].PinDirection)
        {
        	GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODIR_OFFSET), pinPosition) = STD_HIGH;
        }
        else if(PORT_DIR_OUTPUT == ConfigPtr[loopIndex].PinDirection)
		{
        	GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber]+ GPIODIR_OFFSET), pinPosition) = STD_LOW;
		}
		
        /* Setting attach mode */
        switch (ConfigPtr[loopIndex].PinAttach)
		{
			case PORT_ATTACH_PULLUP:
				GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOPUR_OFFSET), pinPosition) = STD_HIGH;
				break;
				
			case PORT_ATTACH_PULLDOWN:
				GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOPDR_OFFSET), pinPosition) = STD_HIGH;
				break;
				
			case PORT_ATTACH_OPENDRAIN:
				GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIOODR_OFFSET), pinPosition) = STD_HIGH;
				break;
			
			case PORT_ATTACH_DEFAULT:
			default:
				break;
		}
		
        /* Setting driver current */
        switch (ConfigPtr[loopIndex].PinCurrent)
		{
			case PORT_PIN_2mA:
				GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODR2R_OFFSET), pinPosition) = STD_HIGH;
				break;
			case PORT_PIN_4mA:
				GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODR4R_OFFSET), pinPosition) = STD_HIGH;
				break;
			case PORT_PIN_8mA:
				GET_BITBAND_ALIAS_ADDRESS((portBaseAddress[portNumber] + GPIODR8R_OFFSET), pinPosition) = STD_HIGH;
				break;
			case PORT_PIN_NA:
			default:
				break;
		}
    }
}

/**********************************************************************************************************************
 *  END OF FILE: Port.c
 *********************************************************************************************************************/
