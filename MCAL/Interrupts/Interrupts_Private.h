/**
 * @file Interrupts_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date August 1, 2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _INTERRUPTS_PRIVATE_H_
#define	_INTERRUPTS_PRIVATE_H_

#include "../mcu_config.h"
#include "Interrupts_Config.h"
#include "../../lib/compiler.h"
#include <../proc/pic18f4620.h>

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)

#define EXTI_INTx_PIN                           0
#define EXTI_INTx_PORT                          1
    
#define EXTI_INT0_EnableInterrupt()             (INTCONbits.INT0IE = 1)
#define EXTI_INT0_DisableInterrupt()            (INTCONbits.INT0IE = 0)
#define EXTI_INT0_ClearFlag()                   (INTCONbits.INT0IF = 0)
#define EXTI_INT0_Flag()                        (INTCONbits.INT0IF)
#define EXTI_INT0_SetTriggerAsFallingEdge()     (INTCON2bits.INTEDG0 = 0)
#define EXTI_INT0_SetTriggerAsRisingEdge()      (INTCON2bits.INTEDG0 = 1)
#define EXTI_INT0_DeInitTrigger()               (EXTI_INT0_SetTriggerAsFallingEdge())

#define EXTI_INT1_EnableInterrupt()             (INTCON3bits.INT1IE = 1)
#define EXTI_INT1_DisableInterrupt()            (INTCON3bits.INT1IE = 0)
#define EXTI_INT1_ClearFlag()                   (INTCON3bits.INT1IF = 0)
#define EXTI_INT1_Flag()                        (INTCON3bits.INT1IF)
#define EXTI_INT1_SetTriggerAsFallingEdge()     (INTCON2bits.INTEDG1 = 0)
#define EXTI_INT1_SetTriggerAsRisingEdge()      (INTCON2bits.INTEDG1 = 1)
#define EXTI_INT1_DeInitTrigger()               (EXTI_INT1_SetTriggerAsFallingEdge())

#define EXTI_INT2_EnableInterrupt()             (INTCON3bits.INT2IE = 1)
#define EXTI_INT2_DisableInterrupt()            (INTCON3bits.INT2IE = 0)
#define EXTI_INT2_ClearFlag()                   (INTCON3bits.INT2IF = 0)
#define EXTI_INT2_Flag()                        (INTCON3bits.INT2IF)
#define EXTI_INT2_SetTriggerAsFallingEdge()     (INTCON2bits.INTEDG2 = 0)
#define EXTI_INT2_SetTriggerAsRisingEdge()      (INTCON2bits.INTEDG2 = 1)
#define EXTI_INT2_DeInitTrigger()               (EXTI_INT2_SetTriggerAsFallingEdge())

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)

//    #define EXTI_INT0_SetAsHighPriority()               NULL
//    #define EXTI_INT0_SetAsLowPriority()                NULL
//    #define EXTI_INT0_DeInitPriority()          (EXTI_INT0_SetAsHighPriority())

    #define EXTI_INT1_SetAsHighPriority()       (INTCON3bits.INT1IP = 1)
    #define EXTI_INT1_SetAsLowPriority()        (INTCON3bits.INT1IP = 0)
    #define EXTI_INT1_DeInitPriority()          (EXTI_INT1_SetAsLowPriority())

    #define EXTI_INT2_SetAsHighPriority()       (INTCON3bits.INT2IP = 1)
    #define EXTI_INT2_SetAsLowPriority()        (INTCON3bits.INT2IP = 0)
    #define EXTI_INT2_DeInitPriority()          (EXTI_INT2_SetAsLowPriority())

    #endif
#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)

#define EXTI_RBx_PIN                            0
#define EXTI_RBx_PORT                           1

#define EXTI_RBx_RISING_EDGE                    0
#define EXTI_RBx_FALLING_EDGE                   1

#define EXTI_RBx_FLAG_LOWERED                   0
#define EXTI_RBx_FLAG_RAISED                    1

#define EXTI_RBx_EnableInterrupt()              (INTCONbits.RBIE = 1)
#define EXTI_RBx_DisableInterrupt()             (INTCONbits.RBIE = 0)
#define EXTI_RBx_ClearFlag()                    (INTCONbits.RBIF = 0)    
#define EXTI_RBx_Flag()                         (INTCONbits.RBIF)  

#define EXTI_RB4_RisingEdgeFlag()               (1 == PORTBbits.RB4)
#define EXTI_RB4_FallingEdgeFlag()              (0 == PORTBbits.RB4)

#define EXTI_RB5_RisingEdgeFlag()               (1 == PORTBbits.RB5)
#define EXTI_RB5_FallingEdgeFlag()              (0 == PORTBbits.RB5)

#define EXTI_RB6_RisingEdgeFlag()               (1 == PORTBbits.RB6)
#define EXTI_RB6_FallingEdgeFlag()              (0 == PORTBbits.RB6)

#define EXTI_RB7_RisingEdgeFlag()               (1 == PORTBbits.RB7)
#define EXTI_RB7_FallingEdgeFlag()              (0 == PORTBbits.RB7)
        
    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        
    #define EXTI_RBx_SetAsHighPriority()        (INTCON2bits.RBIP = 1)
    #define EXTI_RBx_SetAsLowPriority()         (INTCON2bits.RBIP = 0)
    #define EXTI_RBx_DeInitPriority()           (EXTI_RBx_SetAsLowPriority())

    #endif
#endif

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
void EXTI_INT0_ISR(void);
void EXTI_INT1_ISR(void);
void EXTI_INT2_ISR(void);
#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
void EXTI_RB4_RisingEdgeISR(void);
void EXTI_RB4_FallingEdgeISR(void);

void EXTI_RB5_RisingEdgeISR(void);
void EXTI_RB5_FallingEdgeISR(void);

void EXTI_RB6_RisingEdgeISR(void);
void EXTI_RB6_FallingEdgeISR(void);

void EXTI_RB7_RisingEdgeISR(void);
void EXTI_RB7_FallingEdgeISR(void);
#endif
#endif	/* _INTERRUPTS_PRIVATE_H_ */
