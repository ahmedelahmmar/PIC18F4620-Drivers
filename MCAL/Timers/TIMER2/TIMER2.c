/**
 * @file TIMER2.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 08.09.23
 */

#include "../Timers_Private.h"
#include "TIMER2.h"

static uint8  TIMER2_DelayValue = 0;
static uint16 TIMER2_nRequiredInterrupts = 0;

static const TIMER2_InitTypeDef * TIMER2_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
static void (*TIMER2_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType TIMER2_InitInterruptHandler(const TIMER2_InitTypeDef * const InitPtr);
static void TIMER2_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER2_InitPriority(const TIMER2_InitTypeDef * const InitPtr);
    static void TIMER2_DeInitPriority(void);
    #endif
#endif

static Std_ReturnType TIMER2_ConfigPrescaler(const TIMER2_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER2_ConfigPostscaler(const TIMER2_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER2_ConfigTimerDelay(const TIMER2_InitTypeDef * const InitPtr, const uint32 loc_delay_ms);
static Std_ReturnType TIMER2_SetPreload(const TIMER2_InitTypeDef * const InitPtr, const uint8 loc_preload);
static Std_ReturnType TIMER2_SetCompareValue(const TIMER2_InitTypeDef * const InitPtr, const uint8 loc_compareValue);

Std_ReturnType TIMER2_Init(const TIMER2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {   
        __TIMER2_Disable();

        TIMER2_ObjBuffer = InitPtr;

        loc_ret = TIMER2_ConfigPrescaler(InitPtr);

        loc_ret |= TIMER2_ConfigPostscaler(InitPtr);

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
        loc_ret |= TIMER2_InitInterruptHandler(InitPtr);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= TIMER2_InitPriority(InitPtr);
    #endif
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER2_DeInit(const TIMER2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __TIMER2_Disable();
        TIMER2_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
        TIMER2_DeInitInterruptHandler();

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        TIMER2_DeInitPriority();
    #endif
        INTI_TIMER2_DisableInterrupt();
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER2_StartTimer(const TIMER2_InitTypeDef * const InitPtr, const uint32 delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret = TIMER2_ConfigTimerDelay(InitPtr, delay_ms);

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
        INTI_TIMER2_ClearFlag();
        INTI_TIMER2_EnableInterrupt();
#endif
        __TIMER2_Enable();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER2_WriteCounterValue(const TIMER2_InitTypeDef * const InitPtr, const uint8 CounterValue)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret = TIMER2_SetPreload(InitPtr, CounterValue);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER2_ReadCounterValue(const TIMER2_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        *DataBufferPtr = (uint8) __TIMER2_CounterRegister();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER2_WriteCompareValue(const TIMER2_InitTypeDef * const InitPtr, uint8 CompareValue)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret = TIMER2_SetCompareValue(InitPtr, CompareValue);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER2_ReadCompareValue(const TIMER2_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        *DataBufferPtr = (uint8) __TIMER2_CompareRegister();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType TIMER2_InitInterruptHandler(const TIMER2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr->InterruptHandler)
    {
        TIMER2_InterruptHandler = InitPtr->InterruptHandler;
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static void TIMER2_DeInitInterruptHandler(void)
{
    TIMER2_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER2_InitPriority(const TIMER2_InitTypeDef * const InitPtr)
    {
        Std_ReturnType loc_ret = E_OK;

        if (InitPtr->Priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_TIMER2_SetPriority(InitPtr->Priority);
        }
        else 
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;
    }
    
    static void TIMER2_DeInitPriority(void)
    {
        INTI_TIMER2_DeInitPriority();
    }
    #endif
#endif

static Std_ReturnType TIMER2_ConfigPrescaler(const TIMER2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Prescaler < TIMER2_PRESCALER_LIMIT)
    {
        __TIMER2_ConfigPrescaler(InitPtr->Prescaler);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER2_ConfigPostscaler(const TIMER2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Postscaler < TIMER2_POSTSCALER_LIMIT)
    {
        __TIMER2_ConfigPostscaler(InitPtr->Postscaler);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER2_ConfigTimerDelay(const TIMER2_InitTypeDef * const InitPtr, const uint32 loc_delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Mode < TIMER2_MODE_LIMIT)
    {
        // FOSC/4 is the default clock for TIMER2 even with the prescaler disabled.
        uint8 loc_PrescalerValue = (TIMER2_NO_PRESCALER == InitPtr->Prescaler) ? (uint8)(1) : (uint8)(2 << InitPtr->Prescaler);

        uint16 loc_TickTime_us = (uint16)((loc_PrescalerValue * (InitPtr->Postscaler + 1) * 4) / (uint32)(FOSC / 1000000UL));
        uint32 loc_TotalTicks = ((loc_delay_ms * 1000U) / loc_TickTime_us);

        switch (InitPtr->Mode)
        {
            case TIMER2_MODE_NORMAL:  

                TIMER2_nRequiredInterrupts = (uint16)(loc_TotalTicks / 256U);
                TIMER2_DelayValue = (uint8)(256U - (loc_TotalTicks % 256U));

                loc_ret |= TIMER2_SetPreload(InitPtr, TIMER2_DelayValue);
                loc_ret |= TIMER2_SetCompareValue(InitPtr, 0xFF);

                break;

            case TIMER2_MODE_COMPARE_MATCH:;

                uint8 loc_divFactor = 0xFF;

                while (loc_TotalTicks % loc_divFactor) --loc_divFactor;

                TIMER2_nRequiredInterrupts = (uint16)(loc_TotalTicks / loc_divFactor);
                TIMER2_DelayValue = (uint8)(loc_divFactor - 1);

                loc_ret |= TIMER2_SetPreload(InitPtr, 0);
                loc_ret |= TIMER2_SetCompareValue(InitPtr, TIMER2_DelayValue);

                break;

            default:
                loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER2_SetPreload(const TIMER2_InitTypeDef * const InitPtr, uint8 loc_preload)
{
    Std_ReturnType loc_ret = E_OK;

    // Writing to TIMER2 counter register inhibits its operation for 2 clock cycles.
    __TIMER2_CounterRegister() = loc_preload + 2;

    return loc_ret;
}

static Std_ReturnType TIMER2_SetCompareValue(const TIMER2_InitTypeDef * const InitPtr, uint8 loc_compareValue)
{
    Std_ReturnType loc_ret = E_OK;

    __TIMER2_CompareRegister() = loc_compareValue;

    return loc_ret;
}

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
void TIMER2_ISR(void)
{
    INTI_TIMER2_ClearFlag();

    static uint16 interruptCounter;

    if ((NULL_PTR != TIMER2_InterruptHandler) && (interruptCounter++ == TIMER2_nRequiredInterrupts))
    {
        TIMER2_SetPreload(TIMER2_ObjBuffer, TIMER2_DelayValue);

        TIMER2_InterruptHandler();

        interruptCounter = 0;
    }
}
#endif