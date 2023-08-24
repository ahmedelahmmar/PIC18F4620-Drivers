/**
 * @file INTI.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.2
 * @date 01.08.23 
 */

#include "Interrupts_Private.h"
#include "INTI.h"

void INTI_ADC_ClearFlag(void)
{
    INTI_ADC_PrivClearFlag();
}

uint8 INTI_ADC_Flag(void)
{
    return (INTI_ADC_PrivFlag());
}

#if (INTERRUPTS_ADC_INTERRUPTS_FEATURE == STD_ON)
void INTI_ADC_EnableInterrupt(void)
{
    INTI_ADC_PrivEnableInterrupt();
}

void INTI_ADC_DisableInterrupt(void)
{
    INTI_ADC_PrivDisableInterrupt();
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_ADC_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? INTI_ADC_PrivSetAsHighPriority() : INTI_ADC_PrivSetAsLowPriority();
    }

    void INTI_ADC_DeInitPriority(void)
    {
        INTI_ADC_PrivDeInitPriority();
    }
    #endif
#endif

void INTI_TIMER0_ClearFlag(void)
{
    INTI_TIMER0_PrivClearFlag();
}

uint8 INTI_TIMER0_Flag(void)
{
    return (INTI_TIMER0_PrivFlag());
}

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
void INTI_TIMER0_EnableInterrupt(void)
{
    INTI_TIMER0_PrivEnableInterrupt();
}

void INTI_TIMER0_DisableInterrupt(void)
{
    INTI_TIMER0_PrivDisableInterrupt();
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_TIMER0_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? INTI_TIMER0_PrivSetAsHighPriority() : INTI_TIMER0_PrivSetAsLowPriority();
    }

    void INTI_TIMER0_DeInitPriority(void)
    {
        INTI_TIMER0_PrivDeInitPriority();
    }
    #endif
#endif

uint8 INTI_EUSART_TxFlag(void)
{
    return (INTI_EUSART_PrivTxFlag());
}

uint8 INTI_EUSART_RxFlag(void)
{
    return (INTI_EUSART_PrivRxFlag());
}

#if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)

    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
    void INTI_EUSART_EnableTxInterrupt(void)
    {
        INTI_EUSART_PrivEnableTxInterrupt();
    }

    void INTI_EUSART_DisableTxInterrupt(void)
    {
        INTI_EUSART_PrivDisableTxInterrupt();
    }

        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        void INTI_EUSART_SetTxPriority(INTERRUPTS_PriorityTypeDef loc_priority)
        {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? INTI_EUSART_PrivSetTxAsHighPriority() : INTI_EUSART_PrivSetTxAsLowPriority(); 
        }

        void INTI_EUSART_DeInitTxPriority(void)
        {
            INTI_EUSART_PrivDeInitTxPriority();
        }
        #endif
    #endif

    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
    void INTI_EUSART_EnableRxInterrupt(void)
    {
        INTI_EUSART_PrivEnableRxInterrupt();
    }
    void INTI_EUSART_DisableRxInterrupt(void)
    {
        INTI_EUSART_PrivDisableRxInterrupt();
    }

        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        void INTI_EUSART_SetRxPriority(INTERRUPTS_PriorityTypeDef loc_priority)
        {
            (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? INTI_EUSART_PrivSetRxAsHighPriority() : INTI_EUSART_PrivSetRxAsLowPriority();
        }

        void INTI_EUSART_DeInitRxPriority(void)
        {
            INTI_EUSART_PrivDeInitRxPriority();
        }
        #endif
    #endif  
#endif