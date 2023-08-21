/**
 * @file StandardTypes.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief AUTOSAR Standard Data Types
 *
 * The `StandardTypes.h` header file provides a standardized set of data types as defined by the AUTOSAR specification.
 * These data types ensure consistent representation of data across different microcontroller platforms and compilers.
 * The header includes commonly used types like boolean, integer, and floating-point types, enhancing code
 * portability and compatibility.
 *
 * @note Include this header file in your application code to access the AUTOSAR standard data types.
 * @note The file conforms to the AUTOSAR specification, ensuring consistency across different automotive systems.
 * @note The `StandardTypes.h` header simplifies code development by offering a unified set of data types that
 *       remain consistent across different microcontroller families and development environments.
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"

typedef struct
{
    uint16 vendorID;
    uint16 moduleID;

    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
    
} Std_VersionInfoType;

typedef uint8                           Std_TransformerErrorCode;
typedef uint8                           Std_TransformerClass;

#define STD_TRANSFORMER_UNSPECIFIED    (Std_TransformerClass)0x00u; /* Transformer of an unspecified transformer class. */
#define STD_TRANSFORMER_SERIALIZER     (Std_TransformerClass)0x01u; /* Transformer of a serializer class. */
#define STD_TRANSFORMER_SAFETY         (Std_TransformerClass)0x02u; /* Transformer of a safety class. */
#define STD_TRANSFORMER_SECURITY       (Std_TransformerClass)0x03u; /* Transformer of a security class. */
#define STD_TRANSFORMER_CUSTOM         (Std_TransformerClass)0xFFu; /* Transformer of a custom class not standardized by AUTOSAR. */

typedef struct
{
    Std_TransformerErrorCode errorCode;
    Std_TransformerClass transformerClass;

} Std_TransformerError;



#define NULL_PTR                        ((void*)0)

#define STD_IDLE                        0x00u /* Logical state idle */
#define STD_ACTIVE                      0x01u /* Logical state active */

#define STD_OFF                         0x00u
#define STD_ON                          0x01u

#define STD_LOW                         0x00u /* Physical state 0V */
#define STD_HIGH                        0x01u /* Physical state 5V or 3.3V */

typedef uint8                           Std_ReturnType;

#ifndef STATUSTYPEDEFINED 
#define STATUSTYPEDEFINED 

#define E_OK                           (Std_ReturnType)0x00u
typedef unsigned char                   StatusType; /* OSEK compliance */

#endif

#define E_NOT_OK                       (Std_ReturnType)0x01u

#endif /* STD_TYPES_H */
