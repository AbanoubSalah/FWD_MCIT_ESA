/**********************************************************************************************************************
 * @file Gpt.c
 * @brief This file is the implementation for GPT driver for TI microcontroller TM4C123GH6PM
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Gpt.h"
#include "Common_Macros.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/


static const uint32_t GptBaseAddress[] = {
	TIMER0_REG_BASE,
	TIMER1_REG_BASE,
	TIMER2_REG_BASE,
	TIMER3_REG_BASE,
	TIMER4_REG_BASE,
	TIMER5_REG_BASE,
	WTIMER0_REG_BASE,
	WTIMER1_REG_BASE,
	WTIMER2_REG_BASE,
	WTIMER3_REG_BASE,
	WTIMER4_REG_BASE,
	WTIMER5_REG_BASE,
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

void Gpt_Init(const Gpt_ConfigType Gpt_Config[])
{
	uint8 loopIndex;
	
	for(loopIndex = 0; loopIndex < Gpt_CFG_SIZE; ++loopIndex)
    {
		/* Disabling the timer */
		GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Gpt_Config[loopIndex].GptChannelid] + GPTMCTL_OFFSET), GPTMCTL_TAEN_BIT) = STD_LOW;
		
		/* Activating timer clock & Selecting timer configuration */
		if(Gpt_Config[loopIndex].GptChannelid < Gpt_Channel_WTimer0)
		{
			GET_BITBAND_ALIAS_ADDRESS((SYSCTRL_BASE_ADDRESS + RCGCTIMER_OFFSET), (Gpt_Config[loopIndex].GptChannelid % GPT_NUMBER_Timers_GROUP)) = STD_HIGH;
			GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMCFG_OFFSET) = 0x4;
		}
		else if(Gpt_Config[loopIndex].GptChannelid > Gpt_Channel_Timer5)
		{
			GET_BITBAND_ALIAS_ADDRESS((SYSCTRL_BASE_ADDRESS + RCGCWTIMER_OFFSET), (Gpt_Config[loopIndex].GptChannelid % GPT_NUMBER_Timers_GROUP)) = STD_HIGH;
			GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMCFG_OFFSET) = 0x0;
		}
		
		/* Setting timer control register to zeros before any changes */
		GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMCTL_OFFSET) = 0x00000000;
		
		/* Setting the timer channel mode (oneshot or continuous) */
		switch(Gpt_Config[loopIndex].GptChannelMode)
		{
			case GPT_CH_MODE_ONESHOT:
				GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMTAMR_OFFSET) = (GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMTAMR_OFFSET) & (0xFFFFFFFC)) || 0x00000001;
				break;
			
			case GPT_CH_MODE_CONTINUOUS:
				GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMTAMR_OFFSET) = (GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMTAMR_OFFSET) & (0xFFFFFFFC)) || 0x00000002;
				break;
			default:
				break;
		}
		
		/* Set Timer count direction as up-counter */
		GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Gpt_Config[loopIndex].GptChannelid] + GPTMTAMR_OFFSET), GPTMTAMR_TACDIR_BIT) = STD_HIGH;
		
		/* Setting the prescaler value */
		GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Config[loopIndex].GptChannelid], GPTMTAPR_OFFSET) = SystemCoreClock / Gpt_Config[loopIndex].GptChannelTickFrequency;
		
		/* Disabling time-out interrupt by default */
		GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Gpt_Config[loopIndex].GptChannelid] + GPTMIMR_OFFSET), GPTMIMR_TATOIM_Bit) = STD_LOW;
#if (GPT_USE_PREDEF_TIMERS == 1)
		// Only predefined timers can run
		if(((Gpt_Channel_WTimer4 == Gpt_Config[loopIndex].GptChannelid) || (Gpt_Channel_WTimer5 == Gpt_Config[loopIndex].GptChannelid)) && (1 == GPT_USE_PREDEF_TIMERS))
		{
			if((GPT_PREDEF_1US_16BIT == 1) || (GPT_PREDEF_1US_24BIT == 1) || (GPT_PREDEF_1US_32BIT == 1))
			{
				/* Timer A interval load register for 1 us period */
				GET_ADDRESS_BASE_OFFSET(GptBaseAddress[GptBaseAddress[Gpt_Config[loopIndex].GptChannelid]], GPTMTAILR_OFFSET) = ((SystemCoreClock / 1000) / GET_ADDRESS_BASE_OFFSET(GptBaseAddress[GptBaseAddress[Gpt_Config[loopIndex].GptChannelid]], GPTMTAPR_OFFSET)) - 1;
			}
			else
			{
				/* Timer A interval load register for 100 us period */
				GET_ADDRESS_BASE_OFFSET(GptBaseAddress[GptBaseAddress[Gpt_Config[loopIndex].GptChannelid]], GPTMTAILR_OFFSET) = ((SystemCoreClock / 10) / GET_ADDRESS_BASE_OFFSET(GptBaseAddress[GptBaseAddress[Gpt_Config[loopIndex].GptChannelid]], GPTMTAPR_OFFSET)) - 1;
			}
			
			/* Clearing timer time-out interrupt */
			GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Gpt_Config[loopIndex].GptChannelid] + GPTMICR_OFFSET), GPTMICR_TATOCINT_Bit) = STD_HIGH;
			
			/* Enabling timer */
			GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Gpt_Config[loopIndex].GptChannelid] + GPTMCTL_OFFSET), GPTMCTL_TAEN_BIT) = STD_HIGH;
		}
#endif
	}
}

Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
	return (GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Channel], GPTMTAV_OFFSET) * GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Channel], GPTMTAPR_OFFSET) / (SystemCoreClock / 10000));
}

Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
	return (GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Channel], GPTMTAILR_OFFSET) - GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Channel], GPTMTAV_OFFSET)) * GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Channel], GPTMTAPR_OFFSET) / (SystemCoreClock / 1000);
}

void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
	/* Assigning timer number ticks before time-out */
	GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Channel], GPTMTAILR_OFFSET) = Value;
	
	/* Clearing timer time-out interrupt */
	GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Channel] + GPTMICR_OFFSET), GPTMICR_TATOCINT_Bit) = STD_HIGH;
	
	/* Enabling timer */
	GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Channel] + GPTMCTL_OFFSET), GPTMCTL_TAEN_BIT) = STD_HIGH;
}

void Gpt_StopTimer(Gpt_ChannelType Channel)
{
	GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Channel], GPTMTAV_OFFSET) = 0;
	GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Channel] + GPTMCTL_OFFSET), GPTMCTL_TAEN_BIT) = STD_LOW;
}

void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
	/* Enabling time-out interrupt */
	GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Channel] + GPTMIMR_OFFSET), GPTMIMR_TATOIM_Bit) = STD_HIGH;
}

void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
	/* Disabling time-out interrupt */
	GET_BITBAND_ALIAS_ADDRESS((GptBaseAddress[Channel] + GPTMIMR_OFFSET), GPTMIMR_TATOIM_Bit) = STD_LOW;
}

Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32 *TimeValuePtr)
{
	uint32 factorMultiplier;
	switch(PredefTimer)
	{
		case GPT_PREDEF_TIMER_1US_16BIT:
			/* Get least 16 bits as pre-defined */
			factorMultiplier = GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer4], GPTMTAILR_OFFSET) & (0xFFFF);
			*TimeValuePtr = factorMultiplier * GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer4], GPTMTAPR_OFFSET) / (SystemCoreClock / 1000);
			break;
		
		case GPT_PREDEF_TIMER_1US_24BIT:
			/* Get least 24 bits as pre-defined */
			factorMultiplier = GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer4], GPTMTAILR_OFFSET) & (0x1FFFFF);
			*TimeValuePtr = factorMultiplier * GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer4], GPTMTAPR_OFFSET) / (SystemCoreClock / 1000);
			break;
		
		case GPT_PREDEF_TIMER_1US_32BIT:
			/* Get least 32 bits as pre-defined */
			factorMultiplier = GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer4], GPTMTAILR_OFFSET) & (0xFFFFFFFF);
			*TimeValuePtr = factorMultiplier * GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer4], GPTMTAPR_OFFSET) / (SystemCoreClock / 1000);
			break;
		
		case GPT_PREDEF_TIMER_100US_32BIT:
			/* Get least 32 bits as pre-defined */
			factorMultiplier = GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer5], GPTMTAILR_OFFSET) & (0xFFFFFFFF);
			*TimeValuePtr = factorMultiplier * GET_ADDRESS_BASE_OFFSET(GptBaseAddress[Gpt_Channel_WTimer5], GPTMTAPR_OFFSET) / (SystemCoreClock / 1000);
			break;
	}
	
	return E_OK;
}

/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/
