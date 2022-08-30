/**********************************************************************************************************************
 * @file Systick_Cfg.h
 * @brief This file is the header file for systick configuration for TI microcontroller TM4C123GH6PM
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/
 
 
#ifndef _SYSTICK_CFG_H
#define _SYSTICK_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define USE_SYSTICK							(1)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#if (1 == USE_SYSTICK)
void SysTick_Handler(void);
extern void Systick_Cbk(void);
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
#endif  /* _SYSTICK_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Systick_Cfg.h
 *********************************************************************************************************************/