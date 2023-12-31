/**
 * @file Timers_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Private Timer Services
 *
 * The `Timers_Private.h` header file contains private functions and services that are meant for internal use within
 * an embedded application. These functions support the internal workings of timer modules, handling specific
 * timer-related tasks. By keeping them in a separate file, this interface encapsulates internal logic, enhances
 * code modularity, and provides a structured approach to managing private timer services.
 *
 * @note Include this header file only in implementation files that require access to private timer services.
 * @note The file is documented to clarify the purpose, input parameters, return values, and internal usage of
 *       each private function and service.
 * @note The `Timers_Private.h` interface improves code organization and maintainability by isolating internal
 *       timer-related operations from the main public interface.
 * 
 * @version 0.1
 * @date 22.08.23
 */

#ifndef _TIMERS_PRIVATE_H_
#define _TIMERS_PRIVATE_H_

#include "../mcu_registers.h"
#include "../mcu_config.h"

#define __TIMER0_Enable()                           (T0CONbits.TMR0ON = 1)
#define __TIMER0_Disable()                          (T0CONbits.TMR0ON = 0)
#define __TIMER0_ConfigResolution(x)                (T0CONbits.T08BIT = x) 
#define __TIMER0_ConfigMode(x)                      (T0CONbits.T0CS = x)
#define __TIMER0_ConfigSourceEdge(x)                (T0CONbits.T0SE = x)
#define __TIMER0_ConfigPrescaler(x)                 (T0CONbits.T0PS = x)
#define __TIMER0_DisablePrescaler()                 (T0CONbits.PSA = 1)
#define __TIMER0_EnablePrescaler()                  (T0CONbits.PSA = 0)
#define __TIMER0_CounterRegisterLow()               (TMR0L)
#define __TIMER0_CounterRegisterHigh()              (TMR0H)

#define __TIMER1_Enable()                           (T1CONbits.TMR1ON = 1)
#define __TIMER1_Disable()                          (T1CONbits.TMR1ON = 0)       
#define __TIMER1_ConfigMode(x)                      (T1CONbits.TMR1CS = x)
#define __TIMER1_ConfigPrescaler(x)                 (T1CONbits.T1CKPS = x)     
#define __TIMER1_CounterRegisterLow()               (TMR1L)
#define __TIMER1_CounterRegisterHigh()              (TMR1H)

#define __TIMER2_Enable()                           (T2CONbits.TMR2ON = 1)
#define __TIMER2_Disable()                          (T2CONbits.TMR2ON = 0)       
#define __TIMER2_ConfigPostscaler(x)                (T2CONbits.TOUTPS = x)
#define __TIMER2_ConfigPrescaler(x)                 (T2CONbits.T2CKPS = x) 
#define __TIMER2_CounterRegister()                  (TMR2)
#define __TIMER2_CompareRegister()                  (PR2)

#define __TIMER3_Enable()                           (T3CONbits.TMR3ON = 1)
#define __TIMER3_Disable()                          (T3CONbits.TMR3ON = 0)       
#define __TIMER3_ConfigMode(x)                      (T3CONbits.TMR3CS = x)
#define __TIMER3_ConfigPrescaler(x)                 (T3CONbits.T3CKPS = x)     
#define __TIMER3_CounterRegisterLow()               (TMR3L)
#define __TIMER3_CounterRegisterHigh()              (TMR3H)

#endif /* _TIMERS_PRIVATE_H_ */