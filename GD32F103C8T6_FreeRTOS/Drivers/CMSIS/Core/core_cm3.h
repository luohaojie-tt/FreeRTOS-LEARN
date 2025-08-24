#ifndef __CORE_CM3_H_GENERIC
#define __CORE_CM3_H_GENERIC

/** \page CMSIS_MISRA_Exceptions  MISRA-C:2004 Compliance Exceptions
  CMSIS violates the following MISRA-C:2004 rules:

  \li Required Rule 8.5, object/function definition in header file.<br>
    Function definitions in header files are used to allow 'inlining'.

  \li Required Rule 18.4, declaration of union type or object of union type: '{...}'.<br>
    Unions are used for effective representation of core registers.

  \li Advisory Rule 19.7, Function-like macro defined.<br>
    Function-like macros are used to allow more efficient code.
 */

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
/** \ingroup Cortex_M3
  @{
 */

/*  CMSIS CM3 definitions */
#define __CM3_CMSIS_VERSION_MAIN  (0x04)                                   /*!< [31:16] CMSIS HAL main version   */
#define __CM3_CMSIS_VERSION_SUB   (0x00)                                   /*!< [15:0]  CMSIS HAL sub version    */
#define __CM3_CMSIS_VERSION       ((__CM3_CMSIS_VERSION_MAIN << 16) | \
                                    __CM3_CMSIS_VERSION_SUB          )     /*!< CMSIS HAL version number         */

#define __CORTEX_M                (0x03)                                   /*!< Cortex-M Core                    */


#if   defined ( __CC_ARM )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */
  #define __STATIC_INLINE  static __inline

#elif defined ( __GNUC__ )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */
  #define __STATIC_INLINE  static inline

#elif defined ( __ICCARM__ )
  #define __ASM            __asm                                      /*!< asm keyword for IAR Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */
  #define __STATIC_INLINE  static inline

#elif defined ( __TMS470__ )
  #define __ASM            __asm                                      /*!< asm keyword for TI CCS Compiler       */
  #define __STATIC_INLINE  static inline

#elif defined ( __TASKING__ )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler      */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler   */
  #define __STATIC_INLINE  static inline

#elif defined ( __CSMC__ )
  #define __packed
  #define __ASM            _asm                                      /*!< asm keyword for COSMIC Compiler      */
  #define __INLINE         inline                                    /*use -pc99 on compile line !< inline keyword for COSMIC Compiler   */
  #define __STATIC_INLINE  static inline

#endif

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED       0

#if defined ( __CC_ARM )
  #if defined __TARGET_FPU_VFP
    #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __GNUC__ )
  #if defined (__VFP_FP__) && !defined(__SOFTFP__)
    #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __ICCARM__ )
  #if defined __ARMVFP__
    #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __TMS470__ )
  #if defined __TI__VFP_SUPPORT____
    #warning "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __TASKING__ )
  #if defined __FPU_VFP__
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif

#elif defined ( __CSMC__ )		/* Cosmic */
  #if ( __CSMC__ & 0x400)		// FPU present for parser
    #error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
  #endif
#endif

#include <stdint.h>                      /* standard types definitions                      */
#include <core_cmInstr.h>                /* Core Instruction Access                         */
#include <core_cmFunc.h>                 /* Core Function Access                            */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM3_H_GENERIC */