/**
 * @file EEPROM.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Internal EEPROM Interface
 *
 * The EEPROM interface simplifies working with the microcontroller's internal Electrically Erasable Programmable
 * Read-Only Memory (EEPROM). It offers functions to read and write data to the EEPROM, enabling easy storage of
 * critical configuration settings, calibration data, and other essential information. This interface abstracts
 * low-level EEPROM interactions, enhancing code readability and providing a seamless way to manage non-volatile data.
 *
 * @note Include this header file in your application code to access the EEPROM control interface.
 * @note The file is comprehensively documented, offering clear insights into each function's purpose, parameters,
 *       return values, and usage examples.
 * @note The EEPROM interface promotes code portability and can be utilized across various microcontroller families
 *       and development environments.
 * 
 * @version 0.1
 * @date 13.08.23
 */

#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "../Interrupts/Interrupts.h"

/**
 * @brief Reads a byte of data from the internal EEPROM memory.
 *
 * This function reads a byte of data from the internal Electrically Erasable Programmable Read-Only Memory (EEPROM)
 * at the specified memory @param loc_address and stores the result in the memory location pointed to by @param loc_data_ret.
 *
 * @param loc_address Memory address to read from in the EEPROM.
 * @param loc_data_ret Pointer to a uint8 variable where the read data will be stored.
 * @return Std_ReturnType Error status indicating the success of the read operation.
 *     - E_OK: The byte of data was read successfully.
 *     - E_NOT_OK: An error occurred during the read operation (e.g., invalid @param loc_data_ret).
 *
 * @note The @param loc_data_ret should point to a valid uint8 variable where the read data will be stored.
 * @note If an invalid @param loc_data_ret is provided, the function will return E_NOT_OK.
 */
Std_ReturnType EEPROM_ReadByte(const uint16 loc_address, uint8 * const loc_data_ret);

/**
 * @brief Writes a byte of data to the internal EEPROM memory.
 *
 * This function writes a byte of data to the internal Electrically Erasable Programmable Read-Only Memory (EEPROM)
 * at the specified memory @param loc_address with the provided data @param loc_data.
 *
 * @param loc_address Memory address to write to in the EEPROM.
 * @param loc_data Data byte to be written to the specified memory address.
 * @return Std_ReturnType Error status indicating the success of the write operation.
 *     - E_OK: The byte of data was written successfully.
 *     - E_NOT_OK: An error occurred during the write operation (e.g., data write failure).
 *
 * @note The @param loc_data should contain the byte of data to be written.
 */
Std_ReturnType EEPROM_WriteByte(const uint16 loc_address, const uint8 loc_data);


#endif