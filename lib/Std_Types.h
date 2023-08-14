/**
 * @file Std_Types.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief AUTOSAR Standard Data Types
 *
 * The `Std_Types.h` header file provides a standardized set of data types as defined by the AUTOSAR specification.
 * These data types ensure consistent representation of data across different microcontroller platforms and compilers.
 * The header includes commonly used types like boolean, integer, and floating-point types, enhancing code
 * portability and compatibility.
 *
 * @note Include this header file in your application code to access the AUTOSAR standard data types.
 * @note The file conforms to the AUTOSAR specification, ensuring consistency across different automotive systems.
 * @note The `Std_Types.h` header simplifies code development by offering a unified set of data types that
 *       remain consistent across different microcontroller families and development environments.
 */

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

#ifndef FALSE
#define FALSE					0
#endif /* FALSE */

#ifndef TRUE
#define TRUE					1
#endif /* TRUE */

#ifndef NULL
#define NULL					((void*)0)
#endif /* NULL */

#ifndef NULL_PTR
#define NULL_PTR                ((void*)0)
#endif /* NULL_PTR */

#define STD_IDLE                0x00u
#define STD_ACTIVE              0x01u

#define STD_OFF                 0x00u
#define STD_ON                  0x01u

#define STD_LOW                 0x00u
#define STD_HIGH                0x01u

typedef unsigned char           uint8;
typedef signed char             sint8;

typedef unsigned short          uint16;
typedef signed short            sint16;

typedef unsigned long           uint32;
typedef signed long             sint32;

typedef unsigned long long      uint64;
typedef signed long long        sint64;

typedef float                   float32;

typedef double                  float64;

typedef long double             float128;

typedef uint8                   Std_ReturnType;

#define E_OK                   (Std_ReturnType)0x00u
#define E_NOT_OK               (Std_ReturnType)0x01u

#endif /* _STD_TYPES_H_ */
