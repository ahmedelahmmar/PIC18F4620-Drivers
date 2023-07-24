/**
 * @file GPIO.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "GPIO.h"

static volatile uint8 * const TRIS[NUMBER_OF_PORTS] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
static volatile uint8 * const PORT[NUMBER_OF_PORTS] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};
static volatile uint8 * const LAT[NUMBER_OF_PORTS]  = {&LATA,  &LATB,  &LATC,  &LATD,  &LATE };

#if (GPIO_CHANNEL_INTERFACES == STD_ON)
Std_ReturnType GPIO_InitChannel(const channelConfig_t * loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (NULL != loc_channel)
    {
        loc_ret |= GPIO_WriteChannelDirection(loc_channel, loc_channel->direction);
        
        if (loc_channel->direction == GPIO_OUTPUT)
        {
            loc_ret |= GPIO_WriteChannelLogic(loc_channel, loc_channel->logic);
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_WriteChannelDirection(const channelConfig_t * loc_channel, const direction_t loc_direction)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->port < NUMBER_OF_PORTS) && (loc_channel->pin < NUMBER_OF_PINS_PER_PORT))
    {
        switch(loc_direction)
        {
            case GPIO_OUTPUT:
                CLR_BIT(loc_channel->pin, *TRIS[loc_channel->port]);
                break;
            
            case GPIO_INPUT:
                SET_BIT(loc_channel->pin, *TRIS[loc_channel->port]);
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

Std_ReturnType GPIO_WriteChannelLogic(const channelConfig_t * loc_channel, const logic_t loc_logic)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->direction == GPIO_OUTPUT) && (loc_channel->port < NUMBER_OF_PORTS) && (loc_channel->pin < NUMBER_OF_PINS_PER_PORT))
    {
        switch(loc_logic)
        {
            case GPIO_LOW:
                CLR_BIT(loc_channel->pin, *LAT[loc_channel->port]);
                break;
            
            case GPIO_HIGH:
                SET_BIT(loc_channel->pin, *LAT[loc_channel->port]);
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

Std_ReturnType GPIO_ToggleChannelLogic(const channelConfig_t * loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->direction == GPIO_OUTPUT) && (loc_channel->port < NUMBER_OF_PORTS) && (loc_channel->pin < NUMBER_OF_PINS_PER_PORT))
    {
        TOG_BIT(loc_channel->pin, *LAT[loc_channel->port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_ReadChannelDirection(channelConfig_t * loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->port < NUMBER_OF_PORTS) && (loc_channel->pin < NUMBER_OF_PINS_PER_PORT))
    {
        loc_channel->direction = GET_BIT(loc_channel->pin, *TRIS[loc_channel->port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;   
}

Std_ReturnType GPIO_ReadChannelLogic(channelConfig_t * loc_channel)
{
    Std_ReturnType loc_ret = E_OK;
    
    if ((NULL != loc_channel) && (loc_channel->port < NUMBER_OF_PORTS) && (loc_channel->pin < NUMBER_OF_PINS_PER_PORT))
    {
        loc_channel->logic = GET_BIT(loc_channel->pin, *PORT[loc_channel->port]);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;  
}
#endif

#if (GPIO_PORT_INTERFACES == STD_ON)
Std_ReturnType GPIO_WritePortDirection(const port_t loc_port, const uint8 loc_direction_mask)
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

Std_ReturnType GPIO_WritePortLogic(const port_t loc_port, const uint8 loc_logic_mask)
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

Std_ReturnType GPIO_TogglePortLogic(const port_t loc_port)
{
    Std_ReturnType loc_ret = E_OK;
    
    if (loc_port < NUMBER_OF_PORTS)
    {
        *LAT[loc_port] ^= PORT_MASK;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }
    
    return loc_ret;
}

Std_ReturnType GPIO_ReadPortDirection(const port_t loc_port, uint8 * const loc_direction_ret)
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

Std_ReturnType GPIO_ReadPortLogic(const port_t loc_port, uint8 * const loc_logic_ret)
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
 