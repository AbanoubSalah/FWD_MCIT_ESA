 /**********************************************************************************************************************
 * @file IntCtrl_Types.h
 * @brief This file is the header file for IntCtrl driver types
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/
 
#ifndef _INTCTRL_TYPES_H
#define _INTCTRL_TYPES_H

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

/* Enum for system exceptions and interrupts (programmable only)*/
typedef enum
{
	INTCTRL_Reset = -15,
	INTCTRL_NMI = -14,
	INTCTRL_HardFault,
	INTCTRL_MemManage,
	INTCTRL_BusFault,
	INTCTRL_UsageFault,
	INTCTRL_SVC = -5,
	INTCTRL_DebugMon,
	INTCTRL_PendSV = -2,
	INTCTRL_SysTick,
	INTCTRL_GPIOA,
	INTCTRL_GPIOB,
	INTCTRL_GPIOC,
	INTCTRL_GPIOD,
	INTCTRL_GPIOE,
	INTCTRL_UART0,
	INTCTRL_UART1,
	INTCTRL_SSI0,
	INTCTRL_I2C0,
	INTCTRL_PMW0_FAULT,
	INTCTRL_PWM0_0,
	INTCTRL_PWM0_1,
	INTCTRL_PWM0_2,
	INTCTRL_QEI0,
	INTCTRL_ADC0SS0,
	INTCTRL_ADC0SS1,
	INTCTRL_ADC0SS2,
	INTCTRL_ADC0SS3,
	INTCTRL_WDT0,
	INTCTRL_TIMER0A,
	INTCTRL_TIMER0B,
	INTCTRL_TIMER1A,
	INTCTRL_TIMER1B,
	INTCTRL_TIMER2A,
	INTCTRL_TIMER2B,
	INTCTRL_COMP0,
	INTCTRL_COMP1,
	INTCTRL_COMP2,
	INTCTRL_SYSCTL,
	INTCTRL_FLASH,
	INTCTRL_GPIOF,
	INTCTRL_GPIOG,
	INTCTRL_GPIOH,
	INTCTRL_UART2,
	INTCTRL_SSI1,
	INTCTRL_TIMER3A,
	INTCTRL_TIMER3B,
	INTCTRL_I2C1,
	INTCTRL_QEI1,
	INTCTRL_CAN0,
	INTCTRL_CAN1,
	INTCTRL_CAN2,
	INTCTRL_HIB = 43,
	INTCTRL_USB0,
	INTCTRL_PWM0_3,
	INTCTRL_UDMA,
	INTCTRL_UDMAERR,
	INTCTRL_ADC1SS0,
	INTCTRL_ADC1SS1,
	INTCTRL_ADC1SS2,
	INTCTRL_ADC1SS3,
	INTCTRL_GPIOJ = 54,
	INTCTRL_GPIOK,
	INTCTRL_GPIOL,
	INTCTRL_SSI2,
	INTCTRL_SSI3,
	INTCTRL_UART3,
	INTCTRL_UART4,
	INTCTRL_UART5,
	INTCTRL_UART6,
	INTCTRL_UART7,
	INTCTRL_I2C2 = 68,
	INTCTRL_I2C3,
	INTCTRL_TIMER4A,
	INTCTRL_TIMER4B,
	INTCTRL_TIMER5A = 92,
	INTCTRL_TIMER5B,
	INTCTRL_WTIMER0A,
	INTCTRL_WTIMER0B,
	INTCTRL_WTIMER1A,
	INTCTRL_WTIMER1B,
	INTCTRL_WTIMER2A,
	INTCTRL_WTIMER2B,
	INTCTRL_WTIMER3A,
	INTCTRL_WTIMER3B,
	INTCTRL_WTIMER4A,
	INTCTRL_WTIMER4B,
	INTCTRL_WTIMER5A,
	INTCTRL_WTIMER5B,
	INTCTRL_FPU,
	INTCTRL_I2C4 = 109,
	INTCTRL_I2C5,
	INTCTRL_GPIOM,
	INTCTRL_GPION,
	INTCTRL_QEI2,
	INTCTRL_GPIOP0 = 116,
	INTCTRL_GPIOP1,
	INTCTRL_GPIOP2,
	INTCTRL_GPIOP3,
	INTCTRL_GPIOP4,
	INTCTRL_GPIOP5,
	INTCTRL_GPIOP6,
	INTCTRL_GPIOP7,
	INTCTRL_GPIOQ0,
	INTCTRL_GPIOQ1,
	INTCTRL_GPIOQ2,
	INTCTRL_GPIOQ3,
	INTCTRL_GPIOQ4,
	INTCTRL_GPIOQ5,
	INTCTRL_GPIOQ6,
	INTCTRL_GPIOQ7,
	INTCTRL_GPIOR,
	INTCTRL_GPIOS,
	INTCTRL_PMW1_0,
	INTCTRL_PWM1_1,
	INTCTRL_PWM1_2,
	INTCTRL_PWM1_3,
	INTCTRL_PWM1_FAULT,
}IntCtrl_InterruptType;

typedef struct 
{
    IntCtrl_InterruptType vectorNumber;
    uint8 exceptionGroup;
    uint8 exceptionSubGroup;
}IntCtrl_InterruptCfgType;

typedef struct 
{
    IntCtrl_InterruptType exceptionNumber;
    uint8 exceptionGroup;
    uint8 exceptionSubGroup;
}IntCtrl_ExceptionCfgType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
#endif  /* _INTCTRL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Types.h
 *********************************************************************************************************************/
