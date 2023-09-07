/**
 * @file Interrupts_Handler.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date 01.08.23
 */

#include "Interrupts_Private.h"
#include "Interrupts_Handler.h"

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
static volatile uint8 EXTI_RBx_Flags[NUMBER_OF_RBx_PINS] = {EXTI_RBx_FLAG_LOWERED};
#endif

#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
void __interrupt() HighPriorityInterruptHandler(void)
{    
 
}

void __interrupt(low_priority) LowPriorityInterruptHandler(void)
{

}

#elif (INTERRUPTS_PRIORITY_FEATURE == STD_OFF)

void __interrupt() InterruptHandler(void)
{   
    #if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
    if (INTI_TIMER0_Flag())
    {
        TIMER0_ISR();
    }
    #endif

    #if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
    if (INTI_TIMER1_Flag())
    {
        TIMER1_ISR();
    }
    #endif

    #if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
        #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
        if (INTI_EUSART_RxFlag())
        {
            EUSART_RX_ISR();
        }
        #endif

        #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
        if (INTI_EUSART_TxFlag())
        {
            EUSART_TX_ISR();
        }
        #endif
    #endif

    #if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
    if (EXTI_INT0_Flag())
    {
        EXTI_INT0_ISR();
    }
    
    if (EXTI_INT1_Flag())
    {
        EXTI_INT1_ISR();
    }
    
    if (EXTI_INT2_Flag())
    {
        EXTI_INT2_ISR();
    }
    #endif    

    #if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
    if (EXTI_RBx_Flag() && EXTI_RB4_RisingEdgeFlag() && (EXTI_RBx_FLAG_LOWERED == EXTI_RBx_Flags[EXTI_RB4]))
    {
        EXTI_RB4_RisingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB4] ^= 1;
    }
    
    if (EXTI_RBx_Flag() && EXTI_RB4_FallingEdgeFlag() && (EXTI_RBx_FLAG_RAISED == EXTI_RBx_Flags[EXTI_RB4]))
    {
        EXTI_RB4_FallingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB4] ^= 1;
    }
    
    if (EXTI_RBx_Flag() && EXTI_RB5_RisingEdgeFlag() && (EXTI_RBx_FLAG_LOWERED == EXTI_RBx_Flags[EXTI_RB5]))
    {
        EXTI_RB5_RisingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB5] ^= 1;
    }
    
    if (EXTI_RBx_Flag() && EXTI_RB5_FallingEdgeFlag() && (EXTI_RBx_FLAG_RAISED == EXTI_RBx_Flags[EXTI_RB5]))
    {
        EXTI_RB5_FallingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB5] ^= 1;
    }
    
    if (EXTI_RBx_Flag() && EXTI_RB6_RisingEdgeFlag() && (EXTI_RBx_FLAG_LOWERED == EXTI_RBx_Flags[EXTI_RB6]))
    {
        EXTI_RB6_RisingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB6] ^= 1;
    }
    
    if (EXTI_RBx_Flag() && EXTI_RB6_FallingEdgeFlag() && (EXTI_RBx_FLAG_RAISED == EXTI_RBx_Flags[EXTI_RB6]))
    {
        EXTI_RB6_FallingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB6] ^= 1;
    }
    
    if (EXTI_RBx_Flag() && EXTI_RB7_RisingEdgeFlag() && (EXTI_RBx_FLAG_LOWERED == EXTI_RBx_Flags[EXTI_RB7]))
    {
        EXTI_RB7_RisingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB7] ^= 1;
    }
    
    if (EXTI_RBx_Flag() && EXTI_RB7_FallingEdgeFlag() && (EXTI_RBx_FLAG_RAISED == EXTI_RBx_Flags[EXTI_RB7]))
    {
        EXTI_RB7_FallingEdgeISR();
        EXTI_RBx_Flags[EXTI_RB7] ^= 1;
    }
    #endif

    #if (INTERRUPTS_ADC_INTERRUPTS_FEATURE == STD_ON)
    if (INTI_ADC_Flag())
    {
        ADC_ISR();
    }
    #endif
}
#endif