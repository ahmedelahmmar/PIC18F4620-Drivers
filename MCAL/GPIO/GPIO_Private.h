/**
 * @file GPIO_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * 
 * @brief Private GPIO Services
 *
 * The GPIO_Private.h header file contains private functions and services that are meant for internal use within
 * an embedded application. These functions support the internal workings of the GPIO module, handling specific
 * GPIO-related tasks. By keeping them in a separate file, this interface encapsulates internal logic, enhances
 * code modularity, and provides a structured approach to managing private GPIO services.
 *
 * @note Include this header file only in implementation files that require access to private GPIO services.
 * @note The file is documented to clarify the purpose, input parameters, return values, and internal usage of
 *       each private function and service.
 * @note The GPIO_Private.h interface improves code organization and maintainability by isolating internal
 *       GPIO-related operations from the main public interface.
 * 
 * @version 0.1
 * @date 24.07.23
 */

#ifndef _GPIO_PRIVATE_H_
#define	_GPIO_PRIVATE_H_

#include "../../lib/compiler.h"
#include "../../lib/bitmasking.h"
#include <../proc/pic18f4620.h>

#define GPIO_ALL_PINS       0xFF

#endif	/* _GPIO_PRIVATE_H_ */

