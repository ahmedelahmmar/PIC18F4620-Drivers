/**
 * @file TIMER2.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief TIMER2 Interface
 *
 * The TIMER2 interface provides functions and services to control and manage TIMER2, a timer module. It abstracts
 * low-level timer configurations and offers a convenient way to set up and use TIMER2 for various timing operations.
 *
 * @note Include this header file in your application code to access the TIMER2 control interface.
 * @note The file is documented, providing clear explanations for each function's purpose, parameters, return values,
 *       and usage examples.
 * @note The TIMER2 interface is designed to be portable and can be used with different microcontroller families and
 *       development environments.
 * 
 * @version 0.1
 * @date 08.09.23
 */

#ifndef _TIMER2_H_
#define _TIMER2_H_

#include "../../../lib/Std_Types.h"
#include "../../Interrupts/Interrupts.h"

typedef enum
{
    TIMER2_MODE_NORMAL = 0,
    TIMER2_MODE_COMPARE_MATCH,
    TIMER2_MODE_LIMIT

} TIMER2_ModeTypeDef;

typedef enum
{
    TIMER2_NO_POSTSCALER = 0,
    TIMER2_POSTSCALER_2,
    TIMER2_POSTSCALER_3,
    TIMER2_POSTSCALER_4,
    TIMER2_POSTSCALER_5,
    TIMER2_POSTSCALER_6,
    TIMER2_POSTSCALER_7,
    TIMER2_POSTSCALER_8,
    TIMER2_POSTSCALER_9,
    TIMER2_POSTSCALER_10,
    TIMER2_POSTSCALER_11,
    TIMER2_POSTSCALER_12,
    TIMER2_POSTSCALER_13,
    TIMER2_POSTSCALER_14,
    TIMER2_POSTSCALER_15,
    TIMER2_POSTSCALER_16,
    TIMER2_POSTSCALER_LIMIT

} TIMER2_PostscalerTypeDef;

typedef enum
{
    TIMER2_NO_PRESCALER = 0,
    TIMER2_PRESCALER_4,
    TIMER2_PRESCALER_16 = 3,
    TIMER2_PRESCALER_LIMIT

} TIMER2_PrescalerTypeDef;

typedef struct 
{
    TIMER2_ModeTypeDef          Mode;
    TIMER2_PrescalerTypeDef     Prescaler;
    TIMER2_PostscalerTypeDef    Postscaler;

#if (INTERRUPTS_TIMER2_INTERRUPTS_FEATURE == STD_ON)
    void (*InterruptHandler)(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
    #endif
#endif
} TIMER2_InitTypeDef;

/**
 * @brief Initialize TIMER2 with the provided configuration.
 *
 * This function initializes TIMER2 based on the configuration provided in the @param InitPtr parameter. It sets up the timer's
 * mode, prescaler, and other relevant settings.
 *
 * @param InitPtr Pointer to the TIMER2 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: TIMER2 was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration parameters).
 *
 * @note This function must be called before starting or using TIMER2 for any timing operations.
 * @note The @param InitPtr parameter should point to a valid TIMER2_InitTypeDef structure with appropriate configuration settings.
 */
Std_ReturnType TIMER2_Init(const TIMER2_InitTypeDef * const InitPtr);

/**
 * @brief Deinitialize TIMER2 and reset its configuration.
 *
 * This function deinitializes TIMER2 and resets its configuration based on the settings provided in the
 * @param InitPtr parameter. It disables TIMER2 and clears any associated settings.
 *
 * @param InitPtr Pointer to the TIMER2 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the deinitialization.
 *     - E_OK: TIMER2 was deinitialized successfully.
 *     - E_NOT_OK: An error occurred during deinitialization (e.g., invalid configuration parameters).
 *
 * @note This function should be called when TIMER2 is no longer needed to free up hardware resources.
 * @note The @param InitPtr parameter should point to a valid TIMER2_InitTypeDef structure used for TIMER2 configuration.
 */
Std_ReturnType TIMER2_DeInit(const TIMER2_InitTypeDef * const InitPtr);

/**
 * @brief Start TIMER2 to generate a timed delay.
 *
 * This function starts TIMER2 to generate a timed delay based on the specified @param delay_ms parameter. It utilizes the
 * configuration provided in the @param InitPtr parameter to manage the timer operation.
 *
 * @param InitPtr Pointer to the TIMER2 initialization structure containing configuration parameters.
 * @param delay_ms The time delay to generate in milliseconds.
 * @return Std_ReturnType Error status indicating the success of starting the timer.
 *     - E_OK: TIMER2 was started successfully.
 *     - E_NOT_OK: An error occurred during timer start (e.g., invalid configuration or delay value).
 *
 * @note This function is used to generate timed delays with TIMER2.
 * @note The @param InitPtr parameter should point to a valid TIMER2_InitTypeDef structure used for TIMER2 configuration.
 * @note The @param delay_ms parameter specifies the time delay to generate in milliseconds.
 */
Std_ReturnType TIMER2_StartTimer(const TIMER2_InitTypeDef * const InitPtr, const uint32 delay_ms);

/**
 * @brief Write a new value to the TIMER2 counter register.
 *
 * This function writes a new value to the TIMER2 counter register, effectively updating the current count value.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage the counter value update.
 *
 * @param InitPtr Pointer to the TIMER2 initialization structure containing configuration parameters.
 * @param CounterValue The new value to be written to the TIMER2 counter register.
 * @return Std_ReturnType Error status indicating the success of writing the counter value.
 *     - E_OK: The counter value was written successfully.
 *     - E_NOT_OK: An error occurred during counter value update (e.g., invalid configuration or value).
 *
 * @note This function allows you to manually set a new value to the TIMER2 counter register.
 * @note The @param InitPtr parameter should point to a valid TIMER2_InitTypeDef structure used for TIMER2 configuration.
 * @note The @param CounterValue parameter specifies the new value to be written to the TIMER2 counter register.
 */
Std_ReturnType TIMER2_WriteCounterValue(const TIMER2_InitTypeDef * const InitPtr, uint8 CounterValue);

/**
 * @brief Read the current value of the TIMER2 counter register.
 *
 * This function reads the current value of the TIMER2 counter register and stores it in the provided data buffer
 * pointed to by @param DataBufferPtr. It utilizes the configuration provided in the @param InitPtr parameter to manage
 * the counter value retrieval.
 *
 * @param InitPtr Pointer to the TIMER2 initialization structure containing configuration parameters.
 * @param DataBufferPtr Pointer to a variable where the current TIMER2 counter value will be stored.
 * @return Std_ReturnType Error status indicating the success of reading the counter value.
 *     - E_OK: The counter value was read successfully.
 *     - E_NOT_OK: An error occurred during counter value retrieval (e.g., invalid configuration or buffer pointer).
 *
 * @note This function retrieves and stores the current value of the TIMER2 counter register in the provided buffer.
 * @note The @param InitPtr parameter should point to a valid TIMER2_InitTypeDef structure used for TIMER2 configuration.
 * @note The @param DataBufferPtr parameter should be a pointer to a variable where the counter value will be stored.
 */
Std_ReturnType TIMER2_ReadCounterValue(const TIMER2_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr);

/**
 * @brief Write a new value to the TIMER2 compare register.
 *
 * This function writes a new value to the TIMER2 compare register, which determines when a compare match event occurs.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage the compare value update.
 *
 * @param InitPtr Pointer to the TIMER2 initialization structure containing configuration parameters.
 * @param CompareValue The new value to be written to the TIMER2 compare register.
 * @return Std_ReturnType Error status indicating the success of writing the compare value.
 *     - E_OK: The compare value was written successfully.
 *     - E_NOT_OK: An error occurred during compare value update (e.g., invalid configuration or value).
 *
 * @note This function allows you to manually set a new value to the TIMER2 compare register.
 * @note The @param InitPtr parameter should point to a valid TIMER2_InitTypeDef structure used for TIMER2 configuration.
 * @note The @param CompareValue parameter specifies the new value to be written to the TIMER2 compare register.
 */
Std_ReturnType TIMER2_WriteCompareValue(const TIMER2_InitTypeDef * const InitPtr, uint8 CompareValue);

/**
 * @brief Read the current value of the TIMER2 compare register.
 *
 * This function reads the current value of the TIMER2 compare register and stores it in the provided data buffer
 * pointed to by @param DataBufferPtr. It utilizes the configuration provided in the @param InitPtr parameter to manage
 * the compare value retrieval.
 *
 * @param InitPtr Pointer to the TIMER2 initialization structure containing configuration parameters.
 * @param DataBufferPtr Pointer to a variable where the current TIMER2 compare value will be stored.
 * @return Std_ReturnType Error status indicating the success of reading the compare value.
 *     - E_OK: The compare value was read successfully.
 *     - E_NOT_OK: An error occurred during compare value retrieval (e.g., invalid configuration or buffer pointer).
 *
 * @note This function retrieves and stores the current value of the TIMER2 compare register in the provided buffer.
 * @note The @param InitPtr parameter should point to a valid TIMER2_InitTypeDef structure used for TIMER2 configuration.
 * @note The @param DataBufferPtr parameter should be a pointer to a variable where the compare value will be stored.
 */
Std_ReturnType TIMER2_ReadCompareValue(const TIMER2_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr);

#endif /* _TIMER2_H_ */