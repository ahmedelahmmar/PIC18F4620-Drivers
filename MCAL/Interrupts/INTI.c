/**
 * @file INTI.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.2
 * @date 01.08.23 
 */

#include "Interrupts_Private.h"
#include "INTI.h"

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
void INTI_ADC_EnableInterrupt(void)
{
    INTI_ADC_EnableInterrupt_();
}

void INTI_ADC_DisableInterrupt(void)
{
    INTI_ADC_DisableInterrupt_();
}

void INTI_ADC_ClearFlag(void)
{
    INTI_ADC_ClearFlag_();
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    void INTI_ADC_SetPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        (INTERRUPTS_HIGH_PRIORITY == loc_priority) ? INTI_ADC_SetAsHighPriority_() : INTI_ADC_SetAsLowPriority_();
    }

    void INTI_ADC_DeInitPriority(void)
    {
        INTI_ADC_DeInitPriority_();
    }
    #endif
#endif