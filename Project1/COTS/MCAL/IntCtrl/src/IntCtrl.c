/**********************************************************************************************************************
 * @file IntCtrl.c
 * @brief This file is the source file that implements Interrupt control driver for system NVIC\SCB
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "IntCtrl.h"
#include "Tiva_TM4C123GH6PM.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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

void IntCtrl_init(void)
{
    uint8 interruptBitOffset, interruptRegister, loopIndex;
    sint16 curInterruptNumber;
    uint32 interruptPRIxAddress;

/* Assigning bits to groups and subgroups */
#if (configInterruptGroup == 8)
    GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) = (INTCTRL_APINT_KEY | ((GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) & LOWER_HALF_WORD_MASK) | INTCTRL_PRILEVEL_XXX << APINT_PRIGROUP_BIT));
#elif (configInterruptGroup == 4)
    GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) = (INTCTRL_APINT_KEY | ((GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) & LOWER_HALF_WORD_MASk) | INTCTRL_PRILEVEL_XXY << APINT_PRIGROUP_BIT));
#elif (configInterruptGroup == 2)
    GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) = (INTCTRL_APINT_KEY | ((GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) & LOWER_HALF_WORD_MASK) | INTCTRL_PRILEVEL_XYY << APINT_PRIGROUP_BIT));
#elif (configInterruptGroup == 1)
    GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) = (INTCTRL_APINT_KEY | ((GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, APINT_OFFSET) & LOWER_HALF_WORD_MASk) | INTCTRL_PRILEVEL_YYY << APINT_PRIGROUP_BIT));
#else
	#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

    /* Configuring peripherals interrupts */
    for(loopIndex = 0; loopIndex < INTCTRL_INTERRUPTS_COUNT; ++loopIndex)
    {
		curInterruptNumber = (sint8)IntCtrl_interruptsCfg[loopIndex].vectorNumber;

        /* Enabling interrupt in ENx register */
		interruptRegister = (uint8)(curInterruptNumber / INTCTRL_REGISTER_SZ_BITS);
        interruptBitOffset = curInterruptNumber % INTCTRL_REGISTER_SZ_BITS;
		
		SET_BIT(((SYS_PERIPHERALS_BASE_ADDR + INTCTRL_EN0_OFFSET) + (interruptRegister * 4)), interruptBitOffset);
			
        /* Get corresponding PRI register */
        interruptBitOffset = (uint8)INTCTRL_PRIx_FIRST_BIT + (uint8)((curInterruptNumber % 4) * 8);
        interruptRegister = (uint8)(curInterruptNumber / 4);
        interruptPRIxAddress = SYS_PERIPHERALS_BASE_ADDR + INTCTRL_PRIx_OFFSET + (interruptRegister * INTCTRL_REGISTER_SZ_BYTES);

        /* Set priority group and sub group */
#if (configInterruptGroup == 8)
        *((vuint32 *)interruptPRIxAddress) |= ((uint32)(IntCtrl_interruptsCfg[loopIndex].exceptionGroup << interruptBitOffset));
#elif (configInterruptGroup == 4)
        *((vuint32 *)interruptPRIxAddress) |= ((uint32)(IntCtrl_InterruptsCfg[loopIndex].exceptionGroup << (interruptBitOffset + 1)));
        *((vuint32 *)interruptPRIxAddress) |= ((uint32)(IntCtrl_InterruptsCfg[loopIndex].exceptionSubGroup << interruptBitOffset));
#elif (configInterruptGroup == 2)
        *((vuint32 *)interruptPRIxAddress) |= ((uint32)(IntCtrl_interruptsCfg[loopIndex].exceptionGroup << (interruptBitOffset + 2)));
        *((vuint32 *)interruptPRIxAddress) |= ((uint32)(IntCtrl_interruptsCfg[loopIndex].exceptionSubGroup << interruptBitOffset));
#elif (configInterruptGroup == 1)
        *((vuint32 *)interruptPRIxAddress) |= ((uint32)(IntCtrl_InterruptsCfg[loopIndex].exceptionSubGroup << interruptBitOffset));
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

    }

    /* Configuring system exceptions */
    for(loopIndex = 0; loopIndex < INTCTRL_SYS_EXCEPTIONS_COUNT; ++loopIndex)
    {
        switch(IntCtrl_exceptionsCfg[loopIndex].exceptionNumber)
        {
			case INTCTRL_MemManage:
				SET_BIT((SYS_PERIPHERALS_BASE_ADDR + SYSHNDCTRL), BIT_16);
				
				/* Set priority group and sub group */
				
				/* Setting priority bits to zeros using a bit mask */
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) &= ~((uint32)0xE0);
				
#if (configInterruptGroup == 8)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_5);
#elif (configInterruptGroup == 4)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_6);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_5);
#elif (configInterruptGroup == 2)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionGroup) << BIT_7);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup) << BIT_5);
#elif (configInterruptGroup == 1)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_5);
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

            break;
			
			case INTCTRL_BusFault:
				SET_BIT((SYS_PERIPHERALS_BASE_ADDR + SYSHNDCTRL), BIT_17);
				
				/* Set priority group and sub group */
				
				/* Setting priority bits to zeros using a bit mask */
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) &= ~((uint32)0xE000);
				
#if (configInterruptGroup == 8)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_13);
#elif (configInterruptGroup == 4)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_14);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_13);
#elif (configInterruptGroup == 2)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionGroup) << BIT_15);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup) << BIT_13);
#elif (configInterruptGroup == 1)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_13);
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

				break;

			case INTCTRL_UsageFault:
				SET_BIT((SYS_PERIPHERALS_BASE_ADDR + SYSHNDCTRL), BIT_18);
				
				/* Set priority group and sub group */
				
				/* Setting priority bits to zeros using a bit mask */
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) &= ~((uint32)0xE00000);
				
#if (configInterruptGroup == 8)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_21);
#elif (configInterruptGroup == 4)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_22);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_21);
#elif (configInterruptGroup == 2)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionGroup) << BIT_23);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup) << BIT_21);
#elif (configInterruptGroup == 1)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_21);
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

				break;
				
			case INTCTRL_SVC:				
				/* Set priority group and sub group */
				
				/* Setting priority bits to zeros using a bit mask */
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI1_OFFSET) &= ~((uint32)0xE0000000);
				
#if (configInterruptGroup == 8)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI2_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_29);
#elif (configInterruptGroup == 4)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI2_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_30);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI2_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_29);
#elif (configInterruptGroup == 2)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI2_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionGroup) << BIT_31);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI2_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup) << BIT_29);
#elif (configInterruptGroup == 1)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI2_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_29);
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

				break;
			
			case INTCTRL_DebugMon:				
				/* Set priority group and sub group */
				
				/* Setting priority bits to zeros using a bit mask */
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) &= ~((uint32)0xE0);
				
#if (configInterruptGroup == 8)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_5);
#elif (configInterruptGroup == 4)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_6);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_5);
#elif (configInterruptGroup == 2)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionGroup) << BIT_7);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup) << BIT_5);
#elif (configInterruptGroup == 1)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_5);
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

				break;
			
			case INTCTRL_PendSV:				
				/* Set priority group and sub group */
				
				/* Setting priority bits to zeros using a bit mask */
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) &= ~((uint32)0xE00000);
				
#if (configInterruptGroup == 8)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_21);
#elif (configInterruptGroup == 4)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_22);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_21);
#elif (configInterruptGroup == 2)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionGroup) << BIT_23);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup) << BIT_21);
#elif (configInterruptGroup == 1)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_21);
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

				break;

			case INTCTRL_SysTick:
				SET_BIT((SYS_PERIPHERALS_BASE_ADDR + STCTRL_OFFSET), BIT_1);
				
				/* Set priority group and sub group */
				
				/* Setting priority bits to zeros using a bit mask */
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) &= ~((uint32)0xE0000000);
				
#if (configInterruptGroup == 8)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_29);
#elif (configInterruptGroup == 4)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionGroup << BIT_30);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_29);
#elif (configInterruptGroup == 2)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionGroup) << BIT_31);
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)(IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup) << BIT_29);
#elif (configInterruptGroup == 1)
				GET_ADDRESS_BASE_OFFSET(SYS_PERIPHERALS_BASE_ADDR, SYSPRI3_OFFSET) |= ((uint32)IntCtrl_exceptionsCfg[loopIndex].exceptionSubGroup << BIT_29);
#else
#error "Invalid value for configInterruptGroup"
#endif /* configInterruptGroup */

				break;

			default:
				break;
		}
    }
}

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.c
 *********************************************************************************************************************/
