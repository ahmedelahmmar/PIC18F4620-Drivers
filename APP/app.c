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

LED_InitTypeDef LED_RedLed = {
    .Channel.Pin = GPIO_PIN0,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_HIGH,
    .Status = LED_OFF
};

LED_InitTypeDef LED_BlueLed = {
    .Channel.Pin = GPIO_PIN6,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_LOW,
    .Status = LED_OFF
};

PUSHBUTTON_InitTypeDef PB_Top = {
    .Channel.Pin = GPIO_PIN0,
    .Channel.Port = GPIO_PORTB,
    .Configuration = PUSHBUTTON_ACTIVE_HIGH
};

PUSHBUTTON_InitTypeDef PB_Bottom = {
    .Channel.Pin = GPIO_PIN1,
    .Channel.Port = GPIO_PORTB,
    .Configuration = PUSHBUTTON_ACTIVE_LOW
};

void INT0_Routine(void)
{
    LED_Toggle(&LED_RedLed);
}

void INT1_Routine(void)
{
    LED_Toggle(&LED_BlueLed);
}

EXTI_INTxInitTypeDef Interrupt0 = {
    .INTx = EXTI_INT0,
    .Trigger = EXTI_RISING_EDGE,
    .Priority = INTERRUPTS_HIGH_PRIORITY,
    .InterruptHandler = INT0_Routine
};

EXTI_INTxInitTypeDef Interrupt1 = {
    .INTx = EXTI_INT1,
    .Trigger = EXTI_RISING_EDGE,
    .Priority = INTERRUPTS_HIGH_PRIORITY,
    .InterruptHandler = INT1_Routine
};

Std_ReturnType Status;
int main(void)
{
    Status = LED_Init(&LED_RedLed);
    Status |= LED_Init(&LED_BlueLed);
    Status |= PUSHBUTTON_Init(&PB_Top);
    Status |= PUSHBUTTON_Init(&PB_Bottom);
    
    INTERRUPTS_EnablePriorityFeature();
    INTERRUPTS_EnableAllHighPriorityInterrupts();
    
    Status |= EXTI_INTxInit(&Interrupt0);    
    Status |= EXTI_INTxInit(&Interrupt1);
    
    while(TRUE)
    {
//        Status |= PUSHBUTTON_RefreshStatus(&PB_Top);
//        if (PUSHBUTTON_PRESSED == PB_Top.Status)
//        {
//            LED_TurnOn(&LED_RedLed);
//        }
//        
//        Status |= PUSHBUTTON_RefreshStatus(&PB_Bottom);
//        if (PUSHBUTTON_PRESSED == PB_Bottom.Status)
//        {
//            LED_TurnOff(&LED_RedLed);
//        }
        
        LED_Toggle(&LED_BlueLed);
        DELAY_MS(2000);
    }
    
    return 0;
}