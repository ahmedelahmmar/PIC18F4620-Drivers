/**
 * @file Interrupts_Handler.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date August 1, 2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _INTERRUPTS_HANDLER_H_
#define	_INTERRUPTS_HANDLER_H_

#include "EXTI.h"

#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)

void __interrupt() HighPriorityInterruptHandler(void);
void __interrupt(low_priority) LowPriorityInterruptHandler(void);

#elif (INTERRUPTS_PRIORITY_FEATURE == STD_OFF)

void __interrupt() InterruptHandler(void);

#else
#warning "'INTERRUPTS_PRIORITY_FEATURE' not configured in Interrupts_Config.h"
#endif

#endif	/* _INTERRUPTS_HANDLER_H_ */

