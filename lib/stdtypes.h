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

typedef unsigned char           uint8_t;
typedef signed char             sint8_t;

typedef unsigned short          uint16_t;
typedef signed short            sint16_t;

typedef unsigned long           uint32_t;
typedef signed long             sint32_t;

typedef unsigned long long      uint64_t;
typedef signed long long        sint64_t;

typedef float                   f32_t;

typedef double                  f64_t;

typedef long double             f128_t;

typedef enum {RET_OK, RET_NOK}  stdret_t;

#endif /* _STD_TYPES_H_ */
