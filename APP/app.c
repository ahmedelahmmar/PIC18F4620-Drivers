/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

void TIMER0_Handler(void);

TIMER0_InitTypeDef TIMER0 = {
    .Mode = TIMER0_MODE_TIMER,
    .Resolution = TIMER0_RESOLUTION_16BIT,
    .Prescaler = TIMER0_PRESCALER_256,
    .InterruptHandler = TIMER0_Handler
};

LED_InitTypeDef LED1 = {
    .Channel.Port = GPIO_PORTC,
    .Channel.Pin = GPIO_PIN0,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

int main(void)
{
    INTI_EnableInterrupts();

    LED_Init(&LED1);

    TIMER0_Init(&TIMER0);
    TIMER0_StartTimer(&TIMER0, 5000);

    while (1);

    return 0;
}

void TIMER0_Handler(void)
{
    LED_Toggle(&LED1);
}