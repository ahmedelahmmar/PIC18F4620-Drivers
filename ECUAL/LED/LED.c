/**
 * @file LED.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 2023-07-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "LED.h"

Std_ReturnType LED_Init(const led_t * loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {
        channelConfig_t loc_ledChannel = {
            .pin = loc_led->pin,
            .port = loc_led->port,
            .logic = loc_led->logic,
            .direction = GPIO_OUTPUT
        };
        
        loc_ret = GPIO_InitChannel(&loc_ledChannel);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_TurnOn(const led_t * loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {
        channelConfig_t loc_ledChannel = {
            .pin = loc_led->pin,
            .port = loc_led->port,
            .logic = loc_led->logic,
            .direction = GPIO_OUTPUT
        };
        
        loc_ret = GPIO_WriteChannelLogic(&loc_ledChannel, GPIO_HIGH);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_TurnOff(const led_t * loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {
        channelConfig_t loc_ledChannel = {
            .pin = loc_led->pin,
            .port = loc_led->port,
            .logic = loc_led->logic,
            .direction = GPIO_OUTPUT
        };
        
        loc_ret = GPIO_WriteChannelLogic(&loc_ledChannel, GPIO_LOW);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_Toggle(const led_t * loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {
        channelConfig_t loc_ledChannel = {
            .pin = loc_led->pin,
            .port = loc_led->port,
            .logic = loc_led->logic,
            .direction = GPIO_OUTPUT
        };
        
        loc_ret = GPIO_ToggleChannelLogic(&loc_ledChannel);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}