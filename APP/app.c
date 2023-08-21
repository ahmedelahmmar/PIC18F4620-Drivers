/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

void ADCx_Handler(void);

ADC_InitTypeDef ADCx = {
    .InterruptHandler = ADCx_Handler,
    .ChannelConfiguration = ADC_CHANNEL_3_AND_BELOW_ANALOG,
    .AquisitionTime = ADC_AQT_12TAD,
    .Prescaler = ADC_PRESCALER_RC_OSC,
    .ResultAlignment = ADC_ALIGN_LEFT,
    .Vref = ADC_VREF_INTERNAL,
};

volatile ADC_ValueTypeDef pot0, pot1, pot2, pot3;
volatile uint8 ADC_Req = 0;

volatile Std_ReturnType status = E_OK; 

int main(void)
{   
    INTERRUPTS_EnableAllGlobalInterrupts();
    INTERRUPTS_EnableAllPeripheralInterrupts();

    status |= ADC_Init(&ADCx);
    
    while (TRUE)
    {
        switch (ADC_Req)
        {
            case 0:
                status |= ADC_StartConversion(ADC_CHANNEL_0);
                break;

            case 1:
                status |= ADC_StartConversion(ADC_CHANNEL_1);
                break;

            case 2:
                status |= ADC_StartConversion(ADC_CHANNEL_2);
                break;

            case 3:
                status |= ADC_StartConversion(ADC_CHANNEL_3);
                break;

            default:
                status = E_NOT_OK;
        }
    }

    return status;
}

void ADCx_Handler(void)
{
    switch (ADC_Req++)
    {
        case 0:
            status |= ADC_Read(&ADCx, &pot0);
            break;

        case 1:
            status |= ADC_Read(&ADCx, &pot1);
            break;

        case 2:
            status |= ADC_Read(&ADCx, &pot2);
            break;

        case 3:
            status |= ADC_Read(&ADCx, &pot3);
            ADC_Req = 0;
            break;

        default:
            status = E_NOT_OK;
    }
}