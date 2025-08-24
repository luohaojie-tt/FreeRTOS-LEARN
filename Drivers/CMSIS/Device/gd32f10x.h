/*
 * Copyright (c) 2021 GigaDevice Semiconductor Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _GD32F10X_H
#define _GD32F10X_H

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup GD32F10x_System
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#if !defined (GD32F10X_MD) && !defined (GD32F10X_HD) && !defined (GD32F10X_XD) && !defined (GD32F10X_CL)
  /* #define GD32F10X_MD */     /*!< GD32F10X_MD: GD32F101xx and GD32F103xx Medium density devices */
  /* #define GD32F10X_HD */     /*!< GD32F10X_HD: GD32F101xx and GD32F103xx High density devices */
  /* #define GD32F10X_XD */     /*!< GD32F10X_XD: GD32F101xx and GD32F103xx XL density devices */
  /* #define GD32F10X_CL */     /*!< GD32F10X_CL: GD32F105xx and GD32F107xx Connectivity line devices */
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */

#if !defined  USE_STDPERIPH_DRIVER
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will 
   be based on direct access to peripherals registers 
   */
  /*#define USE_STDPERIPH_DRIVER*/
#endif

/**
 * @brief In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application 
   
   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */
#if !defined  HSE_VALUE
#ifdef GD32F10X_CL   
#define HSE_VALUE    ((uint32_t)25000000) /*!< Value of the External oscillator in Hz */
#else 
#define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
#endif
#endif /* HSE_VALUE */


/**
 * @brief In the following line adjust the External High Speed oscillator (HSE) Startup 
   Timeout value 
   */
#define HSE_STARTUP_TIMEOUT   ((uint16_t)0x0500) /*!< Time out for HSE start up */
#define HSI_STARTUP_TIMEOUT   ((uint16_t)0x0500) /*!< Time out for HSI start up */


#define HSI_VALUE    ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/

/* GD32F10x Standard Peripheral Library version number V1.1 */
#define __GD32F10X_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __GD32F10X_STDPERIPH_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __GD32F10X_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __GD32F10X_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __GD32F10X_STDPERIPH_VERSION        ((__GD32F10X_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__GD32F10X_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__GD32F10X_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__GD32F10X_STDPERIPH_VERSION_RC))

/**
  * @}
  */

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* _GD32F10X_H */