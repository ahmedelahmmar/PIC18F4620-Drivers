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

#define TIMER0_PrivEnable()                         (T0CONbits.TMR0ON = 1)
#define TIMER0_PrivDisable()                        (T0CONbits.TMR0ON = 0)
        
#define TIMER0_PrivConfigResolution(x)              (T0CONbits.T08BIT = x) 
#define TIMER0_PrivConfigMode(x)                    (T0CONbits.T0CS = x)
#define TIMER0_PrivConfigSourceEdge(x)              (T0CONbits.T0SE = x)
#define TIMER0_PrivConfigPrescaler(x)               (T0CONbits.T0PS = x)
        
#define TIMER0_PrivEnablePrescaler()                (T0CONbits.PSA = 0)
#define TIMER0_PrivDisablePrescaler()               (T0CONbits.PSA = 1)

#define TIMER0_PrivCounterRegisterLow               (TMR0L)
#define TIMER0_PrivCounterRegisterHigh              (TMR0H)

#endif /* _TIMERS_PRIVATE_H_ */