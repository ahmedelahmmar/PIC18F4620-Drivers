/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

LED_InitTypeDef LED1 = {
    .Channel.Pin = GPIO_PIN0,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

void T0_Handler(void);

TIMER0_InitTypeDef T0 = {
    .InterruptHandler = T0_Handler,
    .Mode = TIMER0_MODE_TIMER,
    .Resolution = TIMER0_RESOLUTION_8BIT,
    .Prescaler = TIMER0_PRESCALER_16,
};

volatile Std_ReturnType Status = E_OK; 
int main(void)
{   
    INTERRUPTS_EnableAllGlobalInterrupts();
    INTERRUPTS_EnableAllPeripheralInterrupts();

    LED_Init(&LED1);
    TIMER0_Init(&T0);
    TIMER0_StartTimer(&T0, 1);
    
    while (TRUE)
    {
        
    }

    return Status;
}

void T0_Handler(void)
{
    static uint8 counter = 0;
    counter++;
    if (counter <= 75)
    {
        LED_TurnOn(&LED1);
    }
    else if (counter < 100)
    {
        LED_TurnOff(&LED1);
    }
    else counter = 0;

}