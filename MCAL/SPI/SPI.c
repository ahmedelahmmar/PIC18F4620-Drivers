/**
 * @file SPI.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 19.09.23
 */

#include "SPI_Private.h"
#include "SPI.h"

#if (INTERRUPTS_SPI_INTERRUPTS_FEATURE == STD_ON)
static void (*SPI_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType SPI_InitInterruptHandler(const SPI_InitTypeDef * const InitPtr);
static void SPI_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType SPI_InitPriority(const SPI_InitTypeDef * const InitPtr);
    static void SPI_DeInitPriority(void);
    #endif
#endif

static Std_ReturnType SPI_InitPins(const SPI_InitTypeDef * const InitPtr);
static Std_ReturnType SPI_DeInitPins(const SPI_InitTypeDef * const InitPtr);

Std_ReturnType SPI_Init(const SPI_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __SPI_Disable();

        __SPI_ConfigMode(InitPtr->Mode);
        __SPI_ConfigClockPolarity(InitPtr->ClockPolarity);
        __SPI_ConfigSampleTime(InitPtr->SampleTime);
        __SPI_ConfigSetupTime(InitPtr->SetupTime);

        loc_ret |= SPI_InitPins(InitPtr);

        #if (INTERRUPTS_SPI_INTERRUPTS_FEATURE == STD_ON)
        INTI_SPI_EnableInterrupt();
        loc_ret |= SPI_InitInterruptHandler(InitPtr);
        #endif

        __SPI_Enable();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType SPI_DeInit(const SPI_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        __SPI_Disable();

        loc_ret |= SPI_DeInitPins(InitPtr);

        #if (INTERRUPTS_SPI_INTERRUPTS_FEATURE == STD_ON)
        INTI_SPI_DisableInterrupt();
        SPI_DeInitInterruptHandler();
        SPI_DeInitPriority();
        #endif
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}
Std_ReturnType SPI_SendData(const SPI_InitTypeDef * const InitPtr, const uint8 Data)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        uint8 loc_FlushByte;

        SSPBUF = Data;
        while (0 == INTI_SPI_Flag());

        loc_FlushByte = SSPBUF;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType SPI_ReadData(const SPI_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        SSPBUF = 0xFF; // Dummy Data

        while (0 == INTI_SPI_Flag());

        *DataBufferPtr = SSPBUF;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType SPI_ExchangeData(const SPI_InitTypeDef * const InitPtr, const uint8 Data, uint8 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        SSPBUF = Data;

        while (0 == INTI_SPI_Flag());

        *DataBufferPtr = SSPBUF;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType SPI_InitPins(const SPI_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        GPIO_InitTypeDef SDO = {
            .Pin = GPIO_PIN5,
            .Port = GPIO_PORTC,
            .Direction = GPIO_OUTPUT,
        };   

        GPIO_InitTypeDef SDI = {
            .Pin = GPIO_PIN4,
            .Port = GPIO_PORTC,
            .Direction = GPIO_INPUT,
        }; 

        GPIO_InitTypeDef CLK = {
            .Pin = GPIO_PIN3,
            .Port = GPIO_PORTC,
            .Direction = (InitPtr->Mode < SPI_MODE_SLAVE_SS_ENABLED) ? GPIO_OUTPUT : GPIO_INPUT,
        };

        if (InitPtr->Mode == SPI_MODE_SLAVE_SS_ENABLED)
        {
            GPIO_InitTypeDef SS = {
                .Pin = GPIO_PIN5,
                .Port = GPIO_PORTA,
                .Direction = GPIO_INPUT,
            };

            loc_ret |= GPIO_InitChannel(&SS);
        }

        loc_ret |= GPIO_InitChannel(&SDO);
        loc_ret |= GPIO_InitChannel(&SDI);
        loc_ret |= GPIO_InitChannel(&CLK);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType SPI_DeInitPins(const SPI_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        GPIO_InitTypeDef SDO = {
            .Pin = GPIO_PIN5,
            .Port = GPIO_PORTC,
        };  

        GPIO_InitTypeDef SDI = {
            .Pin = GPIO_PIN4,
            .Port = GPIO_PORTC,
        };

        GPIO_InitTypeDef CLK = {
            .Pin = GPIO_PIN3,
            .Port = GPIO_PORTC,
        };

        if (InitPtr->Mode == SPI_MODE_SLAVE_SS_ENABLED)
        {
            GPIO_InitTypeDef SS = {
                .Pin = GPIO_PIN5,
                .Port = GPIO_PORTA,
            };

            loc_ret |= GPIO_DeInitChannel(&SS);
        }

        loc_ret |= GPIO_DeInitChannel(&SDO);
        loc_ret |= GPIO_DeInitChannel(&SDI);
        loc_ret |= GPIO_DeInitChannel(&CLK);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_SPI_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType SPI_InitInterruptHandler(const SPI_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr->InterruptHandler)
    {
        SPI_InterruptHandler = InitPtr->InterruptHandler;
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static void SPI_DeInitInterruptHandler(void)
{
    SPI_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType SPI_InitPriority(const SPI_InitTypeDef * const InitPtr)
    {
        Std_ReturnType loc_ret = E_OK;

        if (InitPtr->Priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_SPI_SetPriority(InitPtr->Priority);
        }
        else 
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret;
    }
    
    static void SPI_DeInitPriority(void)
    {
        INTI_SPI_DeInitPriority();
    }
    #endif

void SPI_ISR(void)
{
    INTI_SPI_ClearFlag();

    if (NULL_PTR != SPI_InterruptHandler)
    {
        SPI_InterruptHandler();
    }
}
#endif