/**********************************************************************************************************************
 * @file Tiva_TM4C123GH6PM.h
 * @brief This file contains board specific macros and definitions
 *
 * @author Abanoub Salah
 * @date August 15, 2022
 * *********************************************************************************************************************/


#ifndef _TIVA_TM4C123GH6PM_H_
#define _TIVA_TM4C123GH6PM_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
 
#define SYS_PERIPHERALS_BASE_ADDR       					(0xE000E000)
#define STCTRL_OFFSET   									(0x010)
#define STRELOAD_OFFSET   									(0x014)
#define STCURRENT_OFFSET   									(0x018)
#define INTCTRL_EN0_OFFSET   								(0x100)
#define INTCTRL_PRIx_OFFSET   								(0x400)
#define INTCTRL_PRIx_INTA_BIT  								(0x400)
#define APINT_OFFSET										(0xD0C)
#define APINT_PRIGROUP_BIT									(8)
#define SYSPRI1_OFFSET			   							(0xD18)
#define SYSPRI2_OFFSET			   							(0xD1C)
#define SYSPRI3_OFFSET			   							(0xD20)
#define SYSHNDCTRL											(0xD24)
#define WATCHDOG_BASE_ADDR_WDG1     						(0x40001000)
#define SRAM_BASE		      								(0x20000000)
#define SRAM_ALIAS_BASE		      							(0x22000000)
#define PERIPHERALS_BASE		          					(0x40000000)
#define WDT1_BASE		          							(0x40001000)
#define PERIPHERALS_ALIAS_BASE		      					(0x42000000)

/* Watchdog Definitions */
#define WDTLOAD_OFFSET										(0x000)
#define WDTCTL_OFFSET										(0x008)

/* System Control Definitions */
#define SYSCTRL_BASE_ADDRESS		             			(0x400FE000)

#define RESC_OFFSET                              		   	(0x05C)
#define RCC_OFFSET										   	(0x060)
#define GPIOHBCTL_OFFSET                          		  	(0x06C)
#define RCC2_OFFSET                                 	   	(0x070)
#define PLLSTAT_OFFSET                             		   	(0x168)
#define RCGCWD_OFFSET		                            	(0x600)
#define RCGCTIMER_OFFSET		                            (0x604)
#define RCGCGPIO_OFFSET                            		   	(0x608)
#define RCGCWTIMER_OFFSET                            		(0x65C)
#define PRGPIO_OFFSET                            		   	(0xA08)

/* GPIO Definitions */
#define GPIO_AFSEL_KEY										(0x4C4F434B)
#define GPIODATA_OFFSET                          		  	(0x000)
#define GPIODATA_ALL_PINS_MASK_OFFSET                       (0x3FC)
#define GPIODIR_OFFSET                					  	(0x400)
#define GPIOIS_OFFSET                 						(0x404)
#define GPIOIBE_OFFSET                						(0x408)
#define GPIOIVE_OFFSET                						(0x40C)
#define GPIOIM_OFFSET                 						(0x410)
#define GPIORIS_OFFSET                						(0x414)
#define GPIOMIS_OFFSET 					               		(0x418)
#define GPIOICR_OFFSET                						(0x41C)
#define GPIOAFSEL_OFFSET              						(0x420)
#define GPIODR2R_OFFSET                						(0x500)
#define GPIODR4R_OFFSET                						(0x504)
#define GPIODR8R_OFFSET                						(0x508)
#define GPIOODR_OFFSET                						(0x50C)
#define GPIOPUR_OFFSET                						(0x510)
#define GPIOPDR_OFFSET                						(0x514)
#define GPIOSLR_OFFSET                						(0x518)
#define GPIODEN_OFFSET                						(0x51C)
#define GPIOLOCK_OFFSET               						(0x520)
#define GPIOCR_OFFSET                					 	(0x524)
#define GPIOAMSEL_OFFSET             					 	(0x528)
#define GPIOPCTL_OFFSET             					  	(0x52C)
#define GPIOADCCTL_OFFSET            					 	(0x530)
#define GPIODMACTL_OFFSET            					 	(0x534)
#define PORTA_APB_BASE 										(0x40004000)
#define PORTB_APB_BASE 										(0x40005000)
#define PORTC_APB_BASE  									(0x40006000)
#define PORTD_APB_BASE  									(0x40007000)
#define PORTE_APB_BASE  									(0x40024000)
#define PORTF_APB_BASE  									(0x40025000)

/* GPTM Definitions */
#define TIMER0_REG_BASE 									(0x40030000)
#define TIMER1_REG_BASE										(0x40031000)
#define TIMER2_REG_BASE										(0x40032000)
#define TIMER3_REG_BASE										(0x40033000)
#define TIMER4_REG_BASE										(0x40034000)
#define TIMER5_REG_BASE										(0x40035000)
#define WTIMER0_REG_BASE 									(0x40036000)
#define WTIMER1_REG_BASE									(0x40037000)
#define WTIMER2_REG_BASE									(0x4004C000)
#define WTIMER3_REG_BASE									(0x4004D000)
#define WTIMER4_REG_BASE									(0x4004E000)
#define WTIMER5_REG_BASE									(0x4004F000)
#define GPTMCFG_OFFSET										(0x000)
#define GPTMTAMR_OFFSET										(0x004)
#define GPTMTAMR_TAMR_BIT									(0)
#define GPTMTAMR_TACDIR_BIT									(4)
#define GPTMCTL_OFFSET										(0x00C)
#define GPTMCTL_TAEN_BIT									(0)
#define GPTMIMR_OFFSET										(0x018)
#define GPTMIMR_TATOIM_Bit									(0)
#define GPTMICR_OFFSET										(0x024)
#define GPTMICR_TATOCINT_Bit								(0)
#define GPTMTAILR_OFFSET									(0x028)
#define GPTMTAPR_OFFSET										(0x038)
#define GPTMTAV_OFFSET										(0x050)
#define GPT_NUMBER_Timers_GROUP  							(6)

/* NVIC Definitions */
#define INTCTRL_APINT_KEY            						(0x05FA0000)
#define INTCTRL_PRILEVEL_XXX         						(0x4)
#define INTCTRL_PRILEVEL_XXY         						(0x5)
#define INTCTRL_PRILEVEL_XYY         						(0x6)
#define INTCTRL_PRILEVEL_YYY         						(0x7)
#define INTCTRL_REGISTER_SZ_BITS   							(32)
#define INTCTRL_REGISTER_SZ_BYTES  							(4)
#define INTCTRL_PRIx_FIRST_BIT								(5)

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

#endif /* _TIVA_TM4C123GH6PM_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Tiva_TM4C123GH6PM.h
 *********************************************************************************************************************/
