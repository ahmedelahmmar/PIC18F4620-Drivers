/**
 * @file CCPx_Config.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief
 *  
 * @version 0.1
 * @date 10.09.23
 */

#ifndef _CCPx_CONFIG_H_
#define _CCPx_CONFIG_H_

/**
 * @def CCP1_MODE
 * @brief Control macro used to specify the operational mode of the CCP1 module.
 * 
 * This control macro allows the selection of the desired operating mode for the CCP1 (Capture/Compare/PWM) module.
 * The following modes are available:
 * 
 * - CCP1_CAPTURE_MODE: In this mode, the CCP1 module operates as a capture module, allowing the measurement of external events.
 * - CCP1_COMPARE_MODE: This mode configures the CCP1 module to function as a compare module for generating output based on comparisons.
 * - CCP1_PWM_MODE    : This mode sets up the CCP1 module to operate as a Pulse-Width Modulation (PWM) generator.
 */
#define CCP1_MODE           CCP1_PWM_MODE

/**
 * @def CCP2_MODE
 * @brief Control macro used to specify the operational mode of the CCP2 module.
 * 
 * This control macro allows the selection of the desired operating mode for the CCP2 (Capture/Compare/PWM) module.
 * The following modes are available:
 * 
 * - CCP2_CAPTURE_MODE: In this mode, the CCP2 module operates as a capture module, allowing the measurement of external events.
 * - CCP2_COMPARE_MODE: This mode configures the CCP2 module to function as a compare module for generating output based on comparisons.
 * - CCP2_PWM_MODE    : This mode sets up the CCP2 module to operate as a Pulse-Width Modulation (PWM) generator.
 */
#define CCP2_MODE           CCP2_PWM_MODE

#endif /* _CCPx_CONFIG_H_ */