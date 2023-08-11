/**
 * @file EXTI.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date August 1, 2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Interrupts_Private.h"
#include "EXTI.h"

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
static void (*EXTI_INTx_InterruptHandlers[NUMBER_OF_INTx_PINS])(void) = {NULL};

static const uint8 EXTI_INTxPins[NUMBER_OF_INTx_PINS][2] = {{GPIO_PIN0, GPIO_PORTB},
                                                            {GPIO_PIN1, GPIO_PORTB},
                                                            {GPIO_PIN2, GPIO_PORTB}};
#endif
#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
static void (*EXTI_RBx_InterruptHandlers[NUMBER_OF_RBx_PINS][2])(void) = {NULL};

static const uint8 EXTI_RBxPins[NUMBER_OF_RBx_PINS][2] = {{GPIO_PIN4, GPIO_PORTB},
                                                          {GPIO_PIN5, GPIO_PORTB},
                                                          {GPIO_PIN6, GPIO_PORTB},
                                                          {GPIO_PIN7, GPIO_PORTB}};
#endif

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType EXTI_INTxDisableInterrupt(const EXTI_INTxInitTypeDef * const loc_INTx);
static Std_ReturnType EXTI_INTxEnableInterrupt(const EXTI_INTxInitTypeDef * const loc_INTx);

static Std_ReturnType EXTI_INTxClearFlag(const EXTI_INTxInitTypeDef * const loc_INTx);

static Std_ReturnType EXTI_INTxInitPin(const EXTI_INTxInitTypeDef * const loc_INTx);
static Std_ReturnType EXTI_INTxDeInitPin(const EXTI_INTxInitTypeDef * const loc_INTx);

static Std_ReturnType EXTI_INTxInitTrigger(const EXTI_INTxInitTypeDef * const loc_INTx);
static Std_ReturnType EXTI_INTxDeInitTrigger(const EXTI_INTxInitTypeDef * const loc_INTx);

static Std_ReturnType EXTI_INTxInitHandler(const EXTI_INTxInitTypeDef * const loc_INTx);
static Std_ReturnType EXTI_INTxDeInitHandler(const EXTI_INTxInitTypeDef * const loc_INTx);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType EXTI_INTxInitPriority(const EXTI_INTxInitTypeDef * const loc_INTx);
    static Std_ReturnType EXTI_INTxDeInitPriority(const EXTI_INTxInitTypeDef * const loc_INTx);
    #endif
#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType EXTI_RBxDisableInterrupt(const EXTI_RBxInitTypeDef * const loc_RBx);
static Std_ReturnType EXTI_RBxEnableInterrupt(const EXTI_RBxInitTypeDef * const loc_RBx);

static Std_ReturnType EXTI_RBxClearFlag(const EXTI_RBxInitTypeDef * const loc_RBx);

static Std_ReturnType EXTI_RBxInitPin(const EXTI_RBxInitTypeDef * const loc_RBx);
static Std_ReturnType EXTI_RBxDeInitPin(const EXTI_RBxInitTypeDef * const loc_RBx);

static Std_ReturnType EXTI_RBxInitHandler(const EXTI_RBxInitTypeDef * const loc_RBx);
static Std_ReturnType EXTI_RBxDeInitHandler(const EXTI_RBxInitTypeDef * const loc_RBx);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType EXTI_RBxInitPriority(const EXTI_RBxInitTypeDef * const loc_RBx);
    static Std_ReturnType EXTI_RBxDeInitPriority(const EXTI_RBxInitTypeDef * const loc_RBx);
    #endif  
#endif

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
Std_ReturnType EXTI_INTxInit(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_INTx)
    {
        loc_ret = EXTI_INTxDisableInterrupt(loc_INTx);
        
        loc_ret |= EXTI_INTxClearFlag(loc_INTx);
        
        loc_ret |= EXTI_INTxInitTrigger(loc_INTx);
              
        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= EXTI_INTxInitPriority(loc_INTx);
        #endif
        loc_ret |= EXTI_INTxInitHandler(loc_INTx);

        loc_ret |= EXTI_INTxInitPin(loc_INTx);
        
        loc_ret |= EXTI_INTxEnableInterrupt(loc_INTx);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType EXTI_INTxDeInit(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_INTx)
    {
        loc_ret = EXTI_INTxDisableInterrupt(loc_INTx);
        
        loc_ret |= EXTI_INTxDeInitTrigger(loc_INTx);
              
        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= EXTI_INTxDeInitPriority(loc_INTx);
        #endif
        loc_ret |= EXTI_INTxDeInitHandler(loc_INTx);

        loc_ret |= EXTI_INTxDeInitPin(loc_INTx);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;   
}
#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
Std_ReturnType EXTI_RBxInit(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_RBx)
    {
        loc_ret = EXTI_RBxDisableInterrupt(loc_RBx);
        
        loc_ret |= EXTI_RBxClearFlag(loc_RBx);

        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= EXTI_RBxInitPriority(loc_RBx);
        #endif
        loc_ret |= EXTI_RBxInitHandler(loc_RBx);

        loc_ret |= EXTI_RBxInitPin(loc_RBx);
        
        loc_ret |= EXTI_RBxEnableInterrupt(loc_RBx);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;    
}

Std_ReturnType EXTI_RBxDeInit(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_RBx)
    {
        loc_ret = EXTI_RBxDisableInterrupt(loc_RBx);
                    
        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= EXTI_RBxDeInitPriority(loc_RBx);
        #endif
        loc_ret |= EXTI_RBxDeInitHandler(loc_RBx);

        loc_ret |= EXTI_RBxDeInitPin(loc_RBx);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;  
}
#endif

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType EXTI_INTxDisableInterrupt(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_INTx)
    {
        switch(loc_INTx->INTx)
        {
            case EXTI_INT0:
                EXTI_INT0_DisableInterrupt();
                break;
                
            case EXTI_INT1:
                EXTI_INT1_DisableInterrupt();
                break;
                
            case EXTI_INT2:
                EXTI_INT2_DisableInterrupt();
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
static Std_ReturnType EXTI_INTxEnableInterrupt(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_INTx)
    {
        switch(loc_INTx->INTx)
        {
            case EXTI_INT0:
                EXTI_INT0_EnableInterrupt();
                break;
                
            case EXTI_INT1:
                EXTI_INT1_EnableInterrupt();
                break;
                
            case EXTI_INT2:
                EXTI_INT2_EnableInterrupt();
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

static Std_ReturnType EXTI_INTxClearFlag(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_INTx)
    {
        switch(loc_INTx->INTx)
        {
            case EXTI_INT0:
                EXTI_INT0_ClearFlag();
                break;
                
            case EXTI_INT1:
                EXTI_INT1_ClearFlag();
                break;
                
            case EXTI_INT2:
                EXTI_INT2_ClearFlag();
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

static Std_ReturnType EXTI_INTxInitPin(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_INTx) && (loc_INTx->INTx < NUMBER_OF_INTx_PINS))
    {
        GPIO_InitTypeDef loc_INTxChannel = {
          .Pin = EXTI_INTxPins[loc_INTx->INTx][EXTI_INTx_PIN],
          .Port = EXTI_INTxPins[loc_INTx->INTx][EXTI_INTx_PORT],
        };
        
        loc_ret = GPIO_SetChannelDirection(&loc_INTxChannel, GPIO_INPUT);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}
static Std_ReturnType EXTI_INTxDeInitPin(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_INTx) && (loc_INTx->INTx < NUMBER_OF_INTx_PINS))
    {
        GPIO_InitTypeDef loc_INTxChannel = {
          .Pin = EXTI_INTxPins[loc_INTx->INTx][EXTI_INTx_PIN],
          .Port = EXTI_INTxPins[loc_INTx->INTx][EXTI_INTx_PORT],
        };
        
        loc_ret = GPIO_DeInitChannel(&loc_INTxChannel);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

static Std_ReturnType EXTI_INTxInitTrigger(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_INTx)
    {
        switch(loc_INTx->INTx)
        {
            case EXTI_INT0:
                (EXTI_FALLING_EDGE == loc_INTx->Trigger) ? EXTI_INT0_SetTriggerAsFallingEdge() : EXTI_INT0_SetTriggerAsRisingEdge();
                break;
                
            case EXTI_INT1:
                (EXTI_FALLING_EDGE == loc_INTx->Trigger) ? EXTI_INT1_SetTriggerAsFallingEdge() : EXTI_INT1_SetTriggerAsRisingEdge();
                break;
                
            case EXTI_INT2:
                (EXTI_FALLING_EDGE == loc_INTx->Trigger) ? EXTI_INT2_SetTriggerAsFallingEdge() : EXTI_INT2_SetTriggerAsRisingEdge();
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
static Std_ReturnType EXTI_INTxDeInitTrigger(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_INTx)
    {
        switch(loc_INTx->INTx)
        {
            case EXTI_INT0:
                EXTI_INT0_DeInitTrigger();
                break;
                
            case EXTI_INT1:
                EXTI_INT1_DeInitTrigger();
                break;
                
            case EXTI_INT2:
                EXTI_INT2_DeInitTrigger();
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

static Std_ReturnType EXTI_INTxInitHandler(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_INTx) && (NULL != loc_INTx->InterruptHandler) && (loc_INTx->INTx < NUMBER_OF_INTx_PINS))
    {
        EXTI_INTx_InterruptHandlers[loc_INTx->INTx] = loc_INTx->InterruptHandler;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}
static Std_ReturnType EXTI_INTxDeInitHandler(const EXTI_INTxInitTypeDef * const loc_INTx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_INTx) && (loc_INTx->INTx < NUMBER_OF_INTx_PINS))
    {
        EXTI_INTx_InterruptHandlers[loc_INTx->INTx] = NULL;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType EXTI_INTxInitPriority(const EXTI_INTxInitTypeDef * const loc_INTx)
    {
        Std_ReturnType loc_ret = E_OK;

        if (NULL != loc_INTx)
        {
            switch(loc_INTx->INTx)
            {
//                case EXTI_INT0:
//                    (INTERRUPTS_HIGH_PRIORITY == loc_INTx->Priority) ? EXTI_INT0_SetAsHighPriority() : EXTI_INT0_SetAsLowPriority();
//                    break;

                case EXTI_INT1:
                    (INTERRUPTS_HIGH_PRIORITY == loc_INTx->Priority) ? EXTI_INT1_SetAsHighPriority() : EXTI_INT1_SetAsLowPriority();
                    break;

                case EXTI_INT2:
                    (INTERRUPTS_HIGH_PRIORITY == loc_INTx->Priority) ? EXTI_INT2_SetAsHighPriority() : EXTI_INT2_SetAsLowPriority();
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
    static Std_ReturnType EXTI_INTxDeInitPriority(const EXTI_INTxInitTypeDef * const loc_INTx)
    {
        Std_ReturnType loc_ret = E_OK;

        if (NULL != loc_INTx)
        {
            switch(loc_INTx->INTx)
            {
//                case EXTI_INT0:
//                    EXTI_INT0_DeInitPriority();
//                    break;

                case EXTI_INT1:
                    EXTI_INT1_DeInitPriority();
                    break;

                case EXTI_INT2:
                    EXTI_INT2_DeInitPriority();
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
    #endif
#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType EXTI_RBxDisableInterrupt(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_RBx)
    {
        EXTI_RBx_DisableInterrupt();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}
static Std_ReturnType EXTI_RBxEnableInterrupt(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_RBx)
    {
        EXTI_RBx_EnableInterrupt();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

static Std_ReturnType EXTI_RBxClearFlag(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_RBx)
    {
        EXTI_RBx_ClearFlag();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;    
}

static Std_ReturnType EXTI_RBxInitPin(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_RBx) && (loc_RBx->RBx < NUMBER_OF_RBx_PINS))
    {
        GPIO_InitTypeDef loc_RBxChannel = {
           .Pin = EXTI_RBxPins[loc_RBx->RBx][EXTI_RBx_PIN],
           .Port = EXTI_RBxPins[loc_RBx->RBx][EXTI_RBx_PORT]
        };
        
        loc_ret = GPIO_SetChannelDirection(&loc_RBxChannel, GPIO_INPUT);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}
static Std_ReturnType EXTI_RBxDeInitPin(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_RBx) && (loc_RBx->RBx < NUMBER_OF_RBx_PINS))
    {
        GPIO_InitTypeDef loc_RBxChannel = {
           .Pin = EXTI_RBxPins[loc_RBx->RBx][EXTI_RBx_PIN],
           .Port = EXTI_RBxPins[loc_RBx->RBx][EXTI_RBx_PORT]
        };
        
        loc_ret = GPIO_DeInitChannel(&loc_RBxChannel);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

static Std_ReturnType EXTI_RBxInitHandler(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_RBx) && (NULL != loc_RBx->RisingEdgeInterruptHandler) &&
        (NULL != loc_RBx->FallingEdgeInterruptHandler) && (loc_RBx->RBx < NUMBER_OF_RBx_PINS))
    {
        EXTI_RBx_InterruptHandlers[loc_RBx->RBx][EXTI_RBx_RISING_EDGE] = loc_RBx->RisingEdgeInterruptHandler;
        EXTI_RBx_InterruptHandlers[loc_RBx->RBx][EXTI_RBx_FALLING_EDGE] = loc_RBx->FallingEdgeInterruptHandler;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;   
}
static Std_ReturnType EXTI_RBxDeInitHandler(const EXTI_RBxInitTypeDef * const loc_RBx)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_RBx) && (loc_RBx->RBx < NUMBER_OF_RBx_PINS))
    {
        EXTI_RBx_InterruptHandlers[loc_RBx->RBx][EXTI_RBx_RISING_EDGE] = NULL;
        EXTI_RBx_InterruptHandlers[loc_RBx->RBx][EXTI_RBx_FALLING_EDGE] = NULL;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret; 
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType EXTI_RBxInitPriority(const EXTI_RBxInitTypeDef * const loc_RBx)
    {
        Std_ReturnType loc_ret = E_OK;

        if ((NULL != loc_RBx))
        {
            switch(loc_RBx->Priority)
            {
                case INTERRUPTS_LOW_PRIORITY:
                    EXTI_RBx_SetAsLowPriority();
                    break;
                    
                case INTERRUPTS_HIGH_PRIORITY:
                    EXTI_RBx_SetAsHighPriority();
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
    
    static Std_ReturnType EXTI_RBxDeInitPriority(const EXTI_RBxInitTypeDef * const loc_RBx)
    {
        Std_ReturnType loc_ret = E_OK;

        if ((NULL != loc_RBx))
        {
            EXTI_RBx_DeInitPriority();
        }
        else
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;   
    }
    #endif  
#endif

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
void EXTI_INT0_ISR(void)
{
    EXTI_INT0_ClearFlag();
    
    if (NULL != EXTI_INTx_InterruptHandlers[EXTI_INT0])
    {
        EXTI_INTx_InterruptHandlers[EXTI_INT0]();
    }
}

void EXTI_INT1_ISR(void)
{
    EXTI_INT1_ClearFlag();
    
    if (NULL != EXTI_INTx_InterruptHandlers[EXTI_INT1])
    {
        EXTI_INTx_InterruptHandlers[EXTI_INT1]();
    } 
}

void EXTI_INT2_ISR(void)
{
    EXTI_INT2_ClearFlag();
    
    if (NULL != EXTI_INTx_InterruptHandlers[EXTI_INT2])
    {
        EXTI_INTx_InterruptHandlers[EXTI_INT2]();
    }
}

#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
void EXTI_RB4_RisingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB4][EXTI_RBx_RISING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB4][EXTI_RBx_RISING_EDGE]();
    }
}
void EXTI_RB4_FallingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB4][EXTI_RBx_FALLING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB4][EXTI_RBx_FALLING_EDGE]();
    }
}

void EXTI_RB5_RisingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB5][EXTI_RBx_RISING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB5][EXTI_RBx_RISING_EDGE]();
    }    
}
void EXTI_RB5_FallingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB5][EXTI_RBx_FALLING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB5][EXTI_RBx_FALLING_EDGE]();
    }
}

void EXTI_RB6_RisingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB6][EXTI_RBx_RISING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB6][EXTI_RBx_RISING_EDGE]();
    }
}
void EXTI_RB6_FallingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB6][EXTI_RBx_FALLING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB6][EXTI_RBx_FALLING_EDGE]();
    }
}

void EXTI_RB7_RisingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB7][EXTI_RBx_RISING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB7][EXTI_RBx_RISING_EDGE]();
    }
}
void EXTI_RB7_FallingEdgeISR(void)
{
    EXTI_RBx_ClearFlag();
    
    if (NULL != EXTI_RBx_InterruptHandlers[EXTI_RB7][EXTI_RBx_FALLING_EDGE])
    {
        EXTI_RBx_InterruptHandlers[EXTI_RB7][EXTI_RBx_FALLING_EDGE]();
    }
}
#endif