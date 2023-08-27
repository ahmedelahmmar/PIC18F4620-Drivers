/**
 * @file LCD.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 25.08.23
 */

#include "LCD.h"

static const uint8 RowOffsets[4] = {0x00, 0x40, 0x10, 0x50};

static Std_ReturnType LCD_SendHighNibble(const LCD_InitTypeDef * const InitPtr, const uint8 Data);
static Std_ReturnType LCD_SendLowNibble(const LCD_InitTypeDef * const InitPtr, const uint8 Data);
static Std_ReturnType LCD_SendEnable(const LCD_InitTypeDef * const InitPtr);

static void LCD_reverseString(uint8 * const str, const uint8 length);
static void LCD_intToString(sint32 Data, uint8 * const buffer);
static void LCD_floatToString(float32 Data, uint8 * const buffer, uint8 precision);

Std_ReturnType LCD_Init(const LCD_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret |= GPIO_SetChannelDirection(&(InitPtr->RS), GPIO_OUTPUT);
        loc_ret |= GPIO_SetChannelDirection(&(InitPtr->RW), GPIO_OUTPUT);
        loc_ret |= GPIO_SetChannelDirection(&(InitPtr->E),  GPIO_OUTPUT);

        uint8 loc_counter = (LCD_MODE_4BIT == InitPtr->Mode) ? 4 : 0;
        for (; loc_counter < 8; ++loc_counter)
        {
            loc_ret |= GPIO_SetChannelDirection(&(InitPtr->D[loc_counter]),  GPIO_OUTPUT);
        }

        switch (InitPtr->Mode)
        {
            case LCD_MODE_4BIT:
                DELAY_MS(15);
                loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_RETURN_HOME);
                loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_4BIT_MODE_2LINE);
                break;

            case LCD_MODE_8BIT:
                DELAY_MS(15);
                loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_8BIT_MODE_2LINE);
                DELAY_MS(5);
                loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_8BIT_MODE_2LINE);
                DELAY_US(100);
                loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_8BIT_MODE_2LINE);
                break;

            default:
                loc_ret = E_NOT_OK;
        }

        loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_DISPLAY_OFF);
        loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_CLEAR_DISPLAY);
        loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_INCREMENT_CURSOR);
        loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_RETURN_HOME);
        loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_DISPLAY_ON);
        loc_ret |= LCD_SendCommand(InitPtr, LCD_COMMAND_DDRAM_BASE);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType LCD_SendCommand(const LCD_InitTypeDef * const InitPtr, const LCD_CommandsTypeDef Command)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret |= GPIO_SetChannelLogic(&(InitPtr->RW), GPIO_LOW);   
        loc_ret |= GPIO_SetChannelLogic(&(InitPtr->RS), GPIO_LOW);  

        switch (InitPtr->Mode)
        {
            case LCD_MODE_4BIT:

                loc_ret |= LCD_SendHighNibble(InitPtr, Command);
                loc_ret |= LCD_SendEnable(InitPtr);
                loc_ret |= LCD_SendLowNibble(InitPtr, Command);
                loc_ret |= LCD_SendEnable(InitPtr);

                break;

            case LCD_MODE_8BIT:

                for (uint8 loc_counter = 0; loc_counter < 8; ++loc_counter)
                {
                    loc_ret |= GPIO_SetChannelLogic(&(InitPtr->D[loc_counter]), ((Command >> loc_counter) & 1));
                }
                loc_ret |= LCD_SendEnable(InitPtr);

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

Std_ReturnType LCD_WriteChar(const LCD_InitTypeDef * const InitPtr, const uint8 Data)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        loc_ret |= GPIO_SetChannelLogic(&(InitPtr->RW), GPIO_LOW);   
        loc_ret |= GPIO_SetChannelLogic(&(InitPtr->RS), GPIO_HIGH);  

        switch (InitPtr->Mode)
        {
            case LCD_MODE_4BIT:

                loc_ret |= LCD_SendHighNibble(InitPtr, Data);
                loc_ret |= LCD_SendEnable(InitPtr);
                loc_ret |= LCD_SendLowNibble(InitPtr, Data);
                loc_ret |= LCD_SendEnable(InitPtr);

                break;

            case LCD_MODE_8BIT:

                for (uint8 loc_counter = 0; loc_counter < 8; ++loc_counter)
                {
                    loc_ret |= GPIO_SetChannelLogic(&(InitPtr->D[loc_counter]), ((Data >> loc_counter) & 1));
                }
                loc_ret |= LCD_SendEnable(InitPtr);

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

Std_ReturnType LCD_WriteString(const LCD_InitTypeDef * const InitPtr, const uint8 *Data)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (NULL_PTR != Data))
    {
        while (*Data)
        {
            loc_ret |= LCD_WriteChar(InitPtr, *Data++);
        }
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType LCD_WriteInt(const LCD_InitTypeDef * const InitPtr, const sint32 Data)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        uint8 buffer[17];

        LCD_intToString(Data, buffer);

        loc_ret |= LCD_WriteString(InitPtr, buffer);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType LCD_WriteFloat(const LCD_InitTypeDef * const InitPtr, const float32 Data, const uint8 Precision)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        uint8 buffer[17];
        
        LCD_floatToString(Data, buffer, Precision);

        loc_ret |= LCD_WriteString(InitPtr, buffer);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;   
}

Std_ReturnType LCD_SetCursor(const LCD_InitTypeDef * const InitPtr, const uint8 Row, const uint8 Column)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (Row < InitPtr->Display.Rows) && (Column < InitPtr->Display.Columns))
    {
        loc_ret |= LCD_SendCommand(InitPtr, (LCD_COMMAND_DDRAM_BASE + RowOffsets[Row] + Column)); 
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType LCD_ClearRow(const LCD_InitTypeDef * const InitPtr, const uint8 Row)
{
    Std_ReturnType loc_ret = E_OK;

    if ((NULL_PTR != InitPtr) && (Row < InitPtr->Display.Rows))
    {
        loc_ret |= LCD_SetCursor(InitPtr, Row, 0);

        uint8 buffer[40];
        
        for (uint8 i = 0; i < InitPtr->Display.Columns; ++i) buffer[i] = 0x20;
        buffer[InitPtr->Display.Columns] = '\0';

        loc_ret |= LCD_WriteString(InitPtr, buffer);
        loc_ret |= LCD_SetCursor(InitPtr, Row, 0);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

static Std_ReturnType LCD_SendHighNibble(const LCD_InitTypeDef * const InitPtr, const uint8 Data)
{
    Std_ReturnType loc_ret = E_OK;

    for (uint8 loc_counter = 4; loc_counter < 8; ++loc_counter)
    {
        loc_ret |= GPIO_SetChannelLogic(&(InitPtr->D[loc_counter]), ((Data >> loc_counter) & 0x01));
    }

    return loc_ret;
}

static Std_ReturnType LCD_SendLowNibble(const LCD_InitTypeDef * const InitPtr, const uint8 Data)
{
    Std_ReturnType loc_ret = E_OK;

    for (uint8 loc_counter = 0; loc_counter < 4; ++loc_counter)
    {
        loc_ret |= GPIO_SetChannelLogic(&(InitPtr->D[loc_counter + 4]), ((Data >> loc_counter) & 0x01));
    }

    return loc_ret;  
}

static Std_ReturnType LCD_SendEnable(const LCD_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    loc_ret |= GPIO_SetChannelLogic(&(InitPtr->E), GPIO_HIGH);

    DELAY_US(1);

    loc_ret |= GPIO_SetChannelLogic(&(InitPtr->E), GPIO_LOW);

    DELAY_MS(2);

    return loc_ret;
}

static void LCD_reverseString(uint8 * const str, const uint8 length) 
{
    uint8 start = 0;
    uint8 end = length - 1;
    
    while (start < end) 
    {
        str[start]   ^= str[end];
        str[end]     ^= str[start];
        str[start++] ^= str[end--];
    }
}

static void LCD_intToString(sint32 Data, uint8 * const buffer) 
{
    uint8 i = 0;
    boolean isNegative = 0;
    
    if (Data == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }
    
    if (Data < 0) {
        isNegative = 1;
        Data = -Data;
    }
    
    while (Data > 0) {
        buffer[i++] = ((Data % 10) + '0');
        Data /= 10;
    }
    
    if (isNegative) {
        buffer[i++] = '-';
    }
    
    buffer[i] = '\0';
    
    LCD_reverseString(buffer, i);
}

static void LCD_floatToString(float32 Data, uint8 * const buffer, uint8 precision) 
{
    float32 fracPart = Data - (uint32)Data;

    LCD_intToString((sint32)Data, buffer);

    uint8 i = 0;
    while (buffer[++i] && buffer[0]); 

    if (precision > 0) 
    {
        buffer[i++] = '.';

        while (precision-- > 0) 
        {
            fracPart *= 10;
        }
    }

    LCD_intToString((fracPart < 0) ? -(sint32)fracPart : (sint32)fracPart, (buffer + i));
}