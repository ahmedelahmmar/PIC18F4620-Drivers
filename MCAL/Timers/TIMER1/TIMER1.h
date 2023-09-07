/**
 * @file TIMER1.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief TIMER1 Interface
 *
 * The TIMER1 interface provides functions and services to control and manage TIMER1, a timer module. It abstracts
 * low-level timer configurations and offers a convenient way to set up and use TIMER1 for various timing operations.
 *
 * @note Include this header file in your application code to access the TIMER1 control interface.
 * @note The file is documented, providing clear explanations for each function's purpose, parameters, return values,
 *       and usage examples.
 * @note The TIMER1 interface is designed to be portable and can be used with different microcontroller families and
 *       development environments.
 * 
 * @version 0.1
 * @date 07.09.23
 */

#ifndef _TIMER1_H_
#define _TIMER1_H_

#include "../../../lib/Std_Types.h"
#include "../../GPIO/GPIO.h"
#include "../../Interrupts/Interrupts.h"

typedef enum
{
    TIMER1_MODE_TIMER = 0,
    TIMER1_MODE_COUNTER,
    TIMER1_MODE_LIMIT

} TIMER1_ModeTypeDef;

typedef enum
{
    TIMER1_NO_PRESCALER = 0,
    TIMER1_PRESCALER_2,
    TIMER1_PRESCALER_4,
    TIMER1_PRESCALER_8,
    TIMER1_PRESCALER_LIMIT

} TIMER1_PrescalerTypeDef;

typedef struct
{
    TIMER1_ModeTypeDef Mode;
    TIMER1_PrescalerTypeDef Prescaler;

#if (INTERRUPTS_TIMER1_INTERRUPTS_FEATURE == STD_ON)
    void (*InterruptHandler)(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
    #endif
#endif

} TIMER1_InitTypeDef;

/**
 * @brief Initialize TIMER1 with the provided configuration.
 *
 * This function initializes TIMER1 based on the configuration provided in the @param InitPtr parameter. It sets up the timer's
 * mode, prescaler, and other relevant settings.
 *
 * @param InitPtr Pointer to the TIMER1 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: TIMER1 was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration parameters).
 *
 * @note This function must be called before starting or using TIMER1 for any timing operations.
 * @note The @param InitPtr parameter should point to a valid TIMER1_InitTypeDef structure with appropriate configuration settings.
 */
Std_ReturnType TIMER1_Init(const TIMER1_InitTypeDef * const InitPtr);

/**
 * @brief Deinitialize TIMER1 and reset its configuration.
 *
 * This function deinitializes TIMER1 and resets its configuration based on the settings provided in the
 * @param InitPtr parameter. It disables TIMER1 and clears any associated settings.
 *
 * @param InitPtr Pointer to the TIMER1 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the deinitialization.
 *     - E_OK: TIMER1 was deinitialized successfully.
 *     - E_NOT_OK: An error occurred during deinitialization (e.g., invalid configuration parameters).
 *
 * @note This function should be called when TIMER1 is no longer needed to free up hardware resources.
 * @note The @param InitPtr parameter should point to a valid TIMER1_InitTypeDef structure used for TIMER1 configuration.
 */
Std_ReturnType TIMER1_DeInit(const TIMER1_InitTypeDef * const InitPtr);

/**
 * @brief Start TIMER1 to generate a timed delay.
 *
 * This function starts TIMER1 to generate a timed delay based on the specified @param delay_ms parameter. It utilizes the
 * configuration provided in the @param InitPtr parameter to manage the timer operation.
 *
 * @param InitPtr Pointer to the TIMER1 initialization structure containing configuration parameters.
 * @param delay_ms The time delay to generate in milliseconds.
 * @return Std_ReturnType Error status indicating the success of starting the timer.
 *     - E_OK: TIMER1 was started successfully.
 *     - E_NOT_OK: An error occurred during timer start (e.g., invalid configuration or delay value).
 *
 * @note This function is used to generate timed delays with TIMER1.
 * @note The @param InitPtr parameter should point to a valid TIMER1_InitTypeDef structure used for TIMER1 configuration.
 * @note The @param delay_ms parameter specifies the time delay to generate in milliseconds.
 */
Std_ReturnType TIMER1_StartTimer(const TIMER1_InitTypeDef * const InitPtr, const uint32 delay_ms);

/**
 * @brief Start TIMER1 as a counter.
 *
 * This function starts TIMER1 as a counter, allowing it to count external events or pulses. It utilizes the configuration
 * provided in the @param InitPtr parameter to manage the counter operation.
 *
 * @param InitPtr Pointer to the TIMER1 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of starting the counter.
 *     - E_OK: TIMER1 was started as a counter successfully.
 *     - E_NOT_OK: An error occurred during counter start (e.g., invalid configuration).
 *
 * @note This function is used to configure and start TIMER1 as a counter.
 * @note The @param InitPtr parameter should point to a valid TIMER1_InitTypeDef structure used for TIMER1 configuration.
 * @note Once started as a counter, TIMER1 will count external events or pulses based on its configuration.
 */
Std_ReturnType TIMER1_StartCounter(const TIMER1_InitTypeDef * const InitPtr);

/**
 * @brief Write a new value to the TIMER1 counter register.
 *
 * This function writes a new value to the TIMER1 counter register, effectively updating the current count value.
 * It utilizes the configuration provided in the @param InitPtr parameter to manage the counter value update.
 *
 * @param InitPtr Pointer to the TIMER1 initialization structure containing configuration parameters.
 * @param CounterValue The new value to be written to the TIMER1 counter register.
 * @return Std_ReturnType Error status indicating the success of writing the counter value.
 *     - E_OK: The counter value was written successfully.
 *     - E_NOT_OK: An error occurred during counter value update (e.g., invalid configuration or value).
 *
 * @note This function allows you to manually set a new value to the TIMER1 counter register.
 * @note The @param InitPtr parameter should point to a valid TIMER1_InitTypeDef structure used for TIMER1 configuration.
 * @note The @param CounterValue parameter specifies the new value to be written to the TIMER1 counter register.
 */
Std_ReturnType TIMER1_WriteCounterValue(const TIMER1_InitTypeDef * const InitPtr, const uint16 CounterValue);

/**
 * @brief Read the current value of the TIMER1 counter register.
 *
 * This function reads the current value of the TIMER1 counter register and stores it in the provided data buffer
 * pointed to by @param DataBufferPtr. It utilizes the configuration provided in the @param InitPtr parameter to manage
 * the counter value retrieval.
 *
 * @param InitPtr Pointer to the TIMER1 initialization structure containing configuration parameters.
 * @param DataBufferPtr Pointer to a variable where the current TIMER1 counter value will be stored.
 * @return Std_ReturnType Error status indicating the success of reading the counter value.
 *     - E_OK: The counter value was read successfully.
 *     - E_NOT_OK: An error occurred during counter value retrieval (e.g., invalid configuration or buffer pointer).
 *
 * @note This function retrieves and stores the current value of the TIMER1 counter register in the provided buffer.
 * @note The @param InitPtr parameter should point to a valid TIMER1_InitTypeDef structure used for TIMER1 configuration.
 * @note The @param DataBufferPtr parameter should be a pointer to a variable where the counter value will be stored.
 */
Std_ReturnType TIMER1_ReadCounterValue(const TIMER1_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr);

#endif /* _TIMER1_H_ */