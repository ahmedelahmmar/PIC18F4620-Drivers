/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "app.h"

LED_InitTypeDef LED1 = {
    .Channel.Pin = GPIO_PIN0,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

LED_InitTypeDef LED2 = {
    .Channel.Pin = GPIO_PIN1,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

LED_InitTypeDef LED3 = {
    .Channel.Pin = GPIO_PIN2,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

LED_InitTypeDef LED4 = {
    .Channel.Pin = GPIO_PIN3,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

void RB4_RISR(void)
{
    LED_TurnOn(&LED1);
}

void RB4_FISR(void)
{
    LED_TurnOn(&LED2);
}

void RB5_RISR(void)
{
    LED_TurnOff(&LED1);
}

void RB5_FISR(void)
{
    LED_TurnOff(&LED2);
}

void RB6_RISR(void)
{
    LED_TurnOn(&LED3);
}

void RB6_FISR(void)
{
    LED_TurnOn(&LED4);
}


void RB7_RISR(void)
{
    LED_TurnOff(&LED3);   
}

void RB7_FISR(void)
{
    LED_TurnOff(&LED4);
}


EXTI_RBxInitTypeDef RB4obj = {
    .RBx = EXTI_RB4,
    .RisingEdgeInterruptHandler = RB4_RISR,
    .FallingEdgeInterruptHandler = RB4_FISR
};

EXTI_RBxInitTypeDef RB5obj = {
    .RBx = EXTI_RB5,
    .RisingEdgeInterruptHandler = RB5_RISR,
    .FallingEdgeInterruptHandler = RB5_FISR
};

EXTI_RBxInitTypeDef RB6obj = {
    .RBx = EXTI_RB6,
    .RisingEdgeInterruptHandler = RB6_RISR,
    .FallingEdgeInterruptHandler = RB6_FISR
};

EXTI_RBxInitTypeDef RB7obj = {
    .RBx = EXTI_RB7,
    .RisingEdgeInterruptHandler = RB7_RISR,
    .FallingEdgeInterruptHandler = RB7_FISR
};

Std_ReturnType Status;
int main(void)
{
    INTERRUPTS_EnableAllGlobalInterrupts();
    INTERRUPTS_EnableAllPeripheralInterrupts();
    
    Status |= LED_Init(&LED1);
    Status |= LED_Init(&LED2);
    Status |= LED_Init(&LED3);
    Status |= LED_Init(&LED4);
  
    Status |= EXTI_RBxInit(&RB4obj);    
    Status |= EXTI_RBxInit(&RB5obj);    
    Status |= EXTI_RBxInit(&RB6obj);    
    Status |= EXTI_RBxInit(&RB7obj);    
    
    while(TRUE){}
    
    return 0;
}