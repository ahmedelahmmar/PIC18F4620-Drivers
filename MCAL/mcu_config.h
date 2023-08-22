/**
 * @file mcu_config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief MCU Configuration Hub
 *
 * The `mcu_config.h` header file serves as a central configuration hub for the microcontroller unit (MCU)
 * in embedded software projects. It provides a collection of directives, constants, and macros that enable
 * customization of the MCU's behavior to match specific project requirements. By modifying settings within
 * this file, developers can optimize hardware features, define pin assignments, and configure clock settings.
 * This modular approach enhances code organization, simplifies maintenance, and promotes cross-platform adaptability.
 * Serving as a bridge between hardware and software, `mcu_config.h` facilitates tailored MCU configurations
 * while fostering code reusability and portability.
 * 
 * @version 0.1
 * @date 22.07.23
 */

#ifndef _MCU_CONFIG_H_
#define	_MCU_CONFIG_H_

#define _XTAL_FREQ          16000000UL
#define FCPU                _XTAL_FREQ

#define NUMBER_OF_PORTS             5
#define NUMBER_OF_PINS_PER_PORT     8
#define NUMBER_OF_INTx_PINS         3
#define NUMBER_OF_RBx_PINS          4

#define DELAY_MS(x)               __delay_ms(x)
#define DELAY_US(x)               __delay_us(x)

#endif	/* _MCU_CONFIG_H_ */

