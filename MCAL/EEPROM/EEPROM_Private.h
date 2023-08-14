/**
 * @file EEPROM_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Private EEPROM Services
 *
 * The EEPROM_Private.h header file contains private functions and services that are meant for internal use
 * within an embedded application. These functions support the internal workings of the EEPROM module, handling
 * specific EEPROM-related tasks. By keeping them in a separate file, this interface encapsulates internal logic,
 * enhances code modularity, and provides a structured approach to managing private EEPROM services.
 *
 * @note Include this header file only in implementation files that require access to private EEPROM services.
 * @note The file is documented to clarify the purpose, input parameters, return values, and internal usage of
 *       each private function and service.
 * @note The EEPROM_Private.h interface improves code organization and maintainability by isolating internal
 *       EEPROM-related operations from the main public interface.
 * 
 * @version 0.1
 * @date 13.08.23
 */

#ifndef _EEPROM_PRIVATE_H_
#define _EEPROM_PRIVATE_H_

#include "EEPROM.h"
#include <../proc/pic18f4620.h>
#include <../pic18.h>

#define EEPROM_DataRegister                         (EEDATA)
#define EEPROM_LowerAddressRegister                 (EEADR)
#define EEPROM_LowerAddressRegisterMask             (0xFF)

#define EEPROM_HigherAddressRegister                (EEADRH)
#define EEPROM_HigherAddressRegisterMask            (0x03)

#define EEPROM_PointToEEPROM()                      (EECON1bits.EEPGD = 0)
#define EEPROM_AccessEEPROM()                       (EECON1bits.CFGS = 0)

#define EEPROM_Read()                               (EECON1bits.RD = 1)
#define EEPROM_isReading()                          (1 == EECON1bits.RD)

#define EEPROM_EnableWriting()                      (EECON1bits.WREN = 1)
#define EEPROM_DisableWriting()                     (EECON1bits.WREN = 0)
#define EEPROM_Write()                              (EECON1bits.WR = 1)
#define EEPROM_isWriting()                          (1 == EECON1bits.WR)

#endif