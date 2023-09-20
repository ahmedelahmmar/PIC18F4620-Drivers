/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

SPI_InitTypeDef SPI = {
    .Mode = SPI_MODE_MASTER_PRESCALER_64,
    .SampleTime = SPI_SAMPLE_TIME_MIDDLE_OF_DATA,
    .SetupTime = SPI_SETUP_TIME_LEADING_EDGE,
    .ClockPolarity = SPI_CLOCK_POLARITY_LOW
};

Std_ReturnType ErrorStatus = E_OK;

int main(void)
{
    INTI_EnableInterrupts();

    ErrorStatus |= SPI_Init(&SPI);

    while (1)
    {
        ErrorStatus |= SPI_SendData(&SPI, 'X');
        DELAY_MS(500);
    }

    return 0;
}

void CCP1_Handler(void)
{

}
