/**
 * @file main.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date 2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "APP/app.h"

channelConfig_t LED1 = {
  .pin = GPIO_PIN0,
  .port = GPIO_PORTC,
  .direction = GPIO_OUTPUT,
  .logic = GPIO_LOW 
};

int main(void)
{  
    GPIO_WritePortDirection(GPIO_PORTC, GPIO_OUTPUT);
    GPIO_WritePortLogic(GPIO_PORTC, 0x55);
    
    while(TRUE)
    {
        __delay_ms(1000);
        GPIO_TogglePortLogic(GPIO_PORTC);
    }
    
    return 0;
}