/**
 * @file TIMER0.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.3
 * @date 22.08.23
 */

#include "../Timers_Private.h"
#include "TIMER0.h"

static uint16 TIMER0_nOverflows = 0;
static uint16 TIMER0_InitialPreload = 0;
static const TIMER0_InitTypeDef * TIMER0_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
static void (*TIMER0_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType TIMER0_InitInterruptHandler(const TIMER0_InitTypeDef * const InitPtr);
static void TIMER0_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER0_InitPriority(const TIMER0_InitTypeDef * const InitPtr);
    static void TIMER0_DeInitPriority(void);
    #endif
#endif

static Std_ReturnType TIMER0_ConfigResolution(const TIMER0_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER0_ConfigMode(const TIMER0_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER0_ConfigPrescaler(const TIMER0_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER0_ConfigTimerDelay(const TIMER0_InitTypeDef * const InitPtr, const uint32 loc_delay_ms);
static Std_ReturnType TIMER0_SetPreload(const TIMER0_InitTypeDef * const InitPtr, const uint16 loc_preload);

Std_ReturnType TIMER0_Init(const TIMER0_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {   
        __TIMER0_Disable();

        TIMER0_ObjBuffer = InitPtr;

        loc_ret = TIMER0_ConfigResolution(InitPtr);

        loc_ret |= TIMER0_ConfigPrescaler(InitPtr);

        loc_ret |= TIMER0_ConfigMode(InitPtr);

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
        loc_ret |= TIMER0_InitInterruptHandler(InitPtr);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= TIMER0_InitPriority(InitPtr);
    #endif
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER0_DeInit(const TIMER0_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __TIMER0_Disable();
        TIMER0_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
        TIMER0_DeInitInterruptHandler();

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        TIMER0_DeInitPriority();
    #endif
        INTI_TIMER0_DisableInterrupt();
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER0_StartTimer(const TIMER0_InitTypeDef * const InitPtr, const uint32 delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (TIMER0_MODE_TIMER == InitPtr->Mode))
    {
        loc_ret = TIMER0_ConfigTimerDelay(InitPtr, delay_ms);

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
        INTI_TIMER0_ClearFlag();
        INTI_TIMER0_EnableInterrupt();
#endif
        __TIMER0_Enable();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER0_StartCounter(const TIMER0_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (TIMER0_MODE_COUNTER == InitPtr->Mode))
    {
        GPIO_InitTypeDef TIMER0_Channelx = {
            .Pin = GPIO_PIN4,
            .Port = GPIO_PORTA
        };

        loc_ret = GPIO_SetChannelDirection(&TIMER0_Channelx, GPIO_INPUT);

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
        INTI_TIMER0_ClearFlag();
        INTI_TIMER0_EnableInterrupt();
#endif
        __TIMER0_Enable();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER0_WriteCounterValue(const TIMER0_InitTypeDef * const InitPtr, const uint16 CounterValue)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret = TIMER0_SetPreload(InitPtr, CounterValue);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER0_ReadCounterValue(const TIMER0_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        *DataBufferPtr = __TIMER0_CounterRegisterLow();
        
        if (TIMER0_RESOLUTION_16BIT == InitPtr->Resolution) *DataBufferPtr |= (__TIMER0_CounterRegisterHigh() << 8);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType TIMER0_InitInterruptHandler(const TIMER0_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr->InterruptHandler)
    {
        TIMER0_InterruptHandler = InitPtr->InterruptHandler;
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static void TIMER0_DeInitInterruptHandler(void)
{
    TIMER0_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER0_InitPriority(const TIMER0_InitTypeDef * const InitPtr)
    {
        Std_ReturnType loc_ret = E_OK;

        if (InitPtr->Priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_TIMER0_SetPriority(InitPtr->Priority);
        }
        else 
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;
    }
    
    static void TIMER0_DeInitPriority(void)
    {
        INTI_TIMER0_DeInitPriority();
    }
    #endif
#endif

static Std_ReturnType TIMER0_ConfigResolution(const TIMER0_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Resolution < TIMER0_RESOLUTION_LIMIT)
    {
        __TIMER0_ConfigResolution(InitPtr->Resolution);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER0_ConfigMode(const TIMER0_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Mode < TIMER0_MODE_LIMIT)
    {
        __TIMER0_ConfigMode(InitPtr->Mode);

        if ((TIMER0_MODE_COUNTER == InitPtr->Mode))
        {
            if ((InitPtr->EdgeSelect < TIMER0_SOURCE_EDGE_LIMIT)) __TIMER0_ConfigSourceEdge(InitPtr->EdgeSelect);
            else { loc_ret = E_NOT_OK; }
        }
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER0_ConfigPrescaler(const TIMER0_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((InitPtr->Prescaler < TIMER0_PRESCALER_LIMIT) || (TIMER0_NO_PRESCALER == InitPtr->Prescaler))
    {
        if (TIMER0_NO_PRESCALER == InitPtr->Prescaler)
        {
            __TIMER0_DisablePrescaler();
        }
        else
        {
            __TIMER0_ConfigPrescaler(InitPtr->Prescaler);
            __TIMER0_EnablePrescaler();
        }
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER0_ConfigTimerDelay(const TIMER0_InitTypeDef * const InitPtr, const uint32 loc_delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if ((InitPtr->Prescaler < TIMER0_PRESCALER_LIMIT) || (TIMER0_NO_PRESCALER == InitPtr->Prescaler))
    {
        uint16 loc_TickTime_us = 0;

        // FOSC/4 is the default clock for TIMER0 even with the prescaler disabled.

        if (TIMER0_NO_PRESCALER == InitPtr->Prescaler)
        {
            loc_TickTime_us = (uint16)(4 / (uint32)(FOSC / 1000000UL));
        }
        else
        {
            loc_TickTime_us = (uint16)(((uint16)(2 << InitPtr->Prescaler) * 4) / (uint32)(FOSC / 1000000UL));
        }

        uint32 loc_TotalTicks = ((loc_delay_ms * 1000U) / loc_TickTime_us);

        switch (InitPtr->Resolution)
        {
            case TIMER0_RESOLUTION_8BIT:
                TIMER0_nOverflows = (uint16)(loc_TotalTicks / 256U);
                TIMER0_InitialPreload = (uint16)(256U - (loc_TotalTicks % 256U));
                break;

            case TIMER0_RESOLUTION_16BIT:
                TIMER0_nOverflows = (uint16)(loc_TotalTicks / 65536U);
                TIMER0_InitialPreload = (uint16)(65536U - (loc_TotalTicks % 65536U));
                break;

            default:
                loc_ret = E_NOT_OK;
        }

        loc_ret |= TIMER0_SetPreload(InitPtr, TIMER0_InitialPreload);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER0_SetPreload(const TIMER0_InitTypeDef * const InitPtr, uint16 loc_preload)
{
    Std_ReturnType loc_ret = E_OK;

    // Writing to TIMER0 counter register inhibits its operation for 2 clock cycles.
    loc_preload += 2;

    switch (InitPtr->Resolution)
    {
        case TIMER0_RESOLUTION_8BIT:
            __TIMER0_CounterRegisterLow() = (uint8)(loc_preload & 0xFF);
            break;

        case TIMER0_RESOLUTION_16BIT:
            __TIMER0_CounterRegisterHigh() = (uint8)(loc_preload >> 8);
            __TIMER0_CounterRegisterLow() = (uint8)(loc_preload & 0xFF);
            break;

        default:
            loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
void TIMER0_ISR(void)
{
    INTI_TIMER0_ClearFlag();

    static uint16 overflowCounter;

    if ((NULL_PTR != TIMER0_InterruptHandler) && (overflowCounter++ == TIMER0_nOverflows))
    {
        TIMER0_SetPreload(TIMER0_ObjBuffer, TIMER0_InitialPreload);

        overflowCounter = 0;

        TIMER0_InterruptHandler();
    }
}
#endif