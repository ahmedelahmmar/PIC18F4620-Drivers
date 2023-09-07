/**
 * @file TIMER1.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 07.09.23
 */

#include "../Timers_Private.h"
#include "TIMER1.h"

static uint16 TIMER1_nOverflows = 0;
static uint16 TIMER1_InitialPreload = 0;
static const TIMER1_InitTypeDef * TIMER1_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
static void (*TIMER1_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType TIMER1_InitInterruptHandler(const TIMER1_InitTypeDef * const InitPtr);
static void TIMER1_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER1_InitPriority(const TIMER1_InitTypeDef * const InitPtr);
    static void TIMER1_DeInitPriority(void);
    #endif
#endif

static Std_ReturnType TIMER1_ConfigMode(const TIMER1_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER1_ConfigPrescaler(const TIMER1_InitTypeDef * const InitPtr);
static Std_ReturnType TIMER1_ConfigTimerDelay(const TIMER1_InitTypeDef * const InitPtr, const uint32 loc_delay_ms);
static Std_ReturnType TIMER1_SetPreload(const TIMER1_InitTypeDef * const InitPtr, const uint16 loc_preload);

Std_ReturnType TIMER1_Init(const TIMER1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {   
        __TIMER1_Disable();

        TIMER1_ObjBuffer = InitPtr;

        loc_ret = TIMER1_ConfigPrescaler(InitPtr);

        loc_ret |= TIMER1_ConfigMode(InitPtr);

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
        loc_ret |= TIMER1_InitInterruptHandler(InitPtr);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= TIMER1_InitPriority(InitPtr);
    #endif
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER1_DeInit(const TIMER1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __TIMER1_Disable();
        TIMER1_ObjBuffer = NULL_PTR;

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
        TIMER1_DeInitInterruptHandler();

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        TIMER1_DeInitPriority();
    #endif
        INTI_TIMER1_DisableInterrupt();
#endif   
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER1_StartTimer(const TIMER1_InitTypeDef * const InitPtr, const uint32 delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (TIMER1_MODE_TIMER == InitPtr->Mode))
    {
        loc_ret = TIMER1_ConfigTimerDelay(InitPtr, delay_ms);

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
        INTI_TIMER1_ClearFlag();
        INTI_TIMER1_EnableInterrupt();
#endif
        __TIMER1_Enable();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER1_StartCounter(const TIMER1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (TIMER1_MODE_COUNTER == InitPtr->Mode))
    {
        GPIO_InitTypeDef TIMER1_Channelx = {
            .Pin = GPIO_PIN0,
            .Port = GPIO_PORTC
        };

        loc_ret = GPIO_SetChannelDirection(&TIMER1_Channelx, GPIO_INPUT);

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
        INTI_TIMER1_ClearFlag();
        INTI_TIMER1_EnableInterrupt();
#endif
        __TIMER1_Enable();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER1_WriteCounterValue(const TIMER1_InitTypeDef * const InitPtr, const uint16 CounterValue)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret = TIMER1_SetPreload(InitPtr, CounterValue);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType TIMER1_ReadCounterValue(const TIMER1_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        *DataBufferPtr  = (uint8) __TIMER1_CounterRegisterLow();
        *DataBufferPtr |= (uint8)(__TIMER1_CounterRegisterHigh() << 8);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType TIMER1_InitInterruptHandler(const TIMER1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr->InterruptHandler)
    {
        TIMER1_InterruptHandler = InitPtr->InterruptHandler;
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static void TIMER1_DeInitInterruptHandler(void)
{
    TIMER1_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType TIMER1_InitPriority(const TIMER1_InitTypeDef * const InitPtr)
    {
        Std_ReturnType loc_ret = E_OK;

        if (InitPtr->Priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_TIMER1_SetPriority(InitPtr->Priority);
        }
        else 
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;
    }
    
    static void TIMER1_DeInitPriority(void)
    {
        INTI_TIMER1_DeInitPriority();
    }
    #endif
#endif

static Std_ReturnType TIMER1_ConfigMode(const TIMER1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Mode < TIMER1_MODE_LIMIT)
    {
        __TIMER1_ConfigMode(InitPtr->Mode);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER1_ConfigPrescaler(const TIMER1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Prescaler < TIMER1_PRESCALER_LIMIT)
    {
        __TIMER1_ConfigPrescaler(InitPtr->Prescaler);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER1_ConfigTimerDelay(const TIMER1_InitTypeDef * const InitPtr, const uint32 loc_delay_ms)
{
    Std_ReturnType loc_ret = E_OK;

    if (InitPtr->Prescaler < TIMER1_PRESCALER_LIMIT)
    {
        // FOSC/4 is the default clock for TIMER1 even with the prescaler disabled.
        uint16 loc_TickTime_us = (uint16)(((1 << InitPtr->Prescaler) * 4) / (uint32)(FOSC / 1000000UL));

        uint32 loc_TotalTicks = ((loc_delay_ms * 1000U) / loc_TickTime_us);

        TIMER1_nOverflows = (uint16)(loc_TotalTicks / 65536U);
        TIMER1_InitialPreload = (uint16)(65536U - (loc_TotalTicks % 65536U));

        loc_ret |= TIMER1_SetPreload(InitPtr, TIMER1_InitialPreload);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType TIMER1_SetPreload(const TIMER1_InitTypeDef * const InitPtr, uint16 loc_preload)
{
    Std_ReturnType loc_ret = E_OK;

    // Writing to TIMER1 counter register inhibits its operation for 2 clock cycles.
    loc_preload += 2;

    __TIMER1_CounterRegisterHigh() = (uint8)(loc_preload >> 8);
    __TIMER1_CounterRegisterLow() = (uint8)(loc_preload & 0xFF);

    return loc_ret;
}

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
void TIMER1_ISR(void)
{
    INTI_TIMER1_ClearFlag();

    static uint16 overflowCounter;

    if ((NULL_PTR != TIMER1_InterruptHandler) && (overflowCounter++ == TIMER1_nOverflows))
    {
        TIMER1_SetPreload(TIMER1_ObjBuffer, TIMER1_InitialPreload);

        overflowCounter = 0;

        TIMER1_InterruptHandler();
    }
}
#endif