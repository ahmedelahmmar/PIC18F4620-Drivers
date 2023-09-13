/**
 * @file CCP1.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 10.09.23
 */

#include "../CCPx_Private.h"
#include "CCP1.h"

#if (INTERRUPTS_CCP1_INTERRUPTS_FEATURE == STD_ON)
static void (*CCP1_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType CCP1_InitInterruptHandler(const CCP1_InitTypeDef * const InitPtr);
static void CCP1_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType CCP1_InitPriority(const CCP1_InitTypeDef * const InitPtr);
    static void CCP1_DeInitPriority(void);
    #endif
#endif

Std_ReturnType CCP1_Init(const CCP1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP1_Disable();

        GPIO_InitTypeDef CCP1_Channelx = {
            .Pin = GPIO_PIN2,
            .Port = GPIO_PORTC,
        };

#if (CCP1_MODE == CCP1_CAPTURE_MODE)
        __CCPx_SelectTimerResource(InitPtr->CCPxTIMERx);
        CCP1_Channelx.Direction = GPIO_INPUT;

#elif (CCP1_MODE == CCP1_COMPARE_MODE)
        __CCPx_SelectTimerResource(InitPtr->CCPxTIMERx);
        CCP1_Channelx.Direction = GPIO_OUTPUT;

#elif (CCP1_MODE == CCP1_PWM_MODE)
        CCP1_Channelx.Direction = GPIO_OUTPUT;
#endif
        loc_ret |= GPIO_InitChannel(&CCP1_Channelx);

#if (INTERRUPTS_CCP1_INTERRUPTS_FEATURE == STD_ON)
        INTI_CCP1_EnableInterrupt();
        loc_ret |= CCP1_InitInterruptHandler(InitPtr);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= CCP1_InitPriority(InitPtr);
    #endif
#endif   
        __CCP1_ConfigMode(InitPtr->Mode);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType CCP1_DeInit(const CCP1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP1_Disable();

        GPIO_InitTypeDef CCP1_Channelx = {
            .Pin = GPIO_PIN2,
            .Port = GPIO_PORTC,
        };

        loc_ret |= GPIO_DeInitChannel(&CCP1_Channelx);

#if (INTERRUPTS_CCP1_INTERRUPTS_FEATURE == STD_ON)
        INTI_CCP1_DisableInterrupt();
        CCP1_DeInitInterruptHandler();

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        CCP1_DeInitPriority();
    #endif
#endif   
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;    
}

#if (CCP1_MODE == CCP1_CAPTURE_MODE)

Std_ReturnType CCP1_ReadCapture(const CCP1_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        *DataBufferPtr = (uint16)((uint16)(__CCP1_RegisterHigh() << 8) | (uint8)(__CCP1_RegisterLow()));
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;    
}

#elif (CCP1_MODE == CCP1_COMPARE_MODE)

Std_ReturnType CCP1_WriteCompareValue(const CCP1_InitTypeDef * const InitPtr, const uint16 CompareValue)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP1_RegisterLow() = (uint8)(CompareValue & 0xFF);
        __CCP1_RegisterHigh() = (uint8)(CompareValue >> 8);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;  
}

#elif (CCP1_MODE == CCP1_PWM_MODE)

Std_ReturnType CCP1_PWM_SetFrequency(const CCP1_InitTypeDef * const InitPtr, const uint32 Frequency)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        uint8 loc_Timer2PrescalerValue = (TIMER2_NO_PRESCALER == InitPtr->TIMER2Ptr->Prescaler) ? (uint8)(1) : (uint8)(2 << InitPtr->TIMER2Ptr->Prescaler);
        uint8 loc_Timer2PostscalerValue = InitPtr->TIMER2Ptr->Postscaler + 1;
        uint8 loc_value = (uint8)(((uint32)FOSC / (uint32)(4 * Frequency * loc_Timer2PrescalerValue)) - 1);
        
        TIMER2_WriteCompareValue(InitPtr->TIMER2Ptr, loc_value);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;  
}

Std_ReturnType CCP1_PWM_SetDutyCycle(const CCP1_InitTypeDef * const InitPtr, const uint8 DutyCycle)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (DutyCycle <= 100))
    {
        uint16 loc_DutyCycleValue = (uint16)(4 * (PR2 + 1) * (DutyCycle / 100.0));

        __CCP1_SetDutyCycleLower2Bits(loc_DutyCycleValue & 0x03);

        __CCP1_RegisterLow() = (uint8)(loc_DutyCycleValue >> 2);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret; 
}

Std_ReturnType CCP1_PWM_Start(const CCP1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP1_ConfigMode(InitPtr->Mode);
        __CCPx_EnableTimer2();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret; 
}

Std_ReturnType CCP1_PWM_Stop(const CCP1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP1_Disable();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret; 
}
#endif

#if (INTERRUPTS_CCP1_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType CCP1_InitInterruptHandler(const CCP1_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr->InterruptHandler)
    {
        CCP1_InterruptHandler = InitPtr->InterruptHandler;
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}
static void CCP1_DeInitInterruptHandler(void)
{
    CCP1_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType CCP1_InitPriority(const CCP1_InitTypeDef * const InitPtr)
    {
        Std_ReturnType loc_ret = E_OK;

        if (InitPtr->Priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_CCP1_SetPriority(InitPtr->Priority);
        }
        else 
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;
    }
    static void CCP1_DeInitPriority(void)
    {
        INTI_CCP1_DeInitPriority();
    }
    #endif

void CCP1_ISR(void)
{
    INTI_CCP1_ClearFlag();
    
    if (NULL_PTR != CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
}
#endif