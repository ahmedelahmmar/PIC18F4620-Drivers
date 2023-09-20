/**
 * @file SPI.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Header file for SPI module.
 *
 * This header file defines the interface for controlling the SPI (Serial Peripheral Interface) module.
 * It contains function prototypes and configuration structures for managing SPI communication, including
 * initialization, data transmission, and reception.
 *
 * @note Include this header file in your application code to access the SPI control interface.
 * @note The functions and structures defined in this header allow for flexible configuration and control
 *       of SPI communication on compatible microcontrollers.
 * 
 * @version 0.1
 * @date 19.09.23
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "../GPIO/GPIO.h"
#include "../Interrupts/Interrupts.h"

typedef enum
{
    SPI_MODE_MASTER_PRESCALER_4 = 0,
    SPI_MODE_MASTER_PRESCALER_16,
    SPI_MODE_MASTER_PRESCALER_64,
    SPI_MODE_SLAVE_SS_ENABLED = 4,
    SPI_MODE_SLAVE_SS_DISABLED,

} SPI_ModeTypeDef;

typedef enum
{
    SPI_SAMPLE_TIME_MIDDLE_OF_DATA = 0,
    SPI_SAMPLE_TIME_END_OF_DATA,

} SPI_SampleTimeTypeDef;

typedef enum 
{
    SPI_SETUP_TIME_LEADING_EDGE = 0,
    SPI_SETUP_TIME_TRAILING_EDGE,

} SPI_SetupTimeTypeDef;

typedef enum
{
    SPI_CLOCK_POLARITY_LOW = 0,
    SPI_CLOCK_POLARITY_HIGH,

} SPI_ClockPolarityTypeDef;

typedef struct
{
    SPI_ModeTypeDef             Mode;
    SPI_ClockPolarityTypeDef    ClockPolarity;
    SPI_SetupTimeTypeDef        SetupTime;
    SPI_SampleTimeTypeDef       SampleTime;

#if (INTERRUPTS_SPI_INTERRUPTS_FEATURE == STD_ON)
    void (*InterruptHandler)(void);

    #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef  Priority;
    #endif
#endif

} SPI_InitTypeDef;

/**
 * @brief Initialize the SPI module with the provided configuration.
 *
 * This function initializes the SPI (Serial Peripheral Interface) module based on the configuration
 * provided in the @param InitPtr parameter. It sets up the SPI communication parameters such as baud rate,
 * data frame format, and clock polarity, among others.
 *
 * @param InitPtr Pointer to the SPI initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the initialization.
 *     - E_OK: The SPI module was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid configuration).
 *
 * @note This function must be called before using any other SPI module functions.
 * @note The @param InitPtr structure should be properly configured to specify the desired communication settings.
 */
Std_ReturnType SPI_Init(const SPI_InitTypeDef * const InitPtr);

/**
 * @brief Deinitialize the SPI module.
 *
 * This function deinitializes the SPI (Serial Peripheral Interface) module. It disables the module and clears any
 * configured settings. After calling this function, the SPI module is in an uninitialized state and must be
 * reinitialized using SPI_Init before further use.
 *
 * @param InitPtr Pointer to the SPI initialization structure containing configuration parameters.
 * @return Std_ReturnType Error status indicating the success of the deinitialization.
 *     - E_OK: The SPI module was deinitialized successfully.
 *     - E_NOT_OK: An error occurred during deinitialization (e.g., invalid configuration).
 *
 * @note This function should be called to release resources and reset the SPI module when it is no longer needed.
 */
Std_ReturnType SPI_DeInit(const SPI_InitTypeDef * const InitPtr);

/**
 * @brief Send data over the SPI bus.
 *
 * This function sends the provided data byte over the SPI (Serial Peripheral Interface) bus based on the
 * configuration specified in the @param InitPtr parameter.
 *
 * @param InitPtr Pointer to the SPI initialization structure containing configuration parameters.
 * @param Data The data byte to be transmitted over the SPI bus.
 * @return Std_ReturnType Error status indicating the success of the data transmission.
 *     - E_OK: The data was transmitted successfully.
 *     - E_NOT_OK: An error occurred during data transmission (e.g., SPI not initialized or busy).
 *
 * @note This function is used to send a single data byte over the SPI bus.
 * @note The recieved byte is flushed.
 */
Std_ReturnType SPI_SendData(const SPI_InitTypeDef * const InitPtr, const uint8 Data);

/**
 * @brief Read data from the SPI bus.
 *
 * This function reads a data byte from the SPI (Serial Peripheral Interface) bus based on the configuration
 * specified in the @param InitPtr parameter. The read data is stored in the provided @param DataBufferPtr.
 *
 * @param InitPtr Pointer to the SPI initialization structure containing configuration parameters.
 * @param DataBufferPtr Pointer to a variable where the read data will be stored.
 * @return Std_ReturnType Error status indicating the success of the data reception.
 *     - E_OK: Data was received successfully, and it is stored in @param DataBufferPtr.
 *     - E_NOT_OK: An error occurred during data reception (e.g., SPI not initialized or busy).
 *
 * @note This function is used to read a single data byte from the SPI bus.
 * @note A dummy byte is sent when this function is called. (0xFF)
 */
Std_ReturnType SPI_ReadData(const SPI_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr);

/**
 * @brief Exchange data over the SPI bus.
 *
 * This function sends the provided data byte over the SPI (Serial Peripheral Interface) bus and simultaneously
 * reads a data byte from the bus based on the configuration specified in the @param InitPtr parameter. The received
 * data is stored in the provided @param DataBufferPtr.
 *
 * @param InitPtr Pointer to the SPI initialization structure containing configuration parameters.
 * @param Data The data byte to be transmitted over the SPI bus.
 * @param DataBufferPtr Pointer to a variable where the received data will be stored.
 * @return Std_ReturnType Error status indicating the success of the data exchange.
 *     - E_OK: Data was exchanged successfully, and the received data is stored in @param DataBufferPtr.
 *     - E_NOT_OK: An error occurred during data exchange (e.g., SPI not initialized or busy).
 *
 * @note This function is used for bidirectional data exchange over the SPI bus.
 */
Std_ReturnType SPI_ExchangeData(const SPI_InitTypeDef * const InitPtr, const uint8 Data, uint8 * const DataBufferPtr);

#endif /* _SPI_H_ */