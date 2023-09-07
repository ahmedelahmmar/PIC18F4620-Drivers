/**
 * @file TIMER0.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief TIMER0 Interface
 *
 * The TIMER0 interface provides functions to configure and utilize the TIMER0 hardware timer on a microcontroller.
 * It abstracts low-level timer settings, offering an organized way to manage time-based operations, generate
 * precise delays, and trigger periodic events.
 *
 * @note Include this header file in your application code to access the TIMER0 control interface.
 * @note The file is documented, providing clear explanations for each function's purpose, parameters,
 *       return values, and usage examples.
 * @note The TIMER0 interface supports accurate timekeeping and timing-related tasks across different
 *       microcontroller families and development environments.
 * 
 * @version 0.1
 * @date 22.08.23
 */

#ifndef _TIMER0_H_
#define _TIMER0_H_

#include "../../../lib/Std_Types.h"
#include "../../GPIO/GPIO.h"
#include "../../Interrupts/Interrupts.h"

typedef enum
{
    TIMER0_RESOLUTION_16BIT = 0,
    TIMER0_RESOLUTION_8BIT,
    TIMER0_RESOLUTION_LIMIT

} TIMER0_ResolutionTypeDef;

typedef enum
{
    TIMER0_MODE_TIMER = 0,
    TIMER0_MODE_COUNTER,
    TIMER0_MODE_LIMIT

} TIMER0_ModeTypeDef;

typedef enum
{
    TIMER0_RISING_EDGE = 0,
    TIMER0_FALLING_EDGE,
    TIMER0_SOURCE_EDGE_LIMIT,

} TIMER0_SourceEdgeTypeDef;

typedef enum
{
    TIMER0_PRESCALER_2 = 0,
    TIMER0_PRESCALER_4,
    TIMER0_PRESCALER_8,
    TIMER0_PRESCALER_16,
    TIMER0_PRESCALER_32,
    TIMER0_PRESCALER_64,
    TIMER0_PRESCALER_128,
    TIMER0_PRESCALER_256,
    TIMER0_PRESCALER_LIMIT,
    TIMER0_NO_PRESCALER

} TIMER0_PrescalerTypeDef;

typedef struct
{
    TIMER0_ResolutionTypeDef Resolution;
    TIMER0_ModeTypeDef Mode;
    TIMER0_SourceEdgeTypeDef EdgeSelect;
    TIMER0_PrescalerTypeDef Prescaler;

#if (INTERRUPTS_TIMER0_INTERRUPTS_FEATURE == STD_ON)
    void (*InterruptHandler)(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
    #endif
#endif

} TIMER0_InitTypeDef;

/**
 * @brief Initialize the TIMER0 hardware timer.
 *
 * This function initializes the TIMER0 hardware timer based on the configuration provided in the @param InitPtr parameter.
 * It sets up the timer mode, prescaler settings, and any required interrupt configurations.
 *
 * @param InitPtr Pointer to the TIMER0 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: The TIMER0 was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration parameters).
 *
 * @note This function must be called before utilizing the TIMER0 for any timing operations.
 * @note The @param InitPtr parameter should point to a valid TIMER0_InitTypeDef structure containing appropriate
 *       configuration settings.
 */
Std_ReturnType TIMER0_Init(const TIMER0_InitTypeDef * const InitPtr);

/**
 * @brief Deinitialize the TIMER0 hardware timer.
 *
 * This function deinitializes the TIMER0 hardware timer, resetting its configuration and releasing any allocated
 * resources. It prepares the TIMER0 for reinitialization or shutdown.
 *
 * @param InitPtr Pointer to the TIMER0 initialization structure used for the deinitialization process.
 * @return Std_ReturnType Error status indicating the success of the deinitialization.
 *     - E_OK: The TIMER0 was deinitialized successfully.
 *     - E_NOT_OK: An error occurred during deinitialization (e.g., invalid configuration or resources).
 *
 * @note After calling this function, the TIMER0 module should be reinitialized before performing any timing operations.
 * @note The @param InitPtr parameter should point to a valid TIMER0_InitTypeDef structure used during the initialization.
 */
Std_ReturnType TIMER0_DeInit(const TIMER0_InitTypeDef * const InitPtr);

/**
 * @brief Start a timer with a specified delay using TIMER0.
 *
 * This function starts a timer using the TIMER0 hardware timer. The timer is configured based on the provided
 * configuration in the @param InitPtr parameter, and it is set to generate an interrupt or perform an action after
 * the specified delay in milliseconds (@param delay_ms).
 *
 * @param InitPtr Pointer to the TIMER0 initialization structure containing configuration parameters.
 * @param delay_ms Desired delay in milliseconds before the timer event occurs.
 * @return Std_ReturnType Error status indicating the success of starting the timer.
 *     - E_OK: The timer was started successfully.
 *     - E_NOT_OK: An error occurred while trying to start the timer (e.g., invalid configuration or delay).
 *
 * @note This function sets up TIMER0 for the specified delay, and the timer event will occur after the given delay.
 * @note The @param InitPtr parameter should point to a valid TIMER0_InitTypeDef structure used for the timer configuration.
 * @note The @param delay_ms parameter specifies the delay in milliseconds before the timer event occurs.
 */
Std_ReturnType TIMER0_StartTimer(const TIMER0_InitTypeDef * const InitPtr, const uint32 delay_ms);

/**
 * @brief Start the counter mode using TIMER0.
 *
 * This function starts TIMER0 in the counter mode based on the configuration provided in the @param InitPtr parameter.
 * The timer counts external events or pulses on the specified input pin.
 *
 * @param InitPtr Pointer to the TIMER0 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of starting the counter mode.
 *     - E_OK: The counter mode was started successfully.
 *     - E_NOT_OK: An error occurred during starting the counter mode (e.g., invalid configuration or resources).
 *
 * @note This function enables TIMER0 to count external events on the designated input pin.
 * @note The @param InitPtr parameter should point to a valid TIMER0_InitTypeDef structure used for the timer configuration.
 * @note The counter mode configuration specifies the source of the events to be counted (e.g., external pin pulses).
 */
Std_ReturnType TIMER0_StartCounter(const TIMER0_InitTypeDef * const InitPtr);

Std_ReturnType TIMER0_GetCounterValue(const TIMER0_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr);

#endif /* _TIMER0_H_ */