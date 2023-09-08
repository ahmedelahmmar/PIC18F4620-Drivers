/**
 * @file Interrupts_Config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * 
 * @brief Interrupts Configuration
 *
 * The `Interrupts_Config.h` header file offers a centralized location to configure and manage interrupt settings
 * for an embedded application. It provides macros to customize interrupt priorities, enable or disable
 * interrupts, and set interrupt-related parameters. This interface simplifies the management of interrupt 
 * configurations, enhances code organization, and provides a convenient way to tailor interrupt behavior 
 * to specific project requirements.
 * 
 * @note The file is meticulously documented, offering clear explanations for each configuration option,
 *       parameter usage, and customization examples.
 * @note The `Interrupts_Config.h` interface promotes code adaptability and can be utilized across diverse
 *       microcontroller families and development environments.
 * 
 * @version 0.1
 * @date 01.08.23
 */

#ifndef _INTERRUPTS_CONFIG_H_
#define	_INTERRUPTS_CONFIG_H_

/**
 * @def INTERRUPTS_PRIORITY_FEATURE
 * @brief Control macro to enable or disable interrupt priority feature.
 *     - STD_ON: Enable the interrupt priority feature.
 *     - STD_OFF: Disable the interrupt priority feature.
 */
#define INTERRUPTS_PRIORITY_FEATURE                     STD_OFF

/**
 * @def INTERRUPTS_INTx_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable INTx interrupts.
 *     - STD_ON: Enable the INTx interrupts.
 *     - STD_OFF: Disable the INTx interrupts.
 */
#define INTERRUPTS_INTx_INTERRUPTS_FEATURE              STD_OFF

/**
 * @def INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable OnChange interrupts.
 *     - STD_ON: Enable the OnChange interrupts.
 *     - STD_OFF: Disable the OnChange interrupts.
 */
#define INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE         STD_OFF

/**
 * @def INTERRUPTS_ADC_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the interrupts for the ADC module.
 *     - STD_ON: Enable ADC interrupts.
 *     - STD_OFF: Disable ADC interrupts.
 */
#define INTERRUPTS_ADC_INTERRUPTS_FEATURE              STD_OFF

/**
 * @def INTERRUPTS_TIMER0_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the interrupts for Timer0.
 *     - STD_ON: Enable Timer0 interrupts.
 *     - STD_OFF: Disable Timer0 interrupts.
 */
#define INTERRUPTS_TIMER0_INTERRUPTS_FEATURE           STD_ON

/**
 * @def INTERRUPTS_TIMER1_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the interrupts for Timer1.
 *     - STD_ON: Enable Timer1 interrupts.
 *     - STD_OFF: Disable Timer1 interrupts.
 */
#define INTERRUPTS_TIMER1_INTERRUPTS_FEATURE           STD_ON

/**
 * @def INTERRUPTS_TIMER2_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the interrupts for Timer2.
 *     - STD_ON: Enable Timer2 interrupts.
 *     - STD_OFF: Disable Timer2 interrupts.
 */
#define INTERRUPTS_TIMER2_INTERRUPTS_FEATURE           STD_ON

/**
 * @def INTERRUPTS_TIMER3_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the interrupts for Timer3.
 *     - STD_ON: Enable Timer3 interrupts.
 *     - STD_OFF: Disable Timer3 interrupts.
 */
#define INTERRUPTS_TIMER3_INTERRUPTS_FEATURE           STD_ON

/**
 * @def INTERRUPTS_EUSART_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the interrupts for the EUSART module.
 *     - STD_ON: Enable EUSART interrupts.
 *     - STD_OFF: Disable EUSART interrupts.
 */
#define INTERRUPTS_EUSART_INTERRUPTS_FEATURE           STD_ON

/**
 * @def INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the transmitter interrupts for the EUSART module.
 *     - STD_ON: Enable transmitter interrupts.
 *     - STD_OFF: Disable transmitter interrupts.
 */
#define INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE         STD_OFF

/**
 * @def INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE
 * @brief Control macro to enable or disable the reciever interrupts for the EUSART module.
 *     - STD_ON: Enable reciever interrupts.
 *     - STD_OFF: Disable reciever interrupts.
 */
#define INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE         STD_ON

#endif	/* _INTERRUPTS_CONFIG_H_ */

