/**
 * @file Interrupts.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date August 3, 2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _INTERRUPTS_H_
#define	_INTERRUPTS_H_

#include "../../MCAL/GPIO/GPIO.h"

#include "Interrupts_Config.h"
#include "INTI.h"
#include "EXTI.h"

#include "../../lib/compiler.h"
#include <../proc/pic18f4620.h>

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

