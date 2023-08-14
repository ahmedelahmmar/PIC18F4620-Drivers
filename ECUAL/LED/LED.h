/**
 * @file LED.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief This header file provides an interface for controlling LEDs.
 *
 * The LED interface allows users to easily manage LEDs on a microcontroller without dealing with
 * low-level GPIO configurations. It abstracts the hardware details and provides simple functions
 * to initialize, turn on, turn off, and toggle LED states.
 *
 * @note Include this header file in your application code to access the LED control interface.
 * @note The file is thoroughly documented, providing clear explanations for each function's purpose,
 *       parameters, return values, and usage examples.
 * 
 * @version 0.2
 * @date 25.07.23 
 */
#ifndef _LED_H_
#define	_LED_H_

#include "../../MCAL/GPIO/GPIO.h"

typedef enum
{
    LED_OFF = 0,
    LED_ON
            
} LED_StatusTypeDef;

typedef enum 
{
    LED_ACTIVE_LOW = 0,
    LED_ACTIVE_HIGH
            
} LED_ConfigTypeDef;

typedef struct
{
    GPIO_InitTypeDef Channel;
    LED_StatusTypeDef Status;
    LED_ConfigTypeDef Configuration;
    
} LED_InitTypeDef;

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
 * @note If an invalid @param loc_led or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType LED_Init(const LED_InitTypeDef * const loc_led);

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
Std_ReturnType LED_TurnOn(const LED_InitTypeDef * const loc_led);

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
Std_ReturnType LED_TurnOff(const LED_InitTypeDef * const loc_led);

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
Std_ReturnType LED_Toggle(const LED_InitTypeDef * const loc_led);

/**
 * @brief Refreshes the status of an LED based on the provided configuration.
 *
 * This function refreshes the status of an LED specified by the @param loc_led parameter.
 * It updates the LED's state based on any changes that might have occurred since its initialization.
 *
 * @param loc_led Pointer to the LED configuration structure.
 * @return Std_ReturnType Error status indicating the success of refreshing the LED status.
 *     - E_OK: The LED status was refreshed successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_led or configuration).
 *
 * @note The function expects a valid @param loc_led parameter pointing to a valid LED configuration structure.
 * @note The LED configuration structure should contain the necessary information to control the LED.
 * @note This function should be used periodically to update the LED status if it is controlled externally.
 * @note If an invalid @param loc_led or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType LED_RefreshStatus(LED_InitTypeDef * const loc_led);

/**
 * @brief Retrieves the current status of an LED based on the provided configuration.
 *
 * This function retrieves the current status of an LED specified by the @param loc_led parameter
 * and stores the result in the memory location pointed to by the @param loc_status_ret parameter.
 * The function reads the actual status of the LED, which may differ from the last known state
 * stored in the LED configuration.
 *
 * @param loc_led Pointer to the LED configuration structure.
 * @param loc_status_ret Pointer to an LED_StatusTypeDef variable where the LED status 
 *        will be stored after the function call.
 * @return Std_ReturnType Error status indicating the success of reading the LED status.
 *     - E_OK: The LED status was retrieved successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_led or @param loc_status_ret).
 *
 * @note The function expects a valid @param loc_led parameter pointing to a valid LED configuration structure.
 * @note The @param loc_status_ret should point to a valid LED_StatusTypeDef variable where the 
 *       LED status value will be stored.
 * @note This function can be used to read the real-time status of the LED, which may have changed since initialization.
 * @note If an invalid @param loc_led or @param loc_status_ret is provided, the function will return E_NOT_OK.
 */
Std_ReturnType LED_GetStatus(const LED_InitTypeDef * const loc_led, LED_StatusTypeDef * const loc_status_ret);

#endif	/* _LED_H_ */