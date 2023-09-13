/**
 * @file CCP1.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Header file for CCP1 module control.
 *
 * This header file defines the interface for controlling the CCP1 (Capture/Compare/PWM) module.
 * It contains function prototypes and configuration structures for managing different operating modes,
 * including capture, compare, and PWM, of the CCP1 module.
 *
 * @note Include this header file in your application code to access the CCP1 control interface.
 * @note The functions and structures defined in this header allow for flexible configuration
 *       and control of the CCP1 module on compatible microcontrollers.
 *  
 * @version 0.1
 * @date 10.09.23
 */

#ifndef _CCP1_H_
#define _CCP1_H_

#include "../CCPx_Config.h"
#include "../../GPIO/GPIO.h"
#include "../../Interrupts/Interrupts.h"
#include"../../Timers/TIMER1/TIMER1.h"
#include"../../Timers/TIMER2/TIMER2.h"
#include"../../Timers/TIMER3/TIMER3.h"

#define CCP1_CAPTURE_MODE   0x00
#define CCP1_COMPARE_MODE   0x01
#define CCP1_PWM_MODE       0x02

typedef enum
{
#if (CCP1_MODE == CCP1_CAPTURE_MODE)

    CCP1_MODE_CAPTURE_EVERY_FALLING_EDGE = 0b0100,
    CPP1_MODE_CAPTURE_EVERY_RISING_EDGE = 0b0101,
    CPP1_MODE_CAPTURE_EVERY_4th_RISING_EDGE = 0b0110,
    CPP1_MODE_CAPTURE_EVERY_16th_RISING_EDGE = 0b0111,


#elif (CCP1_MODE == CCP1_COMPARE_MODE)

    CCP1_MODE_TOGGLE_PIN_ON_MATCH = 0b0010,
    CCP1_MODE_SET_PIN_HIGH_ON_MATCH = 0b1000,
    CCP1_MODE_SET_PIN_LOW_ON_MATCH = 0b1001,
    CCP1_MODE_GENERATE_SW_INTERRUPT_ON_MATCH = 0b1010,
    CCP1_MODE_TRIGGER_SPECIAL_EVENT_ON_MATCH = 0b1011,

#elif (CCP1_MODE == CCP1_PWM_MODE)

    CCP1_MODE_PWM = 0b1100,

#endif
} CCP1_ModeTypeDef;

typedef enum
{
    CCPx_TIMER1_FOR_CCPx = 0,
    CCPx_TIMER1_FOR_CCP1_TIMER3_FOR_CPP2,
    CPPx_TIMER3_FOR_CCPx,

} CCPx_TimerResourceTypeDef;

typedef struct 
{
    CCP1_ModeTypeDef Mode;

#if (CCP1_MODE != CCP1_PWM_MODE)
    CCPx_TimerResourceTypeDef CCPxTIMERx;
#else
    TIMER2_InitTypeDef *TIMER2Ptr;
#endif

#if (INTERRUPTS_CCP1_INTERRUPTS_FEATURE == STD_ON)
    void (*InterruptHandler)(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
    #endif
#endif

} CCP1_InitTypeDef;

/**
 * @brief Initialize the CCP1 module with the provided configuration.
 *
 * This function initializes the CCP1 (Capture/Compare/PWM) module based on the configuration
 * provided in the @param InitPtr parameter. It configures the CCP1 module to operate in the specified mode
 * (e.g., capture, compare, or PWM) and sets any required parameters such as timer settings.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: The CCP1 module was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration).
 *
 * @note This function must be called before using any other CCP1 module functions.
 * @note The @param InitPtr structure should be properly configured to specify the desired operating mode and settings.
 */
Std_ReturnType CCP1_Init(const CCP1_InitTypeDef * const InitPtr);

/**
 * @brief Deinitialize the CCP1 module.
 *
 * This function deinitializes the CCP1 (Capture/Compare/PWM) module. It disables the module and clears any
 * configured settings. After calling this function, the CCP1 module is in an uninitialized state and must be
 * reinitialized using CCP1_Init before further use.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the deinitialization.
 *     - E_OK: The CCP1 module was deinitialized successfully.
 *     - E_NOT_OK: An error occurred during deinitialization (e.g., invalid configuration).
 *
 * @note This function should be called to release resources and reset the CCP1 module when it is no longer needed.
 */
Std_ReturnType CCP1_DeInit(const CCP1_InitTypeDef * const InitPtr);

#if (CCP1_MODE == CCP1_CAPTURE_MODE)

/**
 * @brief Read the captured value from the CCP1 module.
 *
 * This function reads the captured value from the CCP1 module. It is intended for use when the CCP1 module is
 * configured in capture mode. The captured value is stored in the provided @param DataBufferPtr.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @param DataBufferPtr Pointer to a variable where the captured value will be stored.
 * @return Std_ReturnType Error status indicating the success of the capture operation.
 *     - E_OK: The capture operation was successful, and the value is stored in @param DataBufferPtr.
 *     - E_NOT_OK: An error occurred during the capture operation (e.g., invalid configuration or buffer pointer).
 *
 * @note This function is intended for use when CCP1 is configured in capture mode.
 */
Std_ReturnType CCP1_ReadCapture(const CCP1_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr);

#elif (CCP1_MODE == CCP1_COMPARE_MODE)

/**
 * @brief Write a compare value to the CCP1 module.
 *
 * This function writes a compare value to the CCP1 module. It is used when the CCP1 module is configured in compare mode
 * to set the value for comparison. The provided @param CompareValue is written to the module's compare register.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @param CompareValue The value to be written to the CCP1 module's compare register.
 * @return Std_ReturnType Error status indicating the success of writing the compare value.
 *     - E_OK: The compare value was written successfully.
 *     - E_NOT_OK: An error occurred during compare value update (e.g., invalid configuration or value).
 *
 * @note This function is intended for use when CCP1 is configured in compare mode.
 */
Std_ReturnType CCP1_WriteCompareValue(const CCP1_InitTypeDef * const InitPtr, const uint16 CompareValue);

#elif (CCP1_MODE == CCP1_PWM_MODE)

/**
 * @brief Set the frequency for PWM operation of the CCP1 module.
 *
 * This function sets the frequency for PWM (Pulse-Width Modulation) operation of the CCP1 module.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @param Frequency The desired PWM frequency in Hertz (Hz).
 * @return Std_ReturnType Error status indicating the success of setting the PWM frequency.
 *     - E_OK: The PWM frequency was set successfully.
 *     - E_NOT_OK: An error occurred during PWM frequency configuration (e.g., invalid configuration or frequency).
 *
 * @note This function is intended for use when CCP1 is configured in PWM mode.
 */
Std_ReturnType CCP1_PWM_SetFrequency(const CCP1_InitTypeDef * const InitPtr, const uint32 Frequency);

/**
 * @brief Set the duty cycle for PWM operation of the CCP1 module.
 *
 * This function sets the duty cycle for PWM (Pulse-Width Modulation) operation of the CCP1 module. It adjusts the duty
 * cycle of the PWM signal output by the CCP1 module.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @param DutyCycle The desired PWM duty cycle as a percentage (0-100%).
 * @return Std_ReturnType Error status indicating the success of setting the PWM duty cycle.
 *     - E_OK: The PWM duty cycle was set successfully.
 *     - E_NOT_OK: An error occurred during PWM duty cycle configuration (e.g., invalid configuration or duty cycle).
 *
 * @note This function is intended for use when CCP1 is configured in PWM mode.
 */
Std_ReturnType CCP1_PWM_SetDutyCycle(const CCP1_InitTypeDef * const InitPtr, const uint8 DutyCycle);

/**
 * @brief Start PWM operation of the CCP1 module.
 *
 * This function starts PWM (Pulse-Width Modulation) operation of the CCP1 module. It enables the generation of the PWM
 * signal based on the configuration parameters provided in the @param InitPtr structure.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of starting PWM operation.
 *     - E_OK: PWM operation was started successfully.
 *     - E_NOT_OK: An error occurred during PWM operation start (e.g., invalid configuration).
 *
 * @note This function is intended for use when CCP1 is configured in PWM mode.
 */
Std_ReturnType CCP1_PWM_Start(const CCP1_InitTypeDef * const InitPtr);

/**
 * @brief Stop PWM operation of the CCP1 module.
 *
 * This function stops PWM (Pulse-Width Modulation) operation of the CCP1 module. It disables the generation of the PWM
 * signal based on the configuration parameters provided in the @param InitPtr structure.
 *
 * @param InitPtr Pointer to the CCP1 initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of stopping PWM operation.
 *     - E_OK: PWM operation was stopped successfully.
 *     - E_NOT_OK: An error occurred during PWM operation stop (e.g., invalid configuration).
 *
 * @note This function is intended for use when CCP1 is configured in PWM mode.
 */
Std_ReturnType CCP1_PWM_Stop(const CCP1_InitTypeDef * const InitPtr);

#else
    #warning "'CCP1_MODE' not configured in CCP1_Config.h"
#endif


#endif /* _CCP1_H_ */