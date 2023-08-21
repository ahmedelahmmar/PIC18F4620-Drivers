/**
 * @file ADC.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 17.08.23
 */

#include "ADC_Private.h"
#include "ADC.h"

static const uint8 ADC_ChannelPins[ADC_CHANNEL_LIMIT][2] = {{GPIO_PIN0, GPIO_PORTA}, //AN0
                                                            {GPIO_PIN1, GPIO_PORTA}, //AN1
                                                            {GPIO_PIN2, GPIO_PORTA}, //AN2
                                                            {GPIO_PIN3, GPIO_PORTA}, //AN3
                                                            {GPIO_PIN5, GPIO_PORTA}, //AN4
                                                            {GPIO_PIN0, GPIO_PORTE}, //AN5
                                                            {GPIO_PIN1, GPIO_PORTE}, //AN6
                                                            {GPIO_PIN2, GPIO_PORTE}, //AN7
                                                            {GPIO_PIN2, GPIO_PORTB}, //AN8
                                                            {GPIO_PIN3, GPIO_PORTB}, //AN9
                                                            {GPIO_PIN1, GPIO_PORTB}, //AN10
                                                            {GPIO_PIN4, GPIO_PORTB}, //AN11
                                                            {GPIO_PIN0, GPIO_PORTB}}; // AN12

static Std_ReturnType ADC_InitAnalogDigitalChannels(ADC_ChannelConfigTypeDef loc_channelConfig);
static Std_ReturnType ADC_InitVrefSource(ADC_VrefTypeDef loc_vref);
static Std_ReturnType ADC_InitChannelSource(ADC_ChannelTypeDef loc_channel);
static Std_ReturnType ADC_InitAquisitionTimePeriod(ADC_AquisitionTimeTypeDef loc_aqt);
static Std_ReturnType ADC_InitPrescalerValue(ADC_PrescalerTypeDef loc_prescaler);
static Std_ReturnType ADC_InitAlignment(ADC_ResultAlignmentTypeDef loc_allignment);

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
static void (*ADC_InterruptHandler)(void) = NULL_PTR;

static Std_ReturnType ADC_InitInterruptHandler(void (*loc_interruptHandler)(void));
static void ADC_DeInitInterruptHandler(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType ADC_InitPriority(INTERRUPTS_PriorityTypeDef);
    static void ADC_DeInitPriority(void);
    #endif
#endif

Std_ReturnType ADC_Init(const ADC_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        ADC_Disable();
        
        loc_ret = ADC_InitAnalogDigitalChannels(InitPtr->ChannelConfiguration);

        loc_ret |= ADC_InitVrefSource(InitPtr->Vref);

        loc_ret |= ADC_InitAquisitionTimePeriod(InitPtr->AquisitionTime);

        loc_ret |= ADC_InitPrescalerValue(InitPtr->Prescaler);

        loc_ret |= ADC_InitAlignment(InitPtr->ResultAlignment);

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
        INTI_ADC_EnableInterrupt();
        loc_ret |= ADC_InitInterruptHandler(InitPtr->InterruptHandler);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        loc_ret |= ADC_InitPriority(InitPtr->Priority);
    #endif
#endif
        ADC_Enable();
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType ADC_DeInit(void)
{
    Std_ReturnType loc_ret = E_OK;
    
    ADC_Disable();

    uint8 ADC_ChannelIterator;
    GPIO_InitTypeDef ADC_Channelx;

    for (ADC_ChannelIterator = 0; ADC_ChannelIterator < ADC_CHANNEL_LIMIT; ++ADC_ChannelIterator)
    {
        ADC_Channelx.Pin = ADC_ChannelPins[ADC_ChannelIterator][ADC_CHANNEL_PIN];
        ADC_Channelx.Port = ADC_ChannelPins[ADC_ChannelIterator][ADC_CHANNEL_PORT];

        loc_ret |= GPIO_DeInitChannel(&ADC_Channelx);
    }

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
    INTI_ADC_DisableInterrupt();
    ADC_DeInitInterruptHandler();

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    ADC_DeInitPriority();
    #endif
#endif
    return loc_ret;
}

Std_ReturnType ADC_StartConversion(const ADC_ChannelTypeDef Channel)
{
    Std_ReturnType loc_ret = E_OK;

    loc_ret = ADC_InitChannelSource(Channel);

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
        INTI_ADC_ClearFlag();
#endif
        ADC_StartConverting();

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_OFF)
        while (ADC_isConverting());
#endif

    return loc_ret;
}

Std_ReturnType ADC_Read(const ADC_InitTypeDef * const InitPtr, ADC_ValueTypeDef * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != DataBufferPtr))
    {
        switch (InitPtr->ResultAlignment)
        {
            case ADC_ALIGN_LEFT:
                *DataBufferPtr = (ADC_ValueTypeDef)(((ADC_ResultHighRegister & 0xC0) << 2) | (ADC_ResultHighRegister << 2) | (ADC_ResultLowRegister >> 6));
                break;

            case ADC_ALIGN_RIGHT:
                *DataBufferPtr = (ADC_ValueTypeDef)((ADC_ResultHighRegister << 8) | ADC_ResultLowRegister);
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

static Std_ReturnType ADC_InitAnalogDigitalChannels(ADC_ChannelConfigTypeDef loc_channelConfig)
{
    Std_ReturnType loc_ret = E_OK;

    if (loc_channelConfig < ADC_CHANNEL_CONFIG_LIMIT)
    {
        ADC_ConfigChannel(loc_channelConfig);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType ADC_InitVrefSource(ADC_VrefTypeDef loc_vref)
{
    Std_ReturnType loc_ret = E_OK;

    if ((ADC_VREF_INTERNAL == loc_vref) || (ADC_VREF_EXTERNAL == loc_vref))
    {
        ADC_ConfigVref(loc_vref);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType ADC_InitChannelSource(ADC_ChannelTypeDef loc_channel)
{
    Std_ReturnType loc_ret = E_OK;

    if (loc_channel < ADC_CHANNEL_LIMIT)
    {   
        ADC_SelectChannel(loc_channel);

        GPIO_InitTypeDef ADC_Channelx = {
            .Pin = ADC_ChannelPins[loc_channel][ADC_CHANNEL_PIN],
            .Port = ADC_ChannelPins[loc_channel][ADC_CHANNEL_PORT]
        };

        loc_ret = GPIO_SetChannelDirection(&ADC_Channelx, GPIO_INPUT);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType ADC_InitAquisitionTimePeriod(ADC_AquisitionTimeTypeDef loc_aqt)
{
    Std_ReturnType loc_ret = E_OK;

    if (loc_aqt < ADC_AQT_LIMIT)
    {
        ADC_ConfigAquisitionTime(loc_aqt);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType ADC_InitPrescalerValue(ADC_PrescalerTypeDef loc_prescaler)
{
    Std_ReturnType loc_ret = E_OK;

    if (loc_prescaler < ADC_PRESCALER_LIMIT)
    {
        ADC_ConfigPrescaler(loc_prescaler);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType ADC_InitAlignment(ADC_ResultAlignmentTypeDef loc_allignment)
{
    Std_ReturnType loc_ret = E_OK;

    if ((ADC_ALIGN_LEFT == loc_allignment) || (ADC_ALIGN_RIGHT == loc_allignment))
    {
        ADC_ConfigAlignment(loc_allignment);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
static Std_ReturnType ADC_InitInterruptHandler(void (*loc_interruptHandler)(void))
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != loc_interruptHandler)
    {
        ADC_InterruptHandler = loc_interruptHandler;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static void ADC_DeInitInterruptHandler(void)
{
    ADC_InterruptHandler = NULL_PTR;
}

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    static Std_ReturnType ADC_InitPriority(INTERRUPTS_PriorityTypeDef loc_priority)
    {
        Std_ReturnType loc_ret = E_OK;

        if (loc_priority < INTERRUPTS_PRIORITY_LIMIT)
        {
            INTI_ADC_SetPriority(loc_priority);
        }
        else
        {
            loc_ret = E_NOT_OK;
        }

        return loc_ret; 
    }
    static void ADC_DeInitPriority(void)
    {
        INTI_ADC_DeInitPriority();
    }
    #endif

void ADC_ISR(void)
{
    INTI_ADC_ClearFlag();

    if (NULL_PTR != ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}
#endif