/**
 * @file PushButton.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * @version 0.1
 * @date July 27, 2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _PUSH_BUTTON_H_
#define	_PUSH_BUTTON_H_

#include "../../MCAL/GPIO/GPIO.h"

typedef enum 
{
    PUSHBUTTON_RELEASED = 0, 
    PUSHBUTTON_PRESSED
            
} PUSHBUTTON_StatusTypeDef;

typedef enum 
{
    PUSHBUTTON_ACTIVE_LOW = 0, 
    PUSHBUTTON_ACTIVE_HIGH
            
} PUSHBUTTON_ConfigTypeDef;

typedef struct
{
    GPIO_InitTypeDef Channel;
    PUSHBUTTON_StatusTypeDef Status;
    PUSHBUTTON_ConfigTypeDef Configuration;
    
} PUSHBUTTON_InitTypeDef;

/**
 * @brief Initializes a push button based on the provided configuration.
 *
 * This function initializes a push button specified by the @param loc_button parameter.
 * It sets up the GPIO channel and any necessary hardware settings to enable push button functionality.
 *
 * @param loc_button Pointer to the push button configuration structure.
 * @return Std_ReturnType Error status indicating the success of initializing the push button.
 *     - E_OK: The push button was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid @param loc_button or configuration).
 *
 * @note The function expects a valid @param loc_button parameter pointing to a valid push button configuration structure.
 * @note The push button configuration structure should contain the necessary information to configure the GPIO channel for the button.
 * @note This function must be called before using the push button for any operations.
 * @note If an invalid @param loc_button or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType PUSHBUTTON_Init(const PUSHBUTTON_InitTypeDef * const loc_button);

/**
 * @brief Refreshes the status of a push button based on the provided configuration.
 *
 * This function refreshes the status of a push button specified by the @param loc_button parameter.
 * It reads the current state of the button and updates the status in the push button configuration.
 *
 * @param loc_button Pointer to the push button configuration structure.
 * @return Std_ReturnType Error status indicating the success of refreshing the push button status.
 *     - E_OK: The push button status was refreshed successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_button or configuration).
 *
 * @note The function expects a valid @param loc_button parameter pointing to a valid push button configuration structure.
 * @note The push button configuration structure should contain the necessary information to identify the button.
 * @note This function should be used periodically to update the push button status if it is monitored continuously.
 * @note The function reads the current state of the push button and updates the status in the configuration.
 * @note If an invalid @param loc_button or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType PUSHBUTTON_RefreshStatus(PUSHBUTTON_InitTypeDef * const loc_button);

/**
 * @brief Retrieves the current status of a push button based on the provided configuration.
 *
 * This function retrieves the current status of a push button specified by the @param loc_button parameter
 * and stores the result in the memory location pointed to by the @param loc_status_ret parameter.
 * The function reads the actual state of the push button, which may differ from the last known state
 * stored in the push button configuration.
 *
 * @param loc_button Pointer to the push button configuration structure.
 * @param loc_status_ret Pointer to a PUSHBUTTON_StatusTypeDef variable where the push button status
 *        will be stored after the function call.
 * @return Std_ReturnType Error status indicating the success of reading the push button status.
 *     - E_OK: The push button status was retrieved successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_button or @param loc_status_ret).
 *
 * @note The function expects a valid @param loc_button parameter pointing to a valid push button configuration structure.
 * @note The @param loc_status_ret should point to a valid PUSHBUTTON_StatusTypeDef variable where the
 *       push button status value will be stored.
 * @note This function can be used to read the real-time status of the push button, which may have changed since initialization.
 * @note If an invalid @param loc_button or @param loc_status_ret is provided, the function will return E_NOT_OK.
 */
Std_ReturnType PUSHBUTTON_GetStatus(const PUSHBUTTON_InitTypeDef * const loc_button, PUSHBUTTON_StatusTypeDef * const loc_status_ret);

#endif	/* _PUSH_BUTTON_H_ */

