#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/**
 * @def CPU_TYPE
 * @brief CPU Type Selection Macro
 *
 * The `CPU_TYPE` macro is defined to select the appropriate CPU type based on the platform's architecture.
 * It should be defined as one of the values: `CPU_TYPE_8`, `CPU_TYPE_16`, `CPU_TYPE_32`, or `CPU_TYPE_64`.
 * This macro aids in determining the correct data types and memory requirements for different platforms.
 */

#define CPU_TYPE                CPU_TYPE_8

/**
 * @def CPU_BIT_ORDER
 * @brief CPU Bit Order Selection Macro
 *
 * The `CPU_BIT_ORDER` macro is defined to select the appropriate bit order based on the platform's
 * architecture. It should be defined as one of the values: `MSB_FIRST` or `LSB_FIRST`. This macro aids
 * in configuring data transmission order for different platforms.
 */
#define CPU_BIT_ORDER           LSB_FIRST

/**
 * @def CPU_BYTE_ORDER
 * @brief CPU Byte Order Selection Macro
 *
 * The `CPU_BYTE_ORDER` macro is defined to select the appropriate byte order based on the platform's
 * architecture. It should be defined as one of the values: `HIGH_BYTE_FIRST` or `LOW_BYTE_FIRST`.
 * This macro aids in configuring data transmission order for multi-byte values on different platforms.
 */

#define CPU_BYTE_ORDER          LOW_BYTE_FIRST

typedef unsigned char           boolean;

#ifndef FALSE
#define FALSE                  (boolean)0x00u
#endif

#ifndef TRUE
#define TRUE                   (boolean)0x01u
#endif

#ifndef NULL
#define NULL                   ((void*)0)
#endif

#define CPU_TYPE_8              8
#define CPU_TYPE_32             32
#define CPU_TYPE_16             16
#define CPU_TYPE_64             64

#define MSB_FIRST               0
#define LSB_FIRST               1

#define HIGH_BYTE_FIRST         0
#define LOW_BYTE_FIRST          1

typedef unsigned char           uint8;
typedef unsigned char           uint8_least;
typedef signed char             sint8;
typedef signed char             sint8_least;

typedef unsigned short          uint16;
typedef unsigned short          uint16_least;
typedef signed short            sint16;
typedef signed short            sint16_least;

typedef unsigned long           uint32;
typedef unsigned long           uint32_least;
typedef signed long             sint32;
typedef signed long             sint32_least;

typedef unsigned long long      uint64;
typedef signed long long        sint64;

typedef float                   float32;
typedef double                  float64;

typedef void*                   VoidPtr;
typedef const void*             ConstVoidPtr;

#endif