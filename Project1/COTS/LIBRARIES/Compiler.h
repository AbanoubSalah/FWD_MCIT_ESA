/**********************************************************************************************************************
 * @file Compiler.h
 * @brief This file is the compiler specific definitions
 *
 * @author Abanoub Salah
 * @date August 10, 2022
 * *********************************************************************************************************************/

#ifndef _COMPILER_H
#define _COMPILER_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define AUTOMATIC
#define STATIC 	static
#define NULL_PTR	((void *)0)

#if defined(__GNUC__)
#define CC_EXTENSION 	__extension__
#elif defined(__CWCC__)
#define CC_EXTENSION
#pragma read_only_switch_tables on
#elif defined(__DCC__) || defined(__ghs__)
#define CC_EXTENSION
#endif

#if defined(__ghs__)
#define typeof __typeof__
#endif


#if defined(__GNUC__) || defined(__CWCC__) || defined(__DCC__) || defined(__ghs__)
#define __weak		 		__attribute__ ((weak))
#else
#define __weak
#endif

#if defined(__GNUC__)
#define __balign(x)       __attribute__ ((aligned (x)))
#elif defined(__ghs__)
#define __balign(x)       __attribute__ ((aligned (x)))
#elif defined(__CWCC__)
#define __balign(x)       __attribute__ ((aligned (x)))
#elif defined(__DCC__)
#define __balign(x)       __attribute__ ((aligned (x)))
#elif defined(__ICCHCS12__)
#define Pragma(x) _Pragma(#x)
#define __balign(x)       Pragma(data_alignment=_align)
#else
#error Compiler not defined.
#endif

#define SECTION_BALIGN(x)  __balign(x)

#if defined(__ICCHCS12__)
#define restrict
#define DECLARE_WEAK
#define __simple __simple
#else
#define DECLARE_WEAK			__attribute__ ((weak))
#define __simple
#endif

#define INLINE __inline__

#define FUNC(rettype,memclass) rettype

#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#define CONSTP2VAR(ptrtype,memclass,ptrclass) ptrtype * const

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

#define P2FUNC(rettype,ptrclass,fctname) rettype (*fctname)

#define CONST(consttype,memclass) const consttype

#define VAR(vartype,memclass) vartype

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

#endif  /* _COMPILER_H */

/**********************************************************************************************************************
 *  END OF FILE: Compiler.h
 *********************************************************************************************************************/
