/**
 * @file ADC_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief Private ADC Services
 *
 * The `ADC_Private.h` header file contains private functions and services that are meant for internal use within
 * an embedded application. These functions support the internal workings of the ADC module, handling specific
 * ADC-related tasks. By keeping them in a separate file, this interface encapsulates internal logic, enhances
 * code modularity, and provides a structured approach to managing private ADC services.
 *
 * @note Include this header file only in implementation files that require access to private ADC services.
 * @note The file is documented to clarify the purpose, input parameters, return values, and internal usage of
 *       each private function and service.
 * @note The `ADC_Private.h` interface improves code organization and maintainability by isolating internal
 *       ADC-related operations from the main public interface.
 * 
 * @version 0.1
 * @date 17.08.23
 */

#ifndef _ADC_PRIVATE_H_
#define _ADC_PRIVATE_H_

#include "../mcu_registers.h"

#define ADC_CHANNEL_PIN                                         0
#define ADC_CHANNEL_PORT                                        1

#define ADC_Enable()                                            (ADCON0bits.ADON = 1)
#define ADC_Disable()                                           (ADCON0bits.ADON = 0)

#define ADC_StartConverting()                                   (ADCON0bits.GO_nDONE = 1)
#define ADC_isConverting()                                      (1 == ADCON0bits.GO_nDONE)

#define ADC_SelectChannel(Channel)                              (ADCON0bits.CHS = Channel)    
#define ADC_ConfigChannel(ChannelConfiguration)                 (ADCON1bits.PCFG = ChannelConfiguration)
#define ADC_ConfigVref(VrefConfiguration)                       (ADCON1bits.VCFG = VrefConfiguration)
#define ADC_ConfigAlignment(AlignmentConfiguration)             (ADCON2bits.ADFM = AlignmentConfiguration)
#define ADC_ConfigAquisitionTime(AquisitionTimeConfigration)    (ADCON2bits.ACQT = AquisitionTimeConfigration)
#define ADC_ConfigPrescaler(PrescalerConfiguration)             (ADCON2bits.ADCS = PrescalerConfiguration)

#define ADC_ResultHighRegister                                  (ADRESH)
#define ADC_ResultLowRegister                                   (ADRESL)

#endif /* _ADC_PRIVATE_H_ */