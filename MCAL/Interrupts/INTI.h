/**
 * @file INTI.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * 
 * @brief Internal Interrupt (INTI) Interface
 *
 * The INTI interface simplifies interrupt management on a microcontroller, offering functions to initialize,
 * configure, and handle interrupts. It abstracts low-level interrupt settings, providing an organized way to
 * manage hardware events and execute corresponding actions. This interface enhances code readability,
 * promotes efficient interrupt handling, and supports smooth integration of interrupt-driven operations.
 *
 * @note The file is documented, offering clear insights into each function's purpose, parameters, return values,
 *       and usage examples.
 * @note The INTI interface ensures portability and can be utilized across different microcontroller families
 *       and development environments.
 * 
 * @version 0.2
 * @date 01.08.23 
 */

#ifndef _INTI_H_
#define _INTI_H_

#include "Interrupts_Config.h"
#include "EXTI.h"

#if ((INTERRUPTS_ADC_INTERRUPTS_FEAUTURE != STD_ON) && (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE != STD_OFF))
#warning "'INTERRUPTS_ADC_INTERRUPTS_FEAUTURE' not configured in Interrupts_Config.h"
#endif

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
void INTI_ADC_EnableInterrupt(void);
void INTI_ADC_DisableInterrupt(void);
void INTI_ADC_ClearFlag(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_ADC_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority);
    void INTI_ADC_DeInitPriority(void);
    #endif
#endif

#endif /* _INTI_H_ */