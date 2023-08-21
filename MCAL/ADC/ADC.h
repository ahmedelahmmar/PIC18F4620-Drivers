/**
 * @file ADC.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Analog-to-Digital Converter (ADC) Interface
 *
 * The ADC interface provides functions to manage the Analog-to-Digital Converter module on a microcontroller.
 * It offers functions for configuring ADC channels, initiating conversions, and reading digital values from
 * analog inputs. This interface abstracts low-level ADC configurations, enhancing code clarity and simplifying
 * analog data acquisition.
 *
 * @note Include this header file in your application code to access the ADC control interface.
 * @note The file is documented, offering clear insights into each function's purpose, input parameters,
 *       return values, and usage examples.
 * @note The ADC interface promotes efficient analog data processing and can be utilized across different
 *       microcontroller families and development environments.
 * 
 * @version 0.1
 * @date 17.08.23
 */

#ifndef _ADC_H_
#define _ADC_H_

#include "../Interrupts/Interrupts.h"

typedef enum
{
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_LIMIT

} ADC_ChannelTypeDef;

typedef enum
{
    ADC_VREF_INTERNAL = 0,
    ADC_VREF_EXTERNAL = 4

} ADC_VrefTypeDef;

typedef enum
{
    ADC_ALL_CHANNELS_ANALOG = 2,
    ADC_CHANNEL_11_AND_BELOW_ANALOG,
    ADC_CHANNEL_10_AND_BELOW_ANALOG,
    ADC_CHANNEL_9_AND_BELOW_ANALOG,
    ADC_CHANNEL_8_AND_BELOW_ANALOG,
    ADC_CHANNEL_7_AND_BELOW_ANALOG,
    ADC_CHANNEL_6_AND_BELOW_ANALOG,
    ADC_CHANNEL_5_AND_BELOW_ANALOG,
    ADC_CHANNEL_4_AND_BELOW_ANALOG,
    ADC_CHANNEL_3_AND_BELOW_ANALOG,
    ADC_CHANNEL_2_AND_BELOW_ANALOG,
    ADC_CHANNEL_1_AND_BELOW_ANALOG,
    ADC_CHANNEL_0_ANALOG,
    ADC_ALL_CHANNELS_DIGITAL,
    ADC_CHANNEL_CONFIG_LIMIT

} ADC_ChannelConfigTypeDef;

typedef enum
{
    ADC_ALIGN_LEFT = 0,
    ADC_ALIGN_RIGHT

} ADC_ResultAlignmentTypeDef;

typedef enum
{
    ADC_AQT_DEFAULT_TAD = 0,
    ADC_AQT_2TAD,
    ADC_AQT_4TAD,
    ADC_AQT_6TAD,
    ADC_AQT_8TAD,
    ADC_AQT_12TAD,
    ADC_AQT_16TAD,
    ADC_AQT_20TAD,
    ADC_AQT_LIMIT

} ADC_AquisitionTimeTypeDef;

typedef enum
{
    ADC_PRESCALER_2 = 0,
    ADC_PRESCALER_8,
    ADC_PRESCALER_32,
    ADC_PRESCALER_RC_OSC,
    ADC_PRESCALER_4,
    ADC_PRESCALER_16,
    ADC_PRESCALER_64,
//  ADC_PRESCALER_RC_OSC can be both 3 or 7.
    ADC_PRESCALER_LIMIT = 8

} ADC_PrescalerTypeDef;

typedef struct
{
    ADC_ChannelConfigTypeDef ChannelConfiguration;
    ADC_VrefTypeDef Vref;
    ADC_AquisitionTimeTypeDef AquisitionTime;
    ADC_PrescalerTypeDef Prescaler;
    ADC_ResultAlignmentTypeDef ResultAlignment;

#if (INTERRUPTS_ADC_INTERRUPTS_FEAUTURE == STD_ON)
    void (*InterruptHandler)(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
    #endif

#endif
} ADC_InitTypeDef;

typedef uint16 ADC_ValueTypeDef;

/**
 * @brief Initialize the Analog-to-Digital Converter (ADC) module.
 *
 * This function initializes the ADC module based on the configuration provided in the @param InitPtr parameter.
 * It sets up the ADC channels, conversion parameters, and any required hardware settings.
 *
 * @param InitPtr Pointer to the ADC initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: The ADC module was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration parameters).
 *
 * @note This function must be called before using any ADC conversion functionality.
 * @note The @param InitPtr parameter should point to a valid ADC_InitTypeDef structure containing appropriate
 *       configuration settings.
 */
Std_ReturnType ADC_Init(const ADC_InitTypeDef * const InitPtr);

/**
 * @brief Deinitialize the Analog-to-Digital Converter (ADC) module.
 *
 * This function deinitializes the ADC module, resetting its configuration and releasing any allocated resources.
 * It prepares the ADC module for reinitialization or shutdown.
 *
 * @return Std_ReturnType Error status indicating the success of the deinitialization.
 *     - E_OK: The ADC module was deinitialized successfully.
 *     - E_NOT_OK: An error occurred during deinitialization.
 *
 * @note After calling this function, the ADC module should be reinitialized before performing any ADC operations.
 */
Std_ReturnType ADC_DeInit(void);

/**
 * @brief Start an ADC conversion on the specified channel.
 *
 * This function initiates an ADC conversion on the specified channel defined by the @param Channel parameter.
 * It triggers the ADC to sample the analog input signal and start the conversion process.
 *
 * @param Channel The ADC channel identifier where the conversion will be performed.
 * @return Std_ReturnType Error status indicating the success of starting the conversion.
 *     - E_OK: The ADC conversion was started successfully.
 *     - E_NOT_OK: An error occurred while trying to start the conversion (e.g., invalid channel).
 *
 * @note Before calling this function, the ADC module should be initialized using the ADC_Init function.
 * @note The @param Channel parameter should correspond to a valid ADC channel identifier.
 * 
 * @note If the ADC interrupts are disabled, the function enters a blocking state until the conversion is done and
 *       the user should read the results using ADC_Read after calling this function.
 *       However if the ADC interrupts are enabled then the user should use ADC_Read in the ADC's interrupt handler.
 */
Std_ReturnType ADC_StartConversion(const ADC_ChannelTypeDef Channel);

/**
 * @brief Read the converted value from the Analog-to-Digital Converter (ADC).
 *
 * This function reads the converted value from the ADC module based on the provided ADC configuration in the
 * @param InitPtr parameter. The converted value is stored in the memory location pointed to by the @param DataBufferPtr
 * parameter.
 *
 * @param InitPtr Pointer to the ADC initialization structure containing configuration parameters.
 * @param DataBufferPtr Pointer to the memory location where the converted ADC value will be stored.
 * @return Std_ReturnType Error status indicating the success of the read operation.
 *     - E_OK: The ADC value was read successfully.
 *     - E_NOT_OK: An error occurred during the read operation (e.g., invalid configuration or buffer pointer).
 *
 * @note This function should be called after a successful ADC conversion initiated by the ADC_StartConversion function.
 * @note The @param InitPtr parameter should point to a valid ADC_InitTypeDef structure matching the configuration
 *       used for the conversion.
 * @note The @param DataBufferPtr parameter should point to a valid memory location where the ADC value will be stored.
 */
Std_ReturnType ADC_Read(const ADC_InitTypeDef * const InitPtr, ADC_ValueTypeDef * const DataBufferPtr);

#endif /* _ADC_H_ */