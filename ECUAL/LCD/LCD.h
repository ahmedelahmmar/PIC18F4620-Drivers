/**
 * @file LCD.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief LCD Display Interface
 *
 * The LCD interface provides functions to interact with and display information on a Liquid Crystal Display (LCD).
 * It abstracts low-level LCD control, allowing users to write characters, strings, and customize displays
 * without dealing with intricate hardware details.
 *
 * @note Include this header file in your application code to access the LCD display interface.
 * @note The file is documented, offering clear explanations for each function's purpose, parameters,
 *       return values, and usage examples.
 * @note The LCD interface simplifies working with LCD displays across different microcontroller families and
 *       development environments.
 * 
 * @version 0.1
 * @date 25.08.23
 */

#ifndef _LCD_H_
#define _LCD_H_

#include <builtins.h>
#include "../../MCAL/GPIO/GPIO.h"

typedef enum
{
    LCD_COMMAND_CLEAR_DISPLAY       = 0x01,
    LCD_COMMAND_RETURN_HOME         = 0x02,
    LCD_COMMAND_DECREMENT_CURSOR    = 0x04, 
    LCD_COMMAND_INCREMENT_CURSOR    = 0x06,
    LCD_COMMAND_DISPLAY_OFF         = 0x08,
    LCD_COMMAND_DISPLAY_ON          = 0x0C,
    LCD_COMMAND_4BIT_MODE_1LINE     = 0x20,
    LCD_COMMAND_4BIT_MODE_2LINE     = 0x28,
    LCD_COMMAND_8BIT_MODE_1LINE     = 0x30,
    LCD_COMMAND_8BIT_MODE_2LINE     = 0x38,
    LCD_COMMAND_CGRAM_BASE          = 0x40,
    LCD_COMMAND_DDRAM_BASE          = 0x80,

} LCD_CommandsTypeDef;

typedef enum
{   
    LCD_MODE_4BIT = 0,
    LCD_MODE_8BIT,
    LCD_MODE_LIMIT

} LCD_ModeTypeDef;

typedef struct
{
    uint8 Rows;   
    uint8 Columns;
    
} LCD_DisplayTypeDef;

typedef struct
{
    LCD_ModeTypeDef Mode;
    LCD_DisplayTypeDef Display;

    GPIO_InitTypeDef RS;
    GPIO_InitTypeDef RW;
    GPIO_InitTypeDef E;
    GPIO_InitTypeDef D[8];

} LCD_InitTypeDef;

/**
 * @brief Initialize the Liquid Crystal Display (LCD).
 *
 * This function initializes the LCD based on the configuration provided in the @param InitPtr parameter. It sets up the
 * display mode, cursor settings, and any required hardware configurations.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: The LCD was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration parameters).
 *
 * @note This function must be called before using the LCD for any display operations.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure containing appropriate
 *       configuration settings.
 */
Std_ReturnType LCD_Init(const LCD_InitTypeDef * const InitPtr);

/**
 * @brief Send a command to the Liquid Crystal Display (LCD).
 *
 * This function sends a command to control the behavior of the LCD based on the specified @param Command parameter.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage the command transmission.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @param Command The command code to be sent to the LCD (e.g., clear display, set cursor position).
 * @return Std_ReturnType Error status indicating the success of sending the command.
 *     - E_OK: The command was sent successfully.
 *     - E_NOT_OK: An error occurred during command transmission (e.g., invalid configuration or command).
 *
 * @note This function is used to send specific commands to control the LCD's behavior and display content.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure used for LCD configuration.
 * @note The @param Command parameter should be one of the LCD command codes defined in the LCD_CommandsTypeDef enum.
 */
Std_ReturnType LCD_SendCommand(const LCD_InitTypeDef * const InitPtr, const LCD_CommandsTypeDef Command);

/**
 * @brief Write a character to the Liquid Crystal Display (LCD).
 *
 * This function writes a single character to the LCD display based on the specified @param Data parameter. It utilizes
 * the configuration provided in the @param InitPtr parameter to manage the character display.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @param Data The character to be displayed on the LCD.
 * @return Std_ReturnType Error status indicating the success of writing the character.
 *     - E_OK: The character was written successfully.
 *     - E_NOT_OK: An error occurred during character display (e.g., invalid configuration or character data).
 *
 * @note This function is used to display individual characters on the LCD.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure used for LCD configuration.
 * @note The @param Data parameter represents the character to be displayed on the LCD screen.
 */
Std_ReturnType LCD_WriteChar(const LCD_InitTypeDef * const InitPtr, const uint8 Data);

/**
 * @brief Write a string to the Liquid Crystal Display (LCD).
 *
 * This function writes a null-terminated string to the LCD display based on the specified @param Data parameter.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage the string display.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @param Data Pointer to the null-terminated string to be displayed on the LCD.
 * @return Std_ReturnType Error status indicating the success of writing the string.
 *     - E_OK: The string was written successfully.
 *     - E_NOT_OK: An error occurred during string display (e.g., invalid configuration or string data).
 *
 * @note This function is used to display a sequence of characters as a string on the LCD.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure used for LCD configuration.
 * @note The @param Data parameter should be a pointer to a null-terminated string to be displayed on the LCD screen.
 */
Std_ReturnType LCD_WriteString(const LCD_InitTypeDef * const InitPtr, const uint8 *Data);

/**
 * @brief Write an integer value to the Liquid Crystal Display (LCD).
 *
 * This function writes an integer value to the LCD display based on the specified @param Data parameter. It utilizes
 * the configuration provided in the @param InitPtr parameter to manage the integer display.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @param Data The integer value to be displayed on the LCD.
 * @return Std_ReturnType Error status indicating the success of writing the integer value.
 *     - E_OK: The integer value was written successfully.
 *     - E_NOT_OK: An error occurred during integer display (e.g., invalid configuration or value).
 *
 * @note This function is used to display an integer value on the LCD screen.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure used for LCD configuration.
 * @note The @param Data parameter represents the integer value to be displayed on the LCD.
 */
Std_ReturnType LCD_WriteInt(const LCD_InitTypeDef * const InitPtr, const sint32 Data);

/**
 * @brief Write a floating-point value to the Liquid Crystal Display (LCD).
 *
 * This function writes a floating-point value to the LCD display based on the specified @param Data parameter.
 * The @param Precision parameter controls the number of decimal places to display. It utilizes the configuration
 * provided in the @param InitPtr parameter to manage the floating-point display.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @param Data The floating-point value to be displayed on the LCD.
 * @param Precision The number of decimal places to display.
 * @return Std_ReturnType Error status indicating the success of writing the floating-point value.
 *     - E_OK: The floating-point value was written successfully.
 *     - E_NOT_OK: An error occurred during floating-point display (e.g., invalid configuration or value).
 *
 * @note This function is used to display a floating-point value on the LCD screen with a specified precision.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure used for LCD configuration.
 * @note The @param Data parameter represents the floating-point value to be displayed on the LCD.
 * @note The @param Precision parameter controls the number of decimal places to display for the floating-point value.
 */
Std_ReturnType LCD_WriteFloat(const LCD_InitTypeDef * const InitPtr, const float32 Data, const uint8 Precision);

/**
 * @brief Set the cursor position on the Liquid Crystal Display (LCD).
 *
 * This function sets the cursor position on the LCD display based on the specified @param Row and @param Column parameters.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage cursor positioning.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @param Row The row index (starting from 0) where the cursor should be positioned.
 * @param Column The column index (starting from 0) where the cursor should be positioned.
 * @return Std_ReturnType Error status indicating the success of setting the cursor position.
 *     - E_OK: The cursor position was set successfully.
 *     - E_NOT_OK: An error occurred during cursor positioning (e.g., invalid configuration or position).
 *
 * @note This function is used to move the cursor to a specific row and column position on the LCD.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure used for LCD configuration.
 * @note The @param Row parameter specifies the row index (starting from 0) where the cursor should be positioned.
 * @note The @param Column parameter specifies the column index (starting from 0) where the cursor should be positioned.
 */
Std_ReturnType LCD_SetCursor(const LCD_InitTypeDef * const InitPtr, const uint8 Row, const uint8 Column);

/**
 * @brief Clear a row on the Liquid Crystal Display (LCD) and Set the cursor at the beginning of the row.
 *
 * This function clears all characters in a specific row on the LCD display based on the specified @param Row parameter.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage the row clearing.
 *
 * @param InitPtr Pointer to the LCD initialization structure containing configuration parameters.
 * @param Row The row index (starting from 0) to be cleared on the LCD.
 * @return Std_ReturnType Error status indicating the success of clearing the row.
 *     - E_OK: The row was cleared successfully.
 *     - E_NOT_OK: An error occurred during row clearing (e.g., invalid configuration or row index).
 *
 * @note This function is used to clear all characters in a specific row on the LCD display.
 * @note The @param InitPtr parameter should point to a valid LCD_InitTypeDef structure used for LCD configuration.
 * @note The @param Row parameter specifies the row index (starting from 0) to be cleared on the LCD.
 */
Std_ReturnType LCD_ClearRow(const LCD_InitTypeDef * const InitPtr, const uint8 Row);

#endif /* _LCD_H_ */