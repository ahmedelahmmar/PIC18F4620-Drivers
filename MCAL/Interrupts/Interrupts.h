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
#include "INTI.h"
#include "EXTI.h"

#include "../../lib/compiler.h"
#include <../proc/pic18f4620.h>

#define INTERRUPTS_GlobalInterruptsFlag                      (INTCONbits.GIE)

#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)

#define INTERRUPTS_EnablePriorityFeature()                   (RCONbits.IPEN = 1)
#define INTERRUPTS_DisablePriorityFeature()                  (RCONbits.IPEN = 0)

#define INTERRUPTS_EnableAllHighPriorityInterrupts()         (INTCONbits.GIEH = 1)
#define INTERRUPTS_DisableAllHighPriorityInterrupts()        (INTCONbits.GIEH = 0)

#define INTERRUPTS_EnableAllLowPriorityInterrupts()          (INTCONbits.GIEL = 1)
#define INTERRUPTS_DisableAllLowPriorityInterrupts()         (INTCONbits.GIEL = 0)

#elif (INTERRUPTS_PRIORITY_FEATURE == STD_OFF)

#define INTERRUPTS_EnableAllGlobalInterrupts()               (INTCONbits.GIE = 1)
#define INTERRUPTS_DisableAllGlobalInterrupts()              (INTCONbits.GIE = 0)

#define INTERRUPTS_EnableAllPeripheralInterrupts()           (INTCONbits.PEIE = 1)
#define INTERRUPTS_DisableAllPeripheralInterrupts()          (INTCONbits.PEIE = 0)

#else
#warning "'INTERRUPTS_PRIORITY_FEATURE' not configured in Interrupts_Config.h"
#endif

#endif	/* _INTERRUPTS_H_ */

