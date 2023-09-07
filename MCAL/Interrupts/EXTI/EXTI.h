/**
 * @file EXTI.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com) 
 * 
 * @brief External Interrupt (EXTI) Interface
 *
 * The EXTI interface simplifies the management of External Interrupt (EXTI) functionality on a microcontroller.
 * It provides functions to initialize and control interrupt sources, allowing users to effortlessly handle hardware
 * events and trigger corresponding interrupt service routines. This interface abstracts low-level EXTI configurations,
 * enhancing code clarity and offering a straightforward approach to implement interrupt-driven operations.
 *
 * @note The file is meticulously documented, providing clear explanations for each function's role, input parameters,
 *       return values, and usage demonstrations.
 * @note The EXTI interface fosters code portability and can be employed across different microcontroller families
 *       and development environments.
 *  
 * @version 0.1
 * @date 01.08.23
 */

#ifndef _EXTI_H_
#define	_EXTI_H_

#include "../../GPIO/GPIO.h"
#include "../Interrupts_Config.h"

#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
typedef enum
{
    INTERRUPTS_LOW_PRIORITY = 0,
    INTERRUPTS_HIGH_PRIORITY,
    INTERRUPTS_PRIORITY_LIMIT
            
} INTERRUPTS_PriorityTypeDef;
#endif

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
typedef enum
{
    EXTI_INT0 = 0,
    EXTI_INT1,
    EXTI_INT2
            
} EXTI_INTxTypeDef;

typedef enum
{
    EXTI_FALLING_EDGE = 0,
    EXTI_RISING_EDGE
            
} EXTI_TriggerTypeDef;

typedef struct
{
    EXTI_INTxTypeDef INTx;
    EXTI_TriggerTypeDef Trigger;
   
#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
#endif
    
    void (*InterruptHandler)(void);
    
} EXTI_INTxInitTypeDef;
#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
typedef enum
{
    EXTI_RB4 = 0,
    EXTI_RB5,
    EXTI_RB6,
    EXTI_RB7
            
} EXTI_RBxTypeDef;

typedef struct
{
    EXTI_RBxTypeDef RBx;

#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_PriorityTypeDef Priority;
#endif
    
    void (*RisingEdgeInterruptHandler)(void);
    void (*FallingEdgeInterruptHandler)(void);
    
} EXTI_RBxInitTypeDef;
#endif

#if ((INTERRUPTS_PRIORITY_FEATURE != STD_ON) && (INTERRUPTS_PRIORITY_FEATURE != STD_OFF))
#warning "'INTERRUPTS_PRIORITY_FEATURE' not configured in Interrupts_Config.h"
#endif

#if (INTERRUPTS_INTx_INTERRUPTS_FEATURE == STD_ON)
/**
 * @brief Initializes the External Interrupt (INTx) module based on the provided configuration.
 *
 * This function initializes the External Interrupt (INTx) module, specifically the interrupt source INTx,
 * using the configuration provided in the @param loc_INTx parameter. It sets up the EXTI module to monitor
 * the designated pin for the specified triggering edge and prepares it for generating interrupts.
 *
 * @param loc_INTx Pointer to the INTx configuration structure.
 * @return Std_ReturnType Error status indicating the success of initializing the INTx module.
 *     - E_OK: The INTx module was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid @param loc_INTx or configuration).
 *
 * @note The function expects a valid @param loc_INTx parameter pointing to a valid INTx configuration structure.
 * @note The INTx configuration structure should contain the necessary information to configure the EXTI module for the specified pin.
 * @note This function must be called before the INTx module can generate interrupts based on the configured edge.
 * @note If an invalid @param loc_INTx or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType EXTI_INTxInit(const EXTI_INTxInitTypeDef * const loc_INTx);

/**
 * @brief De-initializes the External Interrupt (INTx) module based on the provided configuration.
 *
 * This function de-initializes the External Interrupt (INTx) module, specifically the interrupt source INTx,
 * using the configuration provided in the @param loc_INTx parameter. It disables the EXTI module associated with
 * the designated pin, effectively stopping interrupt generation.
 *
 * @param loc_INTx Pointer to the INTx configuration structure.
 * @return Std_ReturnType Error status indicating the success of de-initializing the INTx module.
 *     - E_OK: The INTx module was de-initialized successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_INTx or configuration).
 *
 * @note The function expects a valid @param loc_INTx parameter pointing to a valid INTx configuration structure.
 * @note The INTx configuration structure should contain the necessary information to identify the EXTI module to be de-initialized.
 * @note This function should be called when the INTx module is no longer needed or during system shutdown.
 * @note De-initializing the INTx module will disable interrupt generation for the associated pin.
 * @note If an invalid @param loc_INTx or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType EXTI_INTxDeInit(const EXTI_INTxInitTypeDef * const loc_INTx);
#endif
#if ((INTERRUPTS_INTx_INTERRUPTS_FEATURE != STD_ON) && (INTERRUPTS_INTx_INTERRUPTS_FEATURE != STD_OFF))
#warning "'INTERRUPTS_INTx_INTERRUPTS_FEATURE' not configured in Interrupts_Config.h"
#endif

#if (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE == STD_ON)
/**
 * @brief Initializes the External Interrupt (EXTI) On Change feature on RBx pins based on the provided configuration.
 *
 * This function initializes the External Interrupt (EXTI) On Change feature on RBx pins using the configuration
 * provided in the @param loc_RBx parameter. It configures the EXTI module to monitor changes in logic level
 * on the designated port and bit (RBx pins) and generates interrupts accordingly.
 *
 * @param loc_RBx Pointer to the EXTI RBx configuration structure.
 * @return Std_ReturnType Error status indicating the success of initializing the EXTI On Change feature on RBx pins.
 *     - E_OK: The EXTI On Change feature on RBx pins was initialized successfully.
 *     - E_NOT_OK: An error occurred during initialization (e.g., invalid @param loc_RBx or configuration).
 *
 * @note The function expects a valid @param loc_RBx parameter pointing to a valid EXTI RBx configuration structure.
 * @note The EXTI RBx configuration structure should contain the necessary information to configure the EXTI module
 *       for the specified RBx pins on the designated port.
 * @note This function must be called before the EXTI On Change feature on RBx pins can generate interrupts based on
 *       changes in the logic level of the specified port and bit.
 * @note If an invalid @param loc_RBx or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType EXTI_RBxInit(const EXTI_RBxInitTypeDef * const loc_RBx);

/**
 * @brief De-initializes the External Interrupt (EXTI) On Change feature on RBx pins based on the provided configuration.
 *
 * This function de-initializes the External Interrupt (EXTI) On Change feature on RBx pins using the configuration
 * provided in the @param loc_RBx parameter. It disables the EXTI module associated with the designated port and bit (RBx pins),
 * effectively stopping interrupt generation for the On Change feature.
 *
 * @param loc_RBx Pointer to the EXTI RBx configuration structure.
 * @return Std_ReturnType Error status indicating the success of de-initializing the EXTI On Change feature on RBx pins.
 *     - E_OK: The EXTI On Change feature on RBx pins was de-initialized successfully.
 *     - E_NOT_OK: An error occurred during the process (e.g., invalid @param loc_RBx or configuration).
 *
 * @note The function expects a valid @param loc_RBx parameter pointing to a valid EXTI RBx configuration structure.
 * @note The EXTI RBx configuration structure should contain the necessary information to identify the EXTI module to be de-initialized.
 * @note This function should be called when the EXTI On Change feature on RBx pins is no longer needed or during system shutdown.
 * @note De-initializing the EXTI On Change feature will disable interrupt generation for the associated port and bit.
 * @note If an invalid @param loc_RBx or configuration is provided, the function will return E_NOT_OK.
 */
Std_ReturnType EXTI_RBxDeInit(const EXTI_RBxInitTypeDef * const loc_RBx);
#endif
#if ((INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE != STD_ON) && (INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE != STD_OFF))
#warning "'INTERRUPTS_ON_CHANGE_INTERRUPTS_FEATURE' not configured in Interrupts_Config.h"
#endif

#endif	/* _EXTI_H_ */

