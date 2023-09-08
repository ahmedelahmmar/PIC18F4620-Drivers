/**
 * @file INTI.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.2
 * @date 01.08.23 
 */

#include "../Interrupts_Private.h"
#include "INTI.h"

void INTI_EnableInterrupts(void)
{
    #if (INTERRUPTS_PRIORITY_FEATURE == STD_OFF)
    INTERRUPTS_EnableAllGlobalInterrupts();
    INTERRUPTS_EnableAllPeripheralInterrupts();
    #else
    INTERRUPTS_EnablePriorityFeature();
    INTERRUPTS_EnableAllHighPriorityInterrupts();
    INTERRUPTS_EnableAllLowPriorityInterrupts();
    #endif
}

void INTI_DisableInterrupts(void)
{
    #if (INTERRUPTS_PRIORITY_FEATURE == STD_OFF)
    INTERRUPTS_DisableAllGlobalInterrupts();
    INTERRUPTS_DisableAllPeripheralInterrupts();
    #else
    INTERRUPTS_DisablePriorityFeature();
    INTERRUPTS_DisableAllHighPriorityInterrupts();
    INTERRUPTS_DisableAllLowPriorityInterrupts();
    #endif
}

uint8 INTI_GetInterruptStatus(void)
{
    return INTERRUPTS_GlobalInterruptsFlag();
}

void INTI_SetInterruptStatus(uint8 Status)
{
    switch (Status)
    {
        case 0:
        INTI_DisableInterrupts();
            break;

        case 1:
        INTI_EnableInterrupts();
            break;
    }
}

void INTI_ADC_ClearFlag(void)
{
    __INTI_ADC_ClearFlag();
}

uint8 INTI_ADC_Flag(void)
{
    return (__INTI_ADC_Flag());
}

#if (INTERRUPTS_ADC_INTERRUPTS_FEATURE == STD_ON)
void INTI_ADC_EnableInterrupt(void)
{
    __INTI_ADC_EnableInterrupt();
}

void INTI_ADC_DisableInterrupt(void)
{
    __INTI_ADC_DisableInterrupt();
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_ADC_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? __INTI_ADC_SetAsHighPriority() : __INTI_ADC_SetAsLowPriority();
    }

    void INTI_ADC_DeInitPriority(void)
    {
        __INTI_ADC_DeInitPriority();
    }
    #endif
#endif

void INTI_TIMER0_ClearFlag(void)
{
    __INTI_TIMER0_ClearFlag();
}

uint8 INTI_TIMER0_Flag(void)
{
    return (__INTI_TIMER0_Flag());
}

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
void INTI_TIMER0_EnableInterrupt(void)
{
    __INTI_TIMER0_EnableInterrupt();
}

void INTI_TIMER0_DisableInterrupt(void)
{
    __INTI_TIMER0_DisableInterrupt();
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_TIMER0_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? __INTI_TIMER0_SetAsHighPriority() : __INTI_TIMER0_SetAsLowPriority();
    }

    void INTI_TIMER0_DeInitPriority(void)
    {
        __INTI_TIMER0_DeInitPriority();
    }
    #endif
#endif

void INTI_TIMER1_ClearFlag(void)
{
    __INTI_TIMER1_ClearFlag();
}

uint8 INTI_TIMER1_Flag(void)
{
    return (__INTI_TIMER1_Flag());
}

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
void INTI_TIMER1_EnableInterrupt(void)
{
    __INTI_TIMER1_EnableInterrupt();
}

void INTI_TIMER1_DisableInterrupt(void)
{
    __INTI_TIMER1_DisableInterrupt();
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_TIMER1_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? __INTI_TIMER1_SetAsHighPriority() : __INTI_TIMER1_SetAsLowPriority();
    }

    void INTI_TIMER1_DeInitPriority(void)
    {
        __INTI_TIMER1_DeInitPriority();
    }
    #endif
#endif

void INTI_TIMER2_ClearFlag(void)
{
    __INTI_TIMER2_ClearFlag();
}

uint8 INTI_TIMER2_Flag(void)
{
    return (__INTI_TIMER2_Flag());
}

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
void INTI_TIMER2_EnableInterrupt(void)
{
    __INTI_TIMER2_EnableInterrupt();
}

void INTI_TIMER2_DisableInterrupt(void)
{
    __INTI_TIMER2_DisableInterrupt();
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_TIMER2_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? __INTI_TIMER2_SetAsHighPriority() : __INTI_TIMER2_SetAsLowPriority();
    }

    void INTI_TIMER2_DeInitPriority(void)
    {
        __INTI_TIMER2_DeInitPriority();
    }
    #endif
#endif

uint8 INTI_EUSART_TxFlag(void)
{
    return (__INTI_EUSART_TxFlag());
}

uint8 INTI_EUSART_RxFlag(void)
{
    return (__INTI_EUSART_RxFlag());
}

#if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)

    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
    void INTI_EUSART_EnableTxInterrupt(void)
    {
        __INTI_EUSART_EnableTxInterrupt();
    }

    void INTI_EUSART_DisableTxInterrupt(void)
    {
        __INTI_EUSART_DisableTxInterrupt();
    }

        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        void INTI_EUSART_SetTxPriority(INTERRUPTS_PriorityTypeDef loc_priority)
        {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? __INTI_EUSART_SetTxAsHighPriority() : __INTI_EUSART_SetTxAsLowPriority(); 
        }

        void INTI_EUSART_DeInitTxPriority(void)
        {
            __INTI_EUSART_DeInitTxPriority();
        }
        #endif
    #endif

    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
    void INTI_EUSART_EnableRxInterrupt(void)
    {
        __INTI_EUSART_EnableRxInterrupt();
    }
    void INTI_EUSART_DisableRxInterrupt(void)
    {
        __INTI_EUSART_DisableRxInterrupt();
    }

        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        void INTI_EUSART_SetRxPriority(INTERRUPTS_PriorityTypeDef loc_priority)
        {
            (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? __INTI_EUSART_SetRxAsHighPriority() : __INTI_EUSART_SetRxAsLowPriority();
        }

        void INTI_EUSART_DeInitRxPriority(void)
        {
            __INTI_EUSART_DeInitRxPriority();
        }
        #endif
    #endif  
#endif