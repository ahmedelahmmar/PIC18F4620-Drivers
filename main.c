/**
 * @file main.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "lib/compiler.h"
#include "lib/stdtypes.h"

#define _XTAL_FREQ      16000000UL


int main(void)
{
    TRISC = 0x00;
    
    while (TRUE)
    {
        LATC = 0x00;
        __delay_ms(500);
        
        LATC = 0x01;
        __delay_ms(500);
        
        while (PORTC)
        {
            LATC = LATC << 1;
            __delay_ms(500);
        }
    }
    return 0;
}