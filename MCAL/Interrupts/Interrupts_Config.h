/**
 * @file Interrupts_Config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * 
 * @brief Interrupts Configuration
 *
 * The `Interrupts_Config.h` header file offers a centralized location to configure and manage interrupt settings
 * for an embedded application. It provides macros to customize interrupt priorities, enable or disable
 * interrupts, and set interrupt-related parameters. This interface simplifies the management of interrupt 
 * configurations, enhances code organization, and provides a convenient way to tailor interrupt behavior 
 * to specific project requirements.
 * 
 * @note The file is meticulously documented, offering clear explanations for each configuration option,
 *       parameter usage, and customization examples.
 * @note The `Interrupts_Config.h` interface promotes code adaptability and can be utilized across diverse
 *       microcontroller families and development environments.
 * 
 * @version 0.1
 * @date 01.08.23
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

