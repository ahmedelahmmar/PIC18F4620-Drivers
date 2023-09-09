/**
 * @file GPIO_Config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief GPIO Configuration Interface
 *
 * The GPIO_Config.h header file offers a centralized location to configure and manage GPIO settings for an
 * embedded application. It provides macros, constants, and preprocessor directives to customize GPIO pin
 * assignments, set pin modes, and define port configurations. This interface simplifies the management of GPIO
 * configurations, enhances code organization, and provides a convenient way to tailor GPIO behavior to specific
 * project requirements.
 *
 * @note The file is documented, offering clear explanations for each configuration option, parameter usage,
 *       and customization examples.
 * @note The GPIO_Config.h interface promotes code adaptability and can be utilized across diverse microcontroller
 *       families and development environments.
 * 
 * @version 0.1
 * @date 24.07.23
 */

#ifndef _GPIO_CONFIG_H_
#define	_GPIO_CONFIG_H_

/** 
 * @def GPIO_CHANNEL_INTERFACES
 * @brief Control macro to enable or disable GPIO channel interfaces.
 *     - STD_ON: Include GPIO channel interfaces in the build.
 *     - STD_OFF: Exclude GPIO channel interfaces from the build.
 */
#define GPIO_CHANNEL_INTERFACES     STD_ON

/** 
 * @def GPIO_PORT_INTERFACES
 * @brief Control macro to enable or disable GPIO port interfaces.
 *     - STD_ON: Include GPIO port interfaces in the build.
 *     - STD_OFF: Exclude GPIO port interfaces from the build.
 */
#define GPIO_PORT_INTERFACES        STD_OFF

#endif	/* _GPIO_CONFIG_H_ */

