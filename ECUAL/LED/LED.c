/**
 * @file LED.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.2
 * @date 25.07.23
 */

#include "LED.h"

Std_ReturnType LED_Init(const LED_InitTypeDef * const loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {
        loc_ret = GPIO_SetChannelDirection(&(loc_led->Channel), GPIO_OUTPUT);
        
        switch(loc_led->Configuration)
        {
            case LED_ACTIVE_LOW:
                
                if (LED_ON == loc_led->Status)
                {
                    loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_LOW);
                }
                else if (LED_OFF == loc_led->Status)
                {
                    loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_HIGH);
                }
                else
                {
                    loc_ret = E_NOT_OK;
                }
                
                break;
                
            case LED_ACTIVE_HIGH:
                
                if (LED_ON == loc_led->Status)
                {
                    loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_HIGH);
                }
                else if (LED_OFF == loc_led->Status)
                {
                    loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_LOW);
                }
                else
                {
                    loc_ret = E_NOT_OK;
                }                
                
                break;
                
            default:
                loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_TurnOn(const LED_InitTypeDef * const loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {  
        switch(loc_led->Configuration)
        {
            case LED_ACTIVE_LOW:
                loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_LOW);
                break;
                
            case LED_ACTIVE_HIGH:
                loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_HIGH);
                break;
                
            default:
                loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_TurnOff(const LED_InitTypeDef * const loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {
        switch(loc_led->Configuration)
        {
            case LED_ACTIVE_LOW:
                loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_HIGH);
                break;
                
            case LED_ACTIVE_HIGH:
                loc_ret = GPIO_SetChannelLogic(&(loc_led->Channel), GPIO_LOW);
                break;
                
            default:
                loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_Toggle(const LED_InitTypeDef * const loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {   
        loc_ret = GPIO_ToggleChannelLogic(&(loc_led->Channel));
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_RefreshStatus(LED_InitTypeDef * const loc_led)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_led)
    {   
        loc_ret = GPIO_RefreshChannelLogic(&(loc_led->Channel));
        
        switch(loc_led->Configuration)
        {
            case LED_ACTIVE_LOW:
                loc_led->Status = (GPIO_LOW == loc_led->Channel.Logic) ? LED_ON : LED_OFF;
                break;
                
            case LED_ACTIVE_HIGH:
                loc_led->Status = (GPIO_HIGH == loc_led->Channel.Logic) ? LED_ON : LED_OFF;
                break;
                
            default:
                loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType LED_GetStatus(const LED_InitTypeDef * const loc_led, LED_StatusTypeDef * const loc_status_ret)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_led) && (NULL != loc_status_ret))
    {   
        GPIO_LogicTypeDef loc_logic;
        loc_ret = GPIO_GetChannelLogic(&(loc_led->Channel), &loc_logic);
        
        switch(loc_led->Configuration)
        {
            case LED_ACTIVE_LOW:
                *loc_status_ret = (GPIO_LOW == loc_logic) ? LED_ON : LED_OFF;
                break;
                
            case LED_ACTIVE_HIGH:
                *loc_status_ret = (GPIO_HIGH == loc_logic) ? LED_ON : LED_OFF;
                break;
                
            default:
                loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}