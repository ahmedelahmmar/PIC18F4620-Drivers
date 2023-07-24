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

#define E_OK                    0x00u
#define E_NOT_OK                0x01u

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

#endif /* _STD_TYPES_H_ */
