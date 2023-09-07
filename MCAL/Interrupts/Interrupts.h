/**
 * @file Interrupts.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * 
 * @brief Interrupts Management Interface
 *
 * The Interrupt interface simplifies the management of interrupt functionality on a microcontroller. It offers
 * functions to enable, disable, and configure interrupts, providing an efficient way to handle hardware events
 * and corresponding actions. This interface abstracts low-level interrupt configurations, enhancing code clarity
 * and offering a streamlined approach to implement interrupt-driven operations.
 *
 * @note Include this header file in your application code to access the Interrupt control interface.
 * @note The file is documented, offering clear insights into each function's role, input parameters, return values,
 *       and usage examples.
 * @note The Interrupt interface ensures portability and can be utilized across different microcontroller families
 *       and development environments.
 * 
 * @version 0.1
 * @date 03.08.23
 */

#ifndef _INTERRUPTS_H_
#define	_INTERRUPTS_H_

#include "../../MCAL/GPIO/GPIO.h"

#include "Interrupts_Config.h"
#include "INTI/INTI.h"
#include "EXTI/EXTI.h"

#endif	/* _INTERRUPTS_H_ */

