/**********************************************************************************************************************
 * @file Common_Macro.h
 * @brief This file contains utility macros
 *
 * @author Abanoub Salah
 * @date August 11, 2022
 * *********************************************************************************************************************/

#ifndef _COMMON_MACROS_H
#define _COMMON_MACROS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Tiva_TM4C123GH6PM.h"
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define UPPER_HALF_WORD_MASK									(uint32)(0xFFFF0000)
#define LOWER_HALF_WORD_MASK									(uint32)(0x0000FFFF)

#define BIT_0           										(uint32)(0)
#define BIT_1           										(uint32)(1)
#define BIT_2           										(uint32)(2)
#define BIT_3           										(uint32)(3)
#define BIT_4           										(uint32)(4)
#define BIT_5           										(uint32)(5)
#define BIT_6           										(uint32)(6)
#define BIT_7           										(uint32)(7)
#define BIT_8           										(uint32)(8)
#define BIT_9           										(uint32)(9)
#define BIT_10           										(uint32)(10)
#define BIT_11           										(uint32)(11)
#define BIT_12           										(uint32)(12)
#define BIT_13           										(uint32)(13)
#define BIT_14           										(uint32)(14)
#define BIT_15           										(uint32)(15)
#define BIT_16           										(uint32)(16)
#define BIT_17           										(uint32)(17)
#define BIT_18           										(uint32)(18)
#define BIT_19           										(uint32)(19)
#define BIT_20           										(uint32)(20)
#define BIT_21           										(uint32)(21)
#define BIT_22           										(uint32)(22)
#define BIT_23           										(uint32)(23)
#define BIT_24           										(uint32)(24)
#define BIT_25           										(uint32)(25)
#define BIT_26           										(uint32)(26)
#define BIT_27           										(uint32)(27)
#define BIT_28           										(uint32)(28)
#define BIT_29           										(uint32)(29)
#define BIT_30           										(uint32)(30)
#define BIT_31           										(uint32)(31)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

#define GET_BITBAND_ALIAS_ADDRESS(RegAddress, bit)        		(*((vuint32 *)(PERIPHERALS_ALIAS_BASE + ((((RegAddress - PERIPHERALS_BASE) * 8) + bit) * 4))))
#define GET_ADDRESS_BASE_OFFSET(baseAddr, offset)  				(*((vuint32 *)(baseAddr + offset)))

/* Set a certain bit in any register */
#define SET_BIT(RegAddress, bit)     							(*((vuint32 *)RegAddress) |= (1 << bit))

/* Clear a certain bit in any register */
#define CLEAR_BIT(RegAddress, bit)     							(*((vuint32 *)RegAddress) &= ~(1 << bit))

/* Set Bit using bit mapping of SRAM */
#define SET_BIT_RAM_BB(RegAddress, BIT) 						((*((vuint32 *)( SRAM_ALIAS_BASE + (((uint32)(&RegAddress) - SRAM_BASE) * 32) + ((BIT) * 4) ))) = STD_HIGH)

/* Set Bit using bit mapping of Peripheral */
#define SET_BIT_PER_BB(RegAddress, BIT) 						((*((vuint32 *)( PERIPHERALS_ALIAS_BASE + (((uint32)(&RegAddress) - PERIPHERALS_BASE) * 32) + ((BIT) * 4) ))) = STD_HIGH)

/* Clear Bit using bit mapping of SRAM */
#define CLEAR_BIT_RAM_BB(RegAddress, BIT)						((*((vuint32 *)( SRAM_ALIAS_BASE + (((uint32)(&RegAddress) - SRAM_BASE) * 32) + ((BIT) * 4) ))) = STD_LOW)

/* Clear Bit using bit mapping of Peripheral */
#define CLEAR_BIT_PER_BB(RegAddress, BIT)						((*((vuint32 *)( PERIPHERALS_ALIAS_BASE + (((uint32)(&RegAddress) - PERIPHERALS_BASE) * 32) + ((BIT) * 4) ))) = STD_LOW)

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(RegAddress, bit)    							(*((vuint32 *)RegAddress) ^= (1 << bit))

/* Check if a specific bit is set in any register and return true if yes */
#define IS_BIT_SET(RegAddress, bit)  							(((*((vuint32 *)RegAddress)) & (1 << (bit))) >> bit)

/* Rotate right the register value with specific number of rotates */
#define ROR(RegAddress, num) 									((*((vuint32 *)RegAddress)) = (RegAddress >> num) | (RegAddress << ((sizeof(RegAddress) * 8) - num)))

/* Rotate left the register value with specific number of rotates */
#define ROL(RegAddress, num) 									((*((vuint32 *)RegAddress)) = (RegAddress << num) | (RegAddress >> ((sizeof(RegAddress) * 8) - num)))

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* _COMMON_MACROS_H */

/**********************************************************************************************************************
 *  END OF FILE: Common_Macros.h
 *********************************************************************************************************************/
