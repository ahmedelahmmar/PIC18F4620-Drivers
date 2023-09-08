/**
 * @file TIMER3.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief TIMER3 Interface
 *
 * The TIMER3 interface provides functions and services to control and manage TIMER3, a timer module. It abstracts
 * low-level timer configurations and offers a convenient way to set up and use TIMER3 for various timing operations.
 *
 * @note Include this header file in your application code to access the TIMER3 control interface.
 * @note The file is documented, providing clear explanations for each function's purpose, parameters, return values,
 *       and usage examples.
 * @note The TIMER3 interface is designed to be portable and can be used with different microcontroller families and
 *       development environments.
 * 
 * @version 0.1
 * @date 08.09.23
 */

#ifndef _TIMER3_H_
#define _TIMER3_H_

#include "../../../lib/Std_Types.h"
#include "../../GPIO/GPIO.h"
#include "../../Interrupts/Interrupts.h"

typedef enum
{
    TIMER3_MODE_TIMER = 0,
    TIMER3_MODE_COUNTER,
    TIMER3_MODE_LIMIT

} TIMER3_ModeTypeDef;

typedef enum
{
    TIMER3_NO_PRESCALER = 0,
    TIMER3_PRESCALER_2,
    TIMER3_PRESCALER_4,
    TIMER3_PRESCALER_8,
    TIMER3_PRESCALER_LIMIT

} TIMER3_PrescalerTypeDef;

typedef struct
{
    TIMER3_ModeTypeDef Mode;
    TIMER3_PrescalerTypeDef Prescaler;

#if (INTERRUPTS_TIMER3_INTERRUPTS_FEATURE == STD_ON)
    void (*InterruptHandler)(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
    #endif
#endif

} TIMER3_InitTypeDef;

/**
 * @brief Initialize TIMER3 with the provided configuration.
 *
 * This function initializes TIMER3 based on the configuration provided in the @param InitPtr parameter. It sets up the timer's
 * mode, prescaler, and other relevant settings.
 *
 * @param InitPtr Pointer to the TIMER3 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: TIMER3 was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration parameters).
 *
 * @note This function must be called before starting or using TIMER3 for any timing operations.
 * @note The @param InitPtr parameter should point to a valid TIMER3_InitTypeDef structure with appropriate configuration settings.
 */
Std_ReturnType TIMER3_Init(const TIMER3_InitTypeDef * const InitPtr);

/**
 * @brief Deinitialize TIMER3 and reset its configuration.
 *
 * This function deinitializes TIMER3 and resets its configuration based on the settings provided in the
 * @param InitPtr parameter. It disables TIMER3 and clears any associated settings.
 *
 * @param InitPtr Pointer to the TIMER3 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the deinitialization.
 *     - E_OK: TIMER3 was deinitialized successfully.
 *     - E_NOT_OK: An error occurred during deinitialization (e.g., invalid configuration parameters).
 *
 * @note This function should be called when TIMER3 is no longer needed to free up hardware resources.
 * @note The @param InitPtr parameter should point to a valid TIMER3_InitTypeDef structure used for TIMER3 configuration.
 */
Std_ReturnType TIMER3_DeInit(const TIMER3_InitTypeDef * const InitPtr);

/**
 * @brief Start TIMER3 to generate a timed delay.
 *
 * This function starts TIMER3 to generate a timed delay based on the specified @param delay_ms parameter. It utilizes the
 * configuration provided in the @param InitPtr parameter to manage the timer operation.
 *
 * @param InitPtr Pointer to the TIMER3 initialization structure containing configuration parameters.
 * @param delay_ms The time delay to generate in milliseconds.
 * @return Std_ReturnType Error status indicating the success of starting the timer.
 *     - E_OK: TIMER3 was started successfully.
 *     - E_NOT_OK: An error occurred during timer start (e.g., invalid configuration or delay value).
 *
 * @note This function is used to generate timed delays with TIMER3.
 * @note The @param InitPtr parameter should point to a valid TIMER3_InitTypeDef structure used for TIMER3 configuration.
 * @note The @param delay_ms parameter specifies the time delay to generate in milliseconds.
 */
Std_ReturnType TIMER3_StartTimer(const TIMER3_InitTypeDef * const InitPtr, const uint32 delay_ms);

/**
 * @brief Start TIMER3 as a counter.
 *
 * This function starts TIMER3 as a counter, allowing it to count external events or pulses. It utilizes the configuration
 * provided in the @param InitPtr parameter to manage the counter operation.
 *
 * @param InitPtr Pointer to the TIMER3 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of starting the counter.
 *     - E_OK: TIMER3 was started as a counter successfully.
 *     - E_NOT_OK: An error occurred during counter start (e.g., invalid configuration).
 *
 * @note This function is used to configure and start TIMER3 as a counter.
 * @note The @param InitPtr parameter should point to a valid TIMER3_InitTypeDef structure used for TIMER3 configuration.
 * @note Once started as a counter, TIMER3 will count external events or pulses based on its configuration.
 */
Std_ReturnType TIMER3_StartCounter(const TIMER3_InitTypeDef * const InitPtr);

/**
 * @brief Write a new value to the TIMER3 counter register.
 *
 * This function writes a new value to the TIMER3 counter register, effectively updating the current count value.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage the counter value update.
 *
 * @param InitPtr Pointer to the TIMER3 initialization structure containing configuration parameters.
 * @param CounterValue The new value to be written to the TIMER3 counter register.
 * @return Std_ReturnType Error status indicating the success of writing the counter value.
 *     - E_OK: The counter value was written successfully.
 *     - E_NOT_OK: An error occurred during counter value update (e.g., invalid configuration or value).
 *
 * @note This function allows you to manually set a new value to the TIMER3 counter register.
 * @note The @param InitPtr parameter should point to a valid TIMER3_InitTypeDef structure used for TIMER3 configuration.
 * @note The @param CounterValue parameter specifies the new value to be written to the TIMER3 counter register.
 */
Std_ReturnType TIMER3_WriteCounterValue(const TIMER3_InitTypeDef * const InitPtr, const uint16 CounterValue);

/**
 * @brief Read the current value of the TIMER3 counter register.
 *
 * This function reads the current value of the TIMER3 counter register and stores it in the provided data buffer
 * pointed to by @param DataBufferPtr. It utilizes the configuration provided in the @param InitPtr parameter to manage
 * the counter value retrieval.
 *
 * @param InitPtr Pointer to the TIMER3 initialization structure containing configuration parameters.
 * @param DataBufferPtr Pointer to a variable where the current TIMER3 counter value will be stored.
 * @return Std_ReturnType Error status indicating the success of reading the counter value.
 *     - E_OK: The counter value was read successfully.
 *     - E_NOT_OK: An error occurred during counter value retrieval (e.g., invalid configuration or buffer pointer).
 *
 * @note This function retrieves and stores the current value of the TIMER3 counter register in the provided buffer.
 * @note The @param InitPtr parameter should point to a valid TIMER3_InitTypeDef structure used for TIMER3 configuration.
 * @note The @param DataBufferPtr parameter should be a pointer to a variable where the counter value will be stored.
 */
Std_ReturnType TIMER3_ReadCounterValue(const TIMER3_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr);

#endif /* _TIMER3_H_ */