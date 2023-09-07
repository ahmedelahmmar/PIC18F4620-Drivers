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

#include "../EXTI/EXTI.h"

void INTI_EnableInterrupts(void);
void INTI_DisableInterrupts(void);
uint8 INTI_GetInterruptStatus(void);
void INTI_SetInterruptStatus(uint8 Status);

#if ((INTERRUPTS_ADC_INTERRUPTS_FEATURE != STD_ON) && (INTERRUPTS_ADC_INTERRUPTS_FEATURE != STD_OFF))
#warning "'INTERRUPTS_ADC_INTERRUPTS_FEATURE' not configured in Interrupts_Config.h"
#endif

void INTI_ADC_ClearFlag(void);
uint8 INTI_ADC_Flag(void);

#if (INTERRUPTS_ADC_INTERRUPTS_FEATURE == STD_ON)
void INTI_ADC_EnableInterrupt(void);
void INTI_ADC_DisableInterrupt(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_ADC_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority);
    void INTI_ADC_DeInitPriority(void);
    #endif
#endif

#if ((INTERRUPTS_TIMER0_INTERRUPTS_FEATURE != STD_ON) && (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE != STD_OFF))
#warning "'INTERRUPTS_TIMER0_INTERRUPTS_FEATURE' not configured in Interrupts_Config.h"
#endif

void INTI_TIMER0_ClearFlag(void);
uint8 INTI_TIMER0_Flag(void);

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
void INTI_TIMER0_EnableInterrupt(void);
void INTI_TIMER0_DisableInterrupt(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_TIMER0_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority);
    void INTI_TIMER0_DeInitPriority(void);
    #endif
#endif

#if ((INTERRUPTS_EUSART_INTERRUPTS_FEATURE != STD_ON) && (INTERRUPTS_EUSART_INTERRUPTS_FEATURE != STD_OFF))
#warning "'INTERRUPTS_EUSART_INTERRUPTS_FEATURE' not configured in Interrupts_Config.h"
#endif

#if ((INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE != STD_ON) && (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE != STD_OFF))
#warning "'INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE' not configured in Interrupts_Config.h"
#endif

#if ((INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE != STD_ON) && (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE != STD_OFF))
#warning "'INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE' not configured in Interrupts_Config.h"
#endif

uint8 INTI_EUSART_TxFlag(void);
uint8 INTI_EUSART_RxFlag(void);
#if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)

    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
    void INTI_EUSART_EnableTxInterrupt(void);
    void INTI_EUSART_DisableTxInterrupt(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_EUSART_SetTxPriority(INTERRUPTS_PriorityTypeDef loc_priority);
    void INTI_EUSART_DeInitTxPriority(void);
    #endif

    #endif

    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
    void INTI_EUSART_EnableRxInterrupt(void);
    void INTI_EUSART_DisableRxInterrupt(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_EUSART_SetRxPriority(INTERRUPTS_PriorityTypeDef loc_priority);
    void INTI_EUSART_DeInitRxPriority(void);
    #endif

    #endif

#endif


#endif /* _INTI_H_ */