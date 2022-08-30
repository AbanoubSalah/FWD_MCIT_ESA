/**********************************************************************************************************************
 * @file IntCtrl_Lcfg.h
 * @brief This file is the implementation of the dynamic part of the inerrupt control
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "IntCtrl.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

const IntCtrl_InterruptCfgType  IntCtrl_interruptsCfg[INTCTRL_INTERRUPTS_COUNT] = 
{
    /* Interrupt number, group, sub group */
    {INTCTRL_WDT0,        	1, 0},
    {INTCTRL_TIMER0A,       1, 1}
};

const IntCtrl_ExceptionCfgType  IntCtrl_exceptionsCfg[INTCTRL_SYS_EXCEPTIONS_COUNT] = {
    /* Exception number, group, sub group */
    {INTCTRL_MemManage,		1, 0},
    {INTCTRL_BusFault,		1, 0},
    {INTCTRL_UsageFault,    1, 0},
    {INTCTRL_SVC,           1, 0},
    {INTCTRL_DebugMon,     	1, 0},
    {INTCTRL_PendSV,        1, 0},
    {INTCTRL_SysTick,       1, 0}
};

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Lcfg.c
 *********************************************************************************************************************/
