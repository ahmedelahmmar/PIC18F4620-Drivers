/**
 * @file EUSART_Config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief 
 * 
 * @version 0.1
 * @date 23.08.23
 */

#ifndef _EUSART_CONFIG_H_
#define _EUSART_CONFIG_H_

/**
 * @def EUSART_SYNCHRONOUS_MODE
 * @brief Control macro to enable or disable Synchronous Mode for the EUSART module.
 *     - STD_ON: Enable Synchronous Mode.
 *     - STD_OFF: Disable Synchronous Mode.
 */
#define EUSART_SYNCHRONOUS_MODE                                 STD_OFF

#if ((EUSART_SYNCHRONOUS_MODE != STD_ON) && (EUSART_SYNCHRONOUS_MODE != STD_OFF))
#warning "'EUSART_SYNCHRONOUS_MODE' not configured in EUSART_Config.h"
#endif

#endif /* _EUSART_CONFIG_H_ */