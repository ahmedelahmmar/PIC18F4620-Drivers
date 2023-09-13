/**
 * @file CCPx_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief
 *  
 * @version 0.1
 * @date 10.09.23
 */

#ifndef _CCPX_PRIVATE_H_
#define _CCPX_PRIVATE_H_

#include "../mcu_registers.h"

#define __CCPx_SelectTimerResource(x)                       T3CONbits.T3CCP2 = (x & 0x02);\
                                                            T3CONbits.T3CCP1 = (x & 0x01)

#define __CCPx_EnableTimer2()                               (T2CONbits.TMR2ON = 1)

#define __CCP1_Disable()                                    (CCP1CONbits.CCP1M = 0)
#define __CCP1_ConfigMode(x)                                (CCP1CONbits.CCP1M = x)
#define __CCP1_SetDutyCycleLower2Bits(x)                    (CCP1CONbits.DC1B = x)
#define __CCP1_RegisterLow()                                (CCPR1L)
#define __CCP1_RegisterHigh()                               (CCPR1H)

#define __CCP2_Disable()                                    (CCP2CONbits.CCP2M = 0)
#define __CCP2_ConfigMode(x)                                (CCP2CONbits.CCP2M = x)
#define __CCP2_SetDutyCycleLower2Bits(x)                    (CCP2CONbits.DC2B = x)
#define __CCP2_RegisterLow()                                (CCPR2L)
#define __CCP2_RegisterHigh()                               (CCPR2H)

#endif /* _CPPX_PRIVATE_H_ */