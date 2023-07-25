/**
 * @file LED.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @brief This header file provides an interface for controlling LEDs.
 *
 * The LED interface allows users to easily manage LEDs on a microcontroller without dealing with
 * low-level GPIO configurations. It abstracts the hardware details and provides simple functions
 * to initialize, turn on, turn off, and toggle LED states.
 *
 * @note Include this header file in your application code to access the LED control interface.
 * @note The file is thoroughly documented, providing clear explanations for each function's purpose,
 *       parameters, return values, and usage examples.
 * @note The LED interface is designed to be portable and can be used with different microcontroller
 *       families and development environments.
 * @version 0.1
 * @date 2023-07-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _LED_H_
#define	_LED_H_

#include "../../MCAL/GPIO/GPIO.h"

typedef struct
{
    uint8 pin       : 3;
    uint8 port      : 3;
    uint8 logic     : 1;
    uint8 reserved  : 1;
    
} led_t;

/**
 * @brief Initializes a LED based on the provided configuration.
 *
 * This function initializes a LED based on the configuration provided in the @param loc_led parameter.
 * It sets up the GPIO channel for the LED and configures it as an output.
 *
 * @param loc_led Pointer to the LED configuration structure.
 * @return Std_ReturnType Error status indicating the success of the LED initialization.
 *     - E_OK: The LED was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid @param loc_led or configuration).
 *
 * @note The function expects a valid @param loc_led parameter pointing to a valid LED configuration structure.
 * @note The LED configuration structure should contain the GPIO channel information required to control the LED.
 * @note This function must be called before using the LED for any operations.
 * @note The function internally configures the GPIO channel as an output to control the LED.
 * @note If an invalid @param loc_led or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType LED_Init(const led_t * loc_led);

/**
 * @brief Turns on a LED based on the provided configuration.
 *
 * This function turns on a LED based on the configuration provided in the @param loc_led parameter.
 * It sets the logic level of the corresponding GPIO channel to turn on the LED.
 *
 * @param loc_led Pointer to the LED configuration structure.
 * @return Std_ReturnType Error status indicating the success of turning on the LED.
 *     - E_OK: The LED was turned on successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_led or configuration).
 *
 * @note The function expects a valid @param loc_led parameter pointing to a valid LED configuration structure.
 * @note The LED configuration structure should contain the GPIO channel information required to control the LED.
 * @note This function should be called after initializing the LED using the LED_Init() function.
 * @note The function sets the logic level of the GPIO channel to turn on the LED.
 * @note If an invalid @param loc_led or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType LED_TurnOn(const led_t * loc_led);

/**
 * @brief Turns off a LED based on the provided configuration.
 *
 * This function turns off a LED based on the configuration provided in the @param loc_led parameter.
 * It sets the logic level of the corresponding GPIO channel to turn off the LED.
 *
 * @param loc_led Pointer to the LED configuration structure.
 * @return Std_ReturnType Error status indicating the success of turning off the LED.
 *     - E_OK: The LED was turned off successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_led or configuration).
 *
 * @note The function expects a valid @param loc_led parameter pointing to a valid LED configuration structure.
 * @note The LED configuration structure should contain the GPIO channel information required to control the LED.
 * @note This function should be called after initializing the LED using the LED_Init() function.
 * @note The function sets the logic level of the GPIO channel to turn off the LED.
 * @note If an invalid @param loc_led or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType LED_TurnOff(const led_t * loc_led);

/**
 * @brief Toggles the state of a LED based on the provided configuration.
 *
 * This function toggles the state of a LED based on the configuration provided in the @param loc_led parameter.
 * It reads the current logic level of the corresponding GPIO channel and reverses it to toggle the LED state.
 *
 * @param loc_led Pointer to the LED configuration structure.
 * @return Std_ReturnType Error status indicating the success of toggling the LED state.
 *     - E_OK: The LED state was toggled successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_led or configuration).
 *
 * @note The function expects a valid @param loc_led parameter pointing to a valid LED configuration structure.
 * @note The LED configuration structure should contain the GPIO channel information required to control the LED.
 * @note This function should be called after initializing the LED using the LED_Init() function.
 * @note The function reads the current logic level of the GPIO channel to determine the LED state and toggles it.
 * @note If an invalid @param loc_led or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType LED_Toggle(const led_t * loc_led);

#endif	/* _LED_H_ */

