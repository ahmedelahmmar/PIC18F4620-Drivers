/**
 * @file TIMER3.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 08.09.23
 */

#include "../Timers_Private.h"
#include "TIMER3.h"

static uint16 TIMER3_nRequiredInterrupts = 0;
static uint16 TIMER3_DelayValue = 0;
static const TIMER3_InitTypeDef * TIMER3_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
static void (*TIMER3_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType TIMER3_InitInterruptHandler(const TIMER3_InitTypeDef * const InitPtr);
static void TIMER3_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER3_InitPriority(const TIMER3_InitTypeDef * const InitPtr);
    static void TIMER3_DeInitPriority(void);
    #endif
#endif

static Std_ReturnType TIMER3_ConfigMode(const TIMER3_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER3_ConfigPrescaler(const TIMER3_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER3_ConfigTimerDelay(const TIMER3_InitTypeDef * const InitPtr, const uint32 loc_delay_ms);
static Std_ReturnType TIMER3_SetPreload(const TIMER3_InitTypeDef * const InitPtr, const uint16 loc_preload);

Std_ReturnType TIMER3_Init(const TIMER3_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {   
        __TIMER3_Disable();

        TIMER3_ObjBuffer = InitPtr;

        loc_ret = TIMER3_ConfigPrescaler(InitPtr);

        loc_ret |= TIMER3_ConfigMode(InitPtr);

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
        loc_ret |= TIMER3_InitInterruptHandler(InitPtr);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= TIMER3_InitPriority(InitPtr);
    #endif
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER3_DeInit(const TIMER3_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __TIMER3_Disable();
        TIMER3_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
        TIMER3_DeInitInterruptHandler();

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        TIMER3_DeInitPriority();
    #endif
        INTI_TIMER3_DisableInterrupt();
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER3_StartTimer(const TIMER3_InitTypeDef * const InitPtr, const uint32 delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (TIMER3_MODE_TIMER == InitPtr->Mode))
    {
        loc_ret = TIMER3_ConfigTimerDelay(InitPtr, delay_ms);

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
        INTI_TIMER3_ClearFlag();
        INTI_TIMER3_EnableInterrupt();
#endif
        __TIMER3_Enable();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER3_StartCounter(const TIMER3_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (TIMER3_MODE_COUNTER == InitPtr->Mode))
    {
        GPIO_InitTypeDef TIMER3_Channelx = {
            .Pin = GPIO_PIN0,
            .Port = GPIO_PORTC
        };

        loc_ret = GPIO_SetChannelDirection(&TIMER3_Channelx, GPIO_INPUT);

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
        INTI_TIMER3_ClearFlag();
        INTI_TIMER3_EnableInterrupt();
#endif
        __TIMER3_Enable();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER3_WriteCounterValue(const TIMER3_InitTypeDef * const InitPtr, const uint16 CounterValue)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret = TIMER3_SetPreload(InitPtr, CounterValue);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER3_ReadCounterValue(const TIMER3_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        *DataBufferPtr  = (uint8) __TIMER3_CounterRegisterLow();
        *DataBufferPtr |= (uint8)(__TIMER3_CounterRegisterHigh() << 8);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType TIMER3_InitInterruptHandler(const TIMER3_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr->InterruptHandler)
    {
        TIMER3_InterruptHandler = InitPtr->InterruptHandler;
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static void TIMER3_DeInitInterruptHandler(void)
{
    TIMER3_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER3_InitPriority(const TIMER3_InitTypeDef * const InitPtr)
    {
        Std_ReturnType loc_ret = E_OK;

        if (InitPtr->Priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_TIMER3_SetPriority(InitPtr->Priority);
        }
        else 
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;
    }
    
    static void TIMER3_DeInitPriority(void)
    {
        INTI_TIMER3_DeInitPriority();
    }
    #endif
#endif

static Std_ReturnType TIMER3_ConfigMode(const TIMER3_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Mode < TIMER3_MODE_LIMIT)
    {
        __TIMER3_ConfigMode(InitPtr->Mode);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER3_ConfigPrescaler(const TIMER3_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Prescaler < TIMER3_PRESCALER_LIMIT)
    {
        __TIMER3_ConfigPrescaler(InitPtr->Prescaler);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER3_ConfigTimerDelay(const TIMER3_InitTypeDef * const InitPtr, const uint32 loc_delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Prescaler < TIMER3_PRESCALER_LIMIT)
    {
        // FOSC/4 is the default clock for TIMER3 even with the prescaler disabled.
        uint16 loc_TickTime_us = (uint16)(((1 << InitPtr->Prescaler) * 4) / (uint32)(FOSC / 1000000UL));

        uint32 loc_TotalTicks = ((loc_delay_ms * 1000U) / loc_TickTime_us);

        TIMER3_nRequiredInterrupts = (uint16)(loc_TotalTicks / 65536U);
        TIMER3_DelayValue = (uint16)(65536U - (loc_TotalTicks % 65536U));

        if (0 != (loc_TotalTicks % 65536U)) ++TIMER3_nRequiredInterrupts;

        loc_ret |= TIMER3_SetPreload(InitPtr, TIMER3_DelayValue);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER3_SetPreload(const TIMER3_InitTypeDef * const InitPtr, uint16 loc_preload)
{
    Std_ReturnType loc_ret = E_OK;

    // Writing to TIMER3 counter register inhibits its operation for 2 clock cycles.
    loc_preload += 2;

    __TIMER3_CounterRegisterHigh() = (uint8)(loc_preload >> 8);
    __TIMER3_CounterRegisterLow() = (uint8)(loc_preload & 0xFF);

    return loc_ret;
}

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
void TIMER3_ISR(void)
{
    INTI_TIMER3_ClearFlag();

    static uint16 interruptCounter;

    if ((NULL_PTR != TIMER3_InterruptHandler) && (++interruptCounter == TIMER3_nRequiredInterrupts))
    {
        TIMER3_SetPreload(TIMER3_ObjBuffer, TIMER3_DelayValue);

        TIMER3_InterruptHandler();

        interruptCounter = 0;
    }
}
#endif