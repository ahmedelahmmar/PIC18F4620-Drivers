/**
 * @file PushButton.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date 27.07.23
 */

#include "PushButton.h"

Std_ReturnType PUSHBUTTON_Init(const PUSHBUTTON_InitTypeDef * const loc_button)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_button)
    {
        loc_ret = GPIO_SetChannelDirection(&(loc_button->Channel), GPIO_INPUT);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType PUSHBUTTON_RefreshStatus(PUSHBUTTON_InitTypeDef * const loc_button)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_button)
    {
        loc_ret = GPIO_RefreshChannelLogic(&(loc_button->Channel));
        
        switch(loc_button->Configuration)
        {
            case PUSHBUTTON_ACTIVE_LOW:
                loc_button->Status = (GPIO_LOW == loc_button->Channel.Logic) ? PUSHBUTTON_PRESSED : PUSHBUTTON_RELEASED;
                break;
                
            case PUSHBUTTON_ACTIVE_HIGH:
                loc_button->Status = (GPIO_HIGH == loc_button->Channel.Logic) ? PUSHBUTTON_PRESSED : PUSHBUTTON_RELEASED;
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

Std_ReturnType PUSHBUTTON_GetStatus(const PUSHBUTTON_InitTypeDef * const loc_button, PUSHBUTTON_StatusTypeDef * const loc_status_ret)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_button) && (NULL != loc_status_ret))
    {
        GPIO_LogicTypeDef loc_logic;
        loc_ret = GPIO_GetChannelLogic(&(loc_button->Channel), &loc_logic);
        
        switch(loc_button->Configuration)
        {
            case PUSHBUTTON_ACTIVE_LOW:
               *loc_status_ret = (GPIO_LOW == loc_logic) ? PUSHBUTTON_PRESSED : PUSHBUTTON_RELEASED;
                break;
                
            case PUSHBUTTON_ACTIVE_HIGH:
                *loc_status_ret = (GPIO_HIGH == loc_logic) ? PUSHBUTTON_PRESSED : PUSHBUTTON_RELEASED;
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