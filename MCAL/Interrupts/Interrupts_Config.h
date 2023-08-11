/**
 * @file Interrupts_Config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date August 1, 2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _INTERRUPTS_CONFIG_H_
#define	_INTERRUPTS_CONFIG_H_

/**
 * @def INTERRUPTS_PRIORITY_FEATURE
 * @brief Control macro to enable or disable interrupt priority feature.
 *     - STD_ON: Enable the interrupt priority feature.
 *     - STD_OFF: Disable the interrupt priority feature.
 */
#define INTERRUPTS_PRIORITY_FEATURE                  STD_OFF

/**
 * @def INTERRUPTS_INTx_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable INTx interrupts.
 *     - STD_ON: Enable the INTx interrupts.
 *     - STD_OFF: Disable the INTx interrupts.
 */
#define INTERRUPTS_INTx_INTERRUPTS_FEATURE           STD_OFF

/**
 * @def INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable OnChange interrupts.
 *     - STD_ON: Enable the OnChange interrupts.
 *     - STD_OFF: Disable the OnChange interrupts.
 */
#define INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE      STD_ON

#endif	/* _INTERRUPTS_CONFIG_H_ */

