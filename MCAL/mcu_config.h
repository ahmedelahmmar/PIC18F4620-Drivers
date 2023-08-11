/**
 * @file mcu_config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Centralized MCU Configuration
 * 
 * @version 0.1
 * @date 2023-07-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _MCU_CONFIG_H_
#define	_MCU_CONFIG_H_

#define NUMBER_OF_PORTS             5
#define NUMBER_OF_PINS_PER_PORT     8
#define NUMBER_OF_INTx_PINS         3
#define NUMBER_OF_RBx_PINS          4

#define DELAY_MS(x)               __delay_ms(x)
#define DELAY_US(x)               __delay_us(x)

#endif	/* _MCU_CONFIG_H_ */

