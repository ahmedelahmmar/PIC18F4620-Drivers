/**
 * @file GPIO_Config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 2023-07-24
 * 
 * @copyright Copyright (c) 2023
 * 
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
#define GPIO_PORT_INTERFACES        STD_ON

#endif	/* _GPIO_CONFIG_H_ */

