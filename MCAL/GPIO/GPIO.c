/**
 * @file GPIO.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.3
 * @date 2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "GPIO_Private.h"
#include "GPIO.h"

static volatile uint8 * const TRIS[NUMBER_OF_PORTS] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
static volatile uint8 * const PORT[NUMBER_OF_PORTS] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
static volatile uint8 * const LAT[NUMBER_OF_PORTS]  = {&LATA,  &LATB,  &LATC,  &LATD,  &LATE };

#if (GPIO_CHANNEL_INTERFACES == STD_ON)
Std_ReturnType GPIO_InitChannel(const GPIO_InitTypeDef * const loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_channel)
    {
        loc_ret |= GPIO_SetChannelDirection(loc_channel, loc_channel->Direction);
        
        if (loc_channel->Direction == GPIO_OUTPUT)
        {
            loc_ret |= GPIO_SetChannelLogic(loc_channel, loc_channel->Logic);
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_SetChannelDirection(const GPIO_InitTypeDef * const loc_channel, const GPIO_DirectionTypeDef loc_direction)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->Port < NUMBER_OF_PORTS) && (loc_channel->Pin < NUMBER_OF_PINS_PER_PORT))
    {
        switch(loc_direction)
        {
            case GPIO_OUTPUT:
                CLR_BIT(loc_channel->Pin, *TRIS[loc_channel->Port]);
                break;
            
            case GPIO_INPUT:
                SET_BIT(loc_channel->Pin, *TRIS[loc_channel->Port]);
                break;
                
            default: loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_SetChannelLogic(const GPIO_InitTypeDef * const loc_channel, const GPIO_LogicTypeDef loc_logic)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->Direction == GPIO_OUTPUT) && (loc_channel->Port < NUMBER_OF_PORTS) && (loc_channel->Pin < NUMBER_OF_PINS_PER_PORT))
    {
        switch(loc_logic)
        {
            case GPIO_LOW:
                CLR_BIT(loc_channel->Pin, *LAT[loc_channel->Port]);
                break;
            
            case GPIO_HIGH:
                SET_BIT(loc_channel->Pin, *LAT[loc_channel->Port]);
                break;
                
            default: loc_ret = E_NOT_OK;
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_ToggleChannelLogic(const GPIO_InitTypeDef * const loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->Direction == GPIO_OUTPUT) && (loc_channel->Port < NUMBER_OF_PORTS) && (loc_channel->Pin < NUMBER_OF_PINS_PER_PORT))
    {
        TOG_BIT(loc_channel->Pin, *LAT[loc_channel->Port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_RefreshChannelDirection(GPIO_InitTypeDef * const loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->Port < NUMBER_OF_PORTS) && (loc_channel->Pin < NUMBER_OF_PINS_PER_PORT))
    {
        loc_channel->Direction = GET_BIT(loc_channel->Pin, *TRIS[loc_channel->Port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;   
}

Std_ReturnType GPIO_GetChannelDirection(const GPIO_InitTypeDef * const loc_channel, GPIO_DirectionTypeDef * const loc_direction_ret)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (NULL != loc_direction_ret) && (loc_channel->Port < NUMBER_OF_PORTS) && (loc_channel->Pin < NUMBER_OF_PINS_PER_PORT))
    {
        *loc_direction_ret = GET_BIT(loc_channel->Pin, *TRIS[loc_channel->Port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;    
}

Std_ReturnType GPIO_RefreshChannelLogic(GPIO_InitTypeDef * const loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->Port < NUMBER_OF_PORTS) && (loc_channel->Pin < NUMBER_OF_PINS_PER_PORT))
    {
        loc_channel->Logic = GET_BIT(loc_channel->Pin, *PORT[loc_channel->Port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;  
}

Std_ReturnType GPIO_GetChannelLogic(const GPIO_InitTypeDef * const loc_channel, GPIO_LogicTypeDef * const loc_logic_ret)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (NULL != loc_logic_ret) && (loc_channel->Port < NUMBER_OF_PORTS) && (loc_channel->Pin < NUMBER_OF_PINS_PER_PORT))
    {
        *loc_logic_ret = GET_BIT(loc_channel->Pin, *PORT[loc_channel->Port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;  
}
#endif

#if (GPIO_PORT_INTERFACES == STD_ON)
Std_ReturnType GPIO_SetPortDirection(const GPIO_PortTypeDef loc_port, const uint8 loc_direction_mask)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (loc_port < NUMBER_OF_PORTS)
    {
        *TRIS[loc_port] = loc_direction_mask;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_SetPortLogic(const GPIO_PortTypeDef loc_port, const uint8 loc_logic_mask)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (loc_port < NUMBER_OF_PORTS)
    {
        *LAT[loc_port] = loc_logic_mask;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_TogglePortLogic(const GPIO_PortTypeDef loc_port)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (loc_port < NUMBER_OF_PORTS)
    {
        *LAT[loc_port] ^= GPIO_ALL_PINS;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_GetPortDirection(const GPIO_PortTypeDef loc_port, uint8 * const loc_direction_ret)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_direction_ret) && (loc_port < NUMBER_OF_PORTS))
    {
        *loc_direction_ret = *TRIS[loc_port];
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;   
}

Std_ReturnType GPIO_GetPortLogic(const GPIO_PortTypeDef loc_port, uint8 * const loc_logic_ret)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_logic_ret) && (loc_port < NUMBER_OF_PORTS))
    {
        *loc_logic_ret = *LAT[loc_port];
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;   
}
#endif
 