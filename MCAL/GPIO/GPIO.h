/**
 * @file GPIO.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @brief This header file provides essential definitions and functions for interfacing with
 * General Purpose Input/Output (GPIO) pins on a microcontroller.
 *
 * The GPIO module allows users to control the direction (input/output) and logic level (high/low)
 * of individual pins on the microcontroller, providing a flexible way to interact with external
 * devices and peripherals.
 *
 * @note Include this header in your application code to utilize the GPIO functionality.
 * @note The file is thoroughly documented, providing clear explanations for each function's purpose,
 *       parameters, return values, and usage examples.
 * @version 0.1
 * @date 2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _GPIO_H_
#define _GPIO_H_


#include "GPIO_Config.h"
#include "GPIO_Private.h"

#include "../mcu_config.h"
#include "../../lib/compiler.h"
#include "../../lib/stdtypes.h"
#include "../../lib/bitmasking.h"

#include <../proc/pic18f4620.h>

typedef enum {GPIO_LOW, GPIO_HIGH}                                                                      logic_t;
typedef enum {GPIO_OUTPUT, GPIO_INPUT}                                                                  direction_t;
typedef enum {GPIO_PORTA, GPIO_PORTB, GPIO_PORTC, GPIO_PORTD, GPIO_PORTE}                               port_t;
typedef enum {GPIO_PIN0, GPIO_PIN1, GPIO_PIN2, GPIO_PIN3, GPIO_PIN4, GPIO_PIN5, GPIO_PIN6, GPIO_PIN7}   pin_t;

typedef struct
{
    uint8 pin       : 3;
    uint8 port      : 3;
    uint8 direction : 1;
    uint8 logic     : 1;
    
} channelConfig_t;

/** 
 * @brief Initializes a GPIO channel with the provided configuration.
 *
 * This function initializes a GPIO channel based on the configuration provided in the 
 * @param loc_channel parameter. It sets the direction of the channel as specified in the 
 * configuration and optionally sets the logic level if the direction is set to GPIO_OUTPUT.
 *
 * @param loc_channel Pointer to the channel configuration structure.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: The GPIO channel was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., @param loc_channel is NULL).
 *
 * @note This function must be called before using the GPIO channel for any operations.
 * @note If the direction of the channel is set to GPIO_OUTPUT, the logic level will be set
 *       based on the value specified in the configuration.
 */
Std_ReturnType GPIO_InitChannel(const channelConfig_t * loc_channel);

/** 
 * @brief Sets the direction of a GPIO channel based on the provided configuration.
 *
 * This function initializes a GPIO channel's direction as specified in the configuration.
 *
 * @param loc_channel Pointer to the channel configuration structure.
 * @param loc_direction The desired direction for the GPIO channel (GPIO_OUTPUT or GPIO_INPUT).
 * @return Std_ReturnType Error status indicating the success of setting the channel direction.
 *     - E_OK: The channel direction was set successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_channel or @param loc_direction).
 *
 * @note Ensure that @param loc_channel points to a valid configuration structure.
 * @note The port and pin values within the configuration must be within valid ranges.
 * @note Call this function before using the GPIO channel as an input or output.
 */
Std_ReturnType GPIO_WriteChannelDirection(const channelConfig_t * loc_channel, const direction_t loc_direction);

/** 
 * @brief Sets the logic level of a GPIO channel based on the provided configuration.
 *
 * This function sets the logic level of a GPIO channel specified in the configuration.
 *
 * @param loc_channel Pointer to the channel configuration structure.
 * @param loc_logic The desired logic level for the GPIO channel (GPIO_LOW or GPIO_HIGH).
 * @return Std_ReturnType Error status indicating the success of setting the channel logic level.
 *     - E_OK: The channel logic level was set successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_channel or @param loc_logic).
 *
 * @note Ensure that @param loc_channel points to a valid configuration structure.
 * @note The port and pin values within the configuration must be within valid ranges.
 * @note This function should be called only if the channel's direction is set to GPIO_OUTPUT.
 */
Std_ReturnType GPIO_WriteChannelLogic(const channelConfig_t * loc_channel, const logic_t loc_logic);

/** 
 * @brief Toggles the logic level of a GPIO channel based on the provided configuration.
 *
 * This function toggles the logic level of a GPIO channel specified in the configuration.
 *
 * @param loc_channel Pointer to the channel configuration structure.
 * @return Std_ReturnType Error status indicating the success of toggling the channel logic level.
 *     - E_OK: The channel logic level was toggled successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_channel).
 *
 * @note Ensure that @param loc_channel points to a valid configuration structure.
 * @note The port and pin values within the configuration must be within valid ranges.
 * @note This function should be called only if the channel's direction is set to GPIO_OUTPUT.
 */
Std_ReturnType GPIO_ToggleChannelLogic(const channelConfig_t * loc_channel);

/** 
 * @brief Reads the direction of a GPIO channel based on the provided configuration.
 *
 * This function reads the direction of a GPIO channel specified in the configuration 
 * and updates the @param loc_channel structure with the current direction.
 *
 * @param loc_channel Pointer to the channel configuration structure.
 * @return Std_ReturnType Error status indicating the success of reading the channel direction.
 *     - E_OK: The channel direction was read successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_channel).
 *
 * @note Ensure that @param loc_channel points to a valid configuration structure.
 * @note The port and pin values within the configuration must be within valid ranges.
 * @note The function updates the `direction` member in the channel configuration structure
 *       with the current direction read from the hardware register.
 */
Std_ReturnType GPIO_ReadChannelDirection(channelConfig_t * loc_channel);

/** 
 * @brief Reads the logic level of a GPIO channel based on the provided configuration.
 *
 * This function reads the logic level of a GPIO channel specified in the configuration 
 * and updates the @param loc_channel structure with the current logic level.
 *
 * @param loc_channel Pointer to the channel configuration structure.
 * @return Std_ReturnType Error status indicating the success of reading the channel logic level.
 *     - E_OK: The channel logic level was read successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @p loc_channel).
 *
 * @note Ensure that @param loc_channel points to a valid configuration structure.
 * @note The port and pin values within the configuration must be within valid ranges.
 * @note The function updates the `logic` member in the channel configuration structure
 *       with the current logic level read from the hardware register.
 */
Std_ReturnType GPIO_ReadChannelLogic(channelConfig_t * loc_channel);

/** 
 * @brief Sets the direction of a GPIO port based on the provided configuration.
 *
 * This function sets the direction of a GPIO port specified by the @param loc_port parameter 
 * according to the direction mask value specified in the @param loc_direction_mask parameter. 
 * It modifies the corresponding TRIS (Tri-State) register for the specified port to configure 
 * all the pins in the port as either inputs or outputs based on the mask.
 *
 * @param loc_port The GPIO port identifier (e.g., GPIO_PORTA, GPIO_PORTB, etc.).
 * @param loc_direction_mask The direction mask for the GPIO port, where each bit represents 
 *        the direction of the corresponding pin (0 for output, 1 for input).
 * @return Std_ReturnType Error status indicating the success of setting the port direction.
 *     - E_OK: The port direction was set successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_port parameter).
 *
 * @note The function expects a valid GPIO port identifier passed as the @param loc_port parameter.
 * @note The @param loc_direction_mask is an 8-bit value where each bit represents the direction 
 *       of the corresponding pin in the port. For example, bit 0 represents the direction of 
 *       pin 0, bit 1 represents the direction of pin 1, and so on.
 * @note This function should be called before using any of the GPIO pins in the specified port.
 * @note The function directly modifies the TRIS (Tri-State) register to configure the port's direction.
 */
Std_ReturnType GPIO_WritePortDirection(const port_t loc_port, const uint8 loc_direction_mask);

/** 
 * @brief Sets the logic level of a GPIO port based on the provided configuration.
 *
 * This function sets the logic level of a GPIO port specified by the @param loc_port parameter 
 * according to the logic mask value specified in the @param loc_logic_mask parameter. It modifies 
 * the corresponding LAT (Latch) register for the specified port to set the logic level of all 
 * the pins in the port based on the mask.
 *
 * @param loc_port The GPIO port identifier (e.g., GPIO_PORTA, GPIO_PORTB, etc.).
 * @param loc_logic_mask The logic mask for the GPIO port, where each bit represents the logic 
 *        level of the corresponding pin (0 for logic low, 1 for logic high).
 * @return Std_ReturnType Error status indicating the success of setting the port logic level.
 *     - E_OK: The port logic level was set successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_port parameter).
 *
 * @note The function expects a valid GPIO port identifier passed as the @param loc_port parameter.
 * @note The @param loc_logic_mask is an 8-bit value where each bit represents the logic level 
 *       of the corresponding pin in the port. For example, bit 0 represents the logic level of 
 *       pin 0, bit 1 represents the logic level of pin 1, and so on.
 * @note This function should be called after configuring the port's direction appropriately.
 * @note The function directly modifies the LAT (Latch) register to set the port's logic level.
 */
Std_ReturnType GPIO_WritePortLogic(const port_t loc_port, const uint8 loc_logic_mask);

/** 
 * @brief Toggles the logic level of a GPIO port based on the provided configuration.
 *
 * This function toggles the logic level of a GPIO port specified by the @param loc_port parameter. 
 * It modifies the corresponding LAT (Latch) register for the specified port to toggle the logic level 
 * of all the pins in the port that are configured as outputs.
 *
 * @param loc_port The GPIO port identifier (e.g., GPIO_PORTA, GPIO_PORTB, etc.).
 * @return Std_ReturnType Error status indicating the success of toggling the port logic level.
 *     - E_OK: The port logic level was toggled successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_port parameter).
 *
 * @note The function expects a valid GPIO port identifier passed as the @param loc_port parameter.
 * @note This function should be called after configuring the port's direction appropriately.
 * @note The function directly modifies the LAT (Latch) register to toggle the port's logic level.
 * @note Pins configured as inputs will not be affected by this function.
 */
Std_ReturnType GPIO_TogglePortLogic(const port_t loc_port);

/** 
 * @brief Reads the direction of a GPIO port based on the provided configuration.
 *
 * This function reads the direction of a GPIO port specified by the @param loc_port parameter 
 * and stores the result in the memory location pointed to by the @param loc_direction_ret parameter.
 * The function reads the corresponding TRIS (Tri-State) register for the specified port to 
 * determine the direction of all the pins in the port and returns the result as an 8-bit value.
 *
 * @param loc_port The GPIO port identifier (e.g., GPIO_PORTA, GPIO_PORTB, etc.).
 * @param loc_direction_ret Pointer to an 8-bit memory location where the port direction 
 *        will be stored after the function call.
 * @return Std_ReturnType Error status indicating the success of reading the port direction.
 *     - E_OK: The port direction was read successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_port or @param loc_direction_ret).
 *
 * @note The function expects a valid GPIO port identifier passed as the @param loc_port parameter.
 * @note The @param loc_direction_ret should point to a valid memory location where the 
 *       8-bit port direction value will be stored.
 * @note This function can be used to determine the direction of all the pins in the specified port.
 * @note If an invalid @param loc_port or @param loc_direction_ret is provided, the function will return E_NOT_OK.
 */
Std_ReturnType GPIO_ReadPortDirection(const port_t loc_port, uint8 * const loc_direction_ret);

/** 
 * @brief Reads the logic levels of a GPIO port based on the provided configuration.
 *
 * This function reads the logic levels of a GPIO port specified by the @param loc_port parameter 
 * and stores the result in the memory location pointed to by the @param loc_logic_ret parameter.
 * The function reads the corresponding PORT (Latch) register for the specified port to 
 * determine the logic level of all the pins in the port and returns the result as an 8-bit value.
 *
 * @param loc_port The GPIO port identifier (e.g., GPIO_PORTA, GPIO_PORTB, etc.).
 * @param loc_logic_ret Pointer to an 8-bit memory location where the port logic levels 
 *        will be stored after the function call.
 * @return Std_ReturnType Error status indicating the success of reading the port logic levels.
 *     - E_OK: The port logic levels were read successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_port or @param loc_logic_ret).
 *
 * @note The function expects a valid GPIO port identifier passed as the @param loc_port parameter.
 * @note The @param loc_logic_ret should point to a valid memory location where the 
 *       8-bit port logic levels will be stored.
 * @note This function can be used to determine the logic level of all the pins in the specified port.
 * @note If an invalid @param loc_port or @param loc_logic_ret is provided, the function will return E_NOT_OK.
 */
Std_ReturnType GPIO_ReadPortLogic(const port_t loc_port, uint8 * const loc_logic_ret);

#endif /* _GPIO_H_ */ 