/**
 * @file CCP2.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 10.09.23
 */

#include "../CCPx_Private.h"
#include "CCP2.h"

#if (INTERRUPTS_CCP2_INTERRUPTS_FEATURE == STD_ON)
static void (*CCP2_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType CCP2_InitInterruptHandler(const CCP2_InitTypeDef * const InitPtr);
static void CCP2_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType CCP2_InitPriority(const CCP2_InitTypeDef * const InitPtr);
    static void CCP2_DeInitPriority(void);
    #endif
#endif

Std_ReturnType CCP2_Init(const CCP2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP2_Disable();

        GPIO_InitTypeDef CCP2_Channelx = {
            .Pin = GPIO_PIN2,
            .Port = GPIO_PORTC,
        };

#if (CCP2_MODE == CCP2_CAPTURE_MODE)
        __CCPx_SelectTimerResource(InitPtr->CCPxTIMERx);
        CCP2_Channelx.Direction = GPIO_INPUT;

#elif (CCP2_MODE == CCP2_COMPARE_MODE)
        __CCPx_SelectTimerResource(InitPtr->CCPxTIMERx);
        CCP2_Channelx.Direction = GPIO_OUTPUT;

#elif (CCP2_MODE == CCP2_PWM_MODE)
        CCP2_Channelx.Direction = GPIO_OUTPUT;
#endif
        loc_ret |= GPIO_InitChannel(&CCP2_Channelx);

#if (INTERRUPTS_CCP2_INTERRUPTS_FEATURE == STD_ON)
        INTI_CCP2_EnableInterrupt();
        loc_ret |= CCP2_InitInterruptHandler(InitPtr);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= CCP2_InitPriority(InitPtr);
    #endif
#endif   
        __CCP2_ConfigMode(InitPtr->Mode);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType CCP2_DeInit(const CCP2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP2_Disable();

        GPIO_InitTypeDef CCP2_Channelx = {
            .Pin = GPIO_PIN2,
            .Port = GPIO_PORTC,
        };

        loc_ret |= GPIO_DeInitChannel(&CCP2_Channelx);

#if (INTERRUPTS_CCP2_INTERRUPTS_FEATURE == STD_ON)
        INTI_CCP2_DisableInterrupt();
        CCP2_DeInitInterruptHandler();

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        CCP2_DeInitPriority();
    #endif
#endif   
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;    
}

#if (CCP2_MODE == CCP2_CAPTURE_MODE)

Std_ReturnType CCP2_ReadCapture(const CCP2_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        *DataBufferPtr = (uint16)((uint16)(__CCP2_RegisterHigh() << 8) | (uint8)(__CCP2_RegisterLow()));
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;    
}

#elif (CCP2_MODE == CCP2_COMPARE_MODE)

Std_ReturnType CCP2_WriteCompareValue(const CCP2_InitTypeDef * const InitPtr, const uint16 CompareValue)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP2_RegisterLow() = (uint8)(CompareValue & 0xFF);
        __CCP2_RegisterHigh() = (uint8)(CompareValue >> 8);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;  
}

#elif (CCP2_MODE == CCP2_PWM_MODE)

Std_ReturnType CCP2_PWM_SetFrequency(const CCP2_InitTypeDef * const InitPtr, const uint32 Frequency)
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

Std_ReturnType CCP2_PWM_SetDutyCycle(const CCP2_InitTypeDef * const InitPtr, const uint8 DutyCycle)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (DutyCycle <= 100))
    {
        uint16 loc_DutyCycleValue = (uint16)(4 * (PR2 + 1) * (DutyCycle / 100.0));

        __CCP2_SetDutyCycleLower2Bits(loc_DutyCycleValue & 0x03);

        __CCP2_RegisterLow() = (uint8)(loc_DutyCycleValue >> 2);
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret; 
}

Std_ReturnType CCP2_PWM_Start(const CCP2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP2_ConfigMode(InitPtr->Mode);
        __CCPx_EnableTimer2();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret; 
}

Std_ReturnType CCP2_PWM_Stop(const CCP2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __CCP2_Disable();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret; 
}
#endif

#if (INTERRUPTS_CCP2_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType CCP2_InitInterruptHandler(const CCP2_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr->InterruptHandler)
    {
        CCP2_InterruptHandler = InitPtr->InterruptHandler;
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}
static void CCP2_DeInitInterruptHandler(void)
{
    CCP2_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType CCP2_InitPriority(const CCP2_InitTypeDef * const InitPtr)
    {
        Std_ReturnType loc_ret = E_OK;

        if (InitPtr->Priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_CCP2_SetPriority(InitPtr->Priority);
        }
        else 
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;
    }
    static void CCP2_DeInitPriority(void)
    {
        INTI_CCP2_DeInitPriority();
    }
    #endif

void CCP2_ISR(void)
{
    INTI_CCP2_ClearFlag();
    
    if (NULL_PTR != CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
}
#endif