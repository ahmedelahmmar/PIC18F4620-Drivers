/**
 * @file Interrupts_Handler.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 *  
 * @brief Centralized Interrupt Handlers
 *
 * The `Interrupts_Handler.h` header file serves as a central hub for managing interrupt service routines (ISRs)
 * in an embedded application. It offers a collection of functions to handle different types of interrupts,
 * abstracting low-level ISR implementations. This interface simplifies the organization of ISRs, enhances code
 * modularity, and provides an efficient means to manage hardware events and corresponding actions.
 *
 * @note The file is thoroughly documented, offering clear explanations for each function's purpose, parameters,
 *       return values, and usage examples.
 * @note The `Interrupts_Handler.h` interface promotes code maintainability and can be used across diverse
 *       microcontroller families and development environments.
 * 
 * @version 0.1
 * @date 01.08.23
 */

#ifndef _INTERRUPTS_HANDLER_H_
#define	_INTERRUPTS_HANDLER_H_

#include "EXTI/EXTI.h"

#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)

void __interrupt() HighPriorityInterruptHandler(void);
void __interrupt(low_priority) LowPriorityInterruptHandler(void);

#elif (INTERRUPTS_PRIORITY_FEATURE == STD_OFF)

void __interrupt() InterruptHandler(void);

#else
#warning "'INTERRUPTS_PRIORITY_FEATURE' not configured in Interrupts_Config.h"
#endif

#endif	/* _INTERRUPTS_HANDLER_H_ */

