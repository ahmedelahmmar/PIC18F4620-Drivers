/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

void RxHandler(void);

EUSART_InitTypeDef UART = {
    .RxInterruptHandler = RxHandler,
    .Mode = EUSART_MODE_TXRX,
    .Parity = EUSART_NO_PARITY,
    .BrgResolution = EUSART_BRG_RESOLUTION_16BIT,
    .BrgSpeed = EUSART_BRG_SPEED_HIGH,
    .RxDataFrame = EUSART_RX_DATA_FRAME_8BIT,
    .TxDataFrame = EUSART_TX_DATA_FRAME_8BIT,
};

volatile Std_ReturnType Status = E_OK;
volatile uint8 string[9] = {0};

int main(void)
{   
#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_EnableAllHighPriorityInterrupts();
    INTERRUPTS_EnableAllLowPriorityInterrupts();
#else
    INTERRUPTS_EnableAllGlobalInterrupts();
    INTERRUPTS_EnableAllPeripheralInterrupts();
#endif 

    Status |= EUSART_Init(&UART, 9600);

    while (TRUE)
    {
 
    }

    return Status;
}

void RxHandler(void)
{
    EUSART_ReadStringBlocking(&UART, string, 9);

    for (uint8 i = 0; string[i]; ++i)
    {
        EUSART_SendDataFrameBlocking(&UART, string[i]);
    }
    EUSART_SendDataFrameBlocking(&UART, '\n');
}