/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

void TIMER0_Handler(void);
void TIMER1_Handler(void);
void TIMER2_Handler(void);

TIMER0_InitTypeDef TIMER0 = {
    .Mode = TIMER0_MODE_TIMER,
    .Resolution = TIMER0_RESOLUTION_16BIT,
    .Prescaler = TIMER0_PRESCALER_256,
    .InterruptHandler = TIMER0_Handler
};

TIMER1_InitTypeDef TIMER1 = {
    .Mode = TIMER1_MODE_TIMER,
    .Prescaler = TIMER1_PRESCALER_8,
    .InterruptHandler = TIMER1_Handler
};

TIMER2_InitTypeDef TIMER2 = {
    .Mode = TIMER2_MODE_COMPARE_MATCH,
    .Prescaler = TIMER2_PRESCALER_16,
    .Postscaler = TIMER2_POSTSCALER_16,
    .InterruptHandler = TIMER2_Handler
};

LED_InitTypeDef LED1 = {
    .Channel.Port = GPIO_PORTC,
    .Channel.Pin = GPIO_PIN0,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

LED_InitTypeDef LED2 = {
    .Channel.Port = GPIO_PORTC,
    .Channel.Pin = GPIO_PIN1,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

LED_InitTypeDef LED3 = {
    .Channel.Port = GPIO_PORTC,
    .Channel.Pin = GPIO_PIN2,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

int main(void)
{
    INTI_EnableInterrupts();

    LED_Init(&LED1);
    LED_Init(&LED2);
    LED_Init(&LED3);

    TIMER0_Init(&TIMER0);
    TIMER1_Init(&TIMER1);
    TIMER2_Init(&TIMER2);

    TIMER0_StartTimer(&TIMER0, 500);
    TIMER1_StartTimer(&TIMER1, 1000);
    TIMER2_StartTimer(&TIMER2, 2000);

    while (1);

    return 0;
}

void TIMER0_Handler(void)
{
    LED_Toggle(&LED1);
}

void TIMER1_Handler(void)
{
    LED_Toggle(&LED2);
}

void TIMER2_Handler(void)
{
    LED_Toggle(&LED3);
}