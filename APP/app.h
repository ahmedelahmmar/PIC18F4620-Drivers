/**
 * @file app.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#ifndef _APP_H_
#define _APP_H_

#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/Interrupts/Interrupts.h"
#include "../MCAL/EEPROM/EEPROM.h"
#include "../MCAL/Timers/TIMER0/TIMER0.h"
#include "../MCAL/EUSART/EUSART.h"

#include "../ECUAL/LCD/LCD.h"

typedef struct
{
    GPIO_InitTypeDef EN;
    GPIO_InitTypeDef IN1;
    GPIO_InitTypeDef IN2;

} APP_DCMOTOR_InitTypeDef;

typedef enum
{
    APP_DCMOTOR_ACW = 0,
    APP_DCMOTOR_CW
} APP_DCMOTOR_DirectionTypeDef;

typedef enum
{
    APP_FRAME_NOT_OK = 0,
    APP_FRAME_OK
} APP_FrameStatusTypeDef;


void APP_RX_Handler(void);
void APP_TIMER0_Handler(void);

boolean APP_isDataFrameValid(const uint8 *Frame);
boolean APP_isDutyCyleValid(const uint8 *Frame);
boolean APP_isDcDirectionValid(const uint8 *Frame);
boolean APP_isStepperAngleValid(const uint8 *Frame);
boolean APP_isStepperDirectionValid(const uint8 *Frame);
boolean APP_isEOFValid(const uint8 *Frame);
boolean APP_isFrameLengthValid(const uint8 *Frame, uint8 FrameLength);

Std_ReturnType APP_DCMOTOR_Init(const APP_DCMOTOR_InitTypeDef * const DcMotorInitPtr);
Std_ReturnType APP_DCMOTOR_SetDirection(const APP_DCMOTOR_InitTypeDef * const DcMotorInitPtr, APP_DCMOTOR_DirectionTypeDef Direction);

#endif /* _APP_H_ */