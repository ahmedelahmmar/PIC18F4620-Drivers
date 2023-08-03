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
    .Status = LED_ON
};

LED_InitTypeDef LED_BlueLed = {
    .Channel.Pin = GPIO_PIN6,
    .Channel.Port = GPIO_PORTC,
    .Configuration = LED_ACTIVE_LOW,
    .Status = LED_ON
};

int main(void)
{
    LED_Init(&LED_RedLed);
    LED_Init(&LED_BlueLed);
    
    while(TRUE)
    {
        
    }
    
    return 0;
}
