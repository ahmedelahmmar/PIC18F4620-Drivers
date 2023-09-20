/**
 * @file SPI_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Private header file for SPI module internals.
 *
 * This private header file contains internal functions, macros, and data structures used by the SPI module.
 * These elements are not intended for direct use by external applications. They are provided here for internal
 * implementation purposes only.
 *
 * @note This header file should not be included or referenced directly in external application code.
 * @note The functions and macros defined here are part of the SPI module's internal implementation and should
 *       not be accessed externally.
 * @note External users should refer to the public SPI interface provided in "SPI.h" for SPI module control.
 * 
 * @version 0.1
 * @date 19.09.23
 */

#ifndef _SPI_PRIVATE_H_
#define _SPI_PRIVATE_H_

#include "../mcu_registers.h"

#define __SPI_Enable()                      (SSPCON1bits.SSPEN = 1)
#define __SPI_Disable()                     (SSPCON1bits.SSPEN = 0)

#define __SPI_ConfigClockPolarity(x)        (SSPCON1bits.CKP = x)
#define __SPI_ConfigSampleTime(x)           (SSPSTATbits.SMP = x)
#define __SPI_ConfigSetupTime(x)            (SSPSTATbits.CKE = x)
#define __SPI_ConfigMode(x)                 (SSPCON1bits.SSPM = x)

#define __SPI_isWriteCollisionDetected()    (SSPCON1bits.WCOL)
#define __SPI_isReadCollisionDetected()     (SSPCON1bits.SSPOV)
#define __SPI_ClearReadCollisionFlag()      (SSPCON1bits.SSPOV = 0)

#endif /* _SPI_PRIVATE_H_ */