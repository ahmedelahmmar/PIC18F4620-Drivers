/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

LCD_InitTypeDef LCD = {
    .Display.Rows = 4,
    .Display.Columns = 16,
    .Mode = LCD_MODE_4BIT,

    .D[7].Pin = GPIO_PIN0,
    .D[7].Port = GPIO_PORTD,

    .D[6].Pin = GPIO_PIN5,
    .D[6].Port = GPIO_PORTC,
  
    .D[5].Pin = GPIO_PIN4,
    .D[5].Port = GPIO_PORTC,
  
    .D[4].Pin = GPIO_PIN3,
    .D[4].Port = GPIO_PORTC,

    .E.Pin = GPIO_PIN2,
    .E.Port = GPIO_PORTC,
  
    .RW.Pin = GPIO_PIN1,
    .RW.Port = GPIO_PORTC,
  
    .RS.Pin = GPIO_PIN0,
    .RS.Port = GPIO_PORTC,
};

EUSART_InitTypeDef UART = {
    .RxInterruptHandler = APP_RX_Handler,
    .Mode = EUSART_MODE_RX,
    .Parity = EUSART_NO_PARITY,
    .BrgResolution = EUSART_BRG_RESOLUTION_16BIT,
    .BrgSpeed = EUSART_BRG_SPEED_HIGH,
    .RxDataFrame = EUSART_RX_DATA_FRAME_8BIT
};

TIMER0_InitTypeDef TIMER0 = {
    .InterruptHandler = APP_TIMER0_Handler,
    .Mode = TIMER0_MODE_TIMER,
    .Prescaler = TIMER0_PRESCALER_16,
    .Resolution = TIMER0_RESOLUTION_8BIT
};

APP_DCMOTOR_InitTypeDef APP_DcMotor = {
    .EN.Pin = GPIO_PIN0,
    .EN.Port = GPIO_PORTA,
    .IN1.Pin = GPIO_PIN2,
    .IN1.Port = GPIO_PORTA,
    .IN2.Pin = GPIO_PIN1,
    .IN2.Port = GPIO_PORTA,
};

volatile static Std_ReturnType APP_ErrorStatus = E_OK;
volatile static uint8 APP_Frame[9] = {0};

static uint8 APP_DutyCycle;
static uint8 APP_DcDirection;
static uint8 APP_StepperAngle;
static uint8 APP_StepperDirection;

static volatile APP_FrameStatusTypeDef APP_FrameStatus = APP_FRAME_NOT_OK;

int main(void)
{   
#if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
    INTERRUPTS_EnableAllHighPriorityInterrupts();
    INTERRUPTS_EnableAllLowPriorityInterrupts();
#else
    INTERRUPTS_EnableAllGlobalInterrupts();
    INTERRUPTS_EnableAllPeripheralInterrupts();
#endif 

    APP_ErrorStatus |= TIMER0_Init(&TIMER0);
    APP_ErrorStatus |= TIMER0_StartTimer(&TIMER0, 1);

    APP_ErrorStatus |= EUSART_Init(&UART, 9600);

    APP_ErrorStatus |= LCD_Init(&LCD);
    APP_ErrorStatus |= APP_DCMOTOR_Init(&APP_DcMotor);   

    APP_ErrorStatus |= LCD_ClearRow(&LCD, 0);  
    APP_ErrorStatus |= LCD_WriteFloat(&LCD, -123.456, 3);

    APP_ErrorStatus |= LCD_ClearRow(&LCD, 1);  
    APP_ErrorStatus |= LCD_WriteInt(&LCD, -69696969);   

    while (TRUE)
    {      
        if (APP_FrameStatus == APP_FRAME_OK)
        {
            APP_DCMOTOR_SetDirection(&APP_DcMotor, ('B' == APP_DcDirection) ? APP_DCMOTOR_CW : APP_DCMOTOR_ACW);
        }
    }

    return APP_ErrorStatus;
}

boolean APP_isDataFrameValid(const uint8 *Frame)
{
    if (!APP_isFrameLengthValid(Frame, 8)) return FALSE;

    if (!APP_isDutyCyleValid(Frame))  return FALSE;

    if (!APP_isDcDirectionValid(Frame)) return FALSE; 

    if (!APP_isStepperAngleValid(Frame)) return FALSE;

    if (!APP_isStepperDirectionValid(Frame)) return FALSE;

    if (!APP_isEOFValid(Frame)) return FALSE;

    return TRUE;
}

boolean APP_isDutyCyleValid(const uint8 *Frame)
{
    if ((Frame[0] - '0') > 1) return FALSE;

    for (uint8 FrameIndex = 0; FrameIndex < 3; ++FrameIndex)
    {  
        if ((Frame[FrameIndex] < 0x30) || (Frame[FrameIndex] > 0x39)) return FALSE;
    }

    uint8 loc_DutyCycle = ((Frame[0] - '0') * 100) + ((Frame[1] - '0') * 10) + (Frame[2] - '0');

    if (loc_DutyCycle > 100) return FALSE;

    APP_DutyCycle = loc_DutyCycle;

    return TRUE;
}

boolean APP_isDcDirectionValid(const uint8 *Frame)
{
    if (('B' != Frame[3]) && ('F' != Frame[3])) return FALSE;

    APP_DcDirection = Frame[3];

    return TRUE;
}

boolean APP_isStepperAngleValid(const uint8 *Frame)
{
    if ((((Frame[4] - '0') *10) + (Frame[5] - '0')) > 45) return FALSE;

    for (uint8 FrameIndex = 4; FrameIndex < 6; ++FrameIndex)
    {   
        if ((Frame[FrameIndex] < 0x30) || (Frame[FrameIndex] > 0x39)) return FALSE;
    }

    APP_StepperAngle = (((Frame[4] - '0') * 10) + (Frame[5] - '0'));

    return TRUE;
}

boolean APP_isStepperDirectionValid(const uint8 *Frame)
{
    if (('R' != Frame[6]) && ('L' != Frame[6])) return FALSE;

    APP_StepperDirection = Frame[3];

    return TRUE;  
}

boolean APP_isEOFValid(const uint8 *Frame)
{
    return ('E' == Frame[7]);
}

boolean APP_isFrameLengthValid(const uint8 *Frame, uint8 FrameLength)
{
    uint8 loc_FrameLength = 0;

    while ((*Frame++) && (loc_FrameLength <= FrameLength)) loc_FrameLength++;

    return (loc_FrameLength == FrameLength);
}

Std_ReturnType APP_DCMOTOR_Init(const APP_DCMOTOR_InitTypeDef * const DcMotorInitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != DcMotorInitPtr)
    {
        loc_ret |= GPIO_SetChannelDirection(&(DcMotorInitPtr->EN), GPIO_OUTPUT);
        loc_ret |= GPIO_SetChannelDirection(&(DcMotorInitPtr->IN1), GPIO_OUTPUT);
        loc_ret |= GPIO_SetChannelDirection(&(DcMotorInitPtr->IN2), GPIO_OUTPUT);
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType APP_DCMOTOR_SetDirection(const APP_DCMOTOR_InitTypeDef * const DcMotorInitPtr, APP_DCMOTOR_DirectionTypeDef Direction)
{
    Std_ReturnType loc_ret = E_OK;

    switch (Direction)
    {
        case APP_DCMOTOR_ACW:

            APP_ErrorStatus |= GPIO_SetChannelLogic(&(DcMotorInitPtr->IN1), GPIO_LOW);
            APP_ErrorStatus |= GPIO_SetChannelLogic(&(DcMotorInitPtr->IN2), GPIO_HIGH);
            break;
        
        case APP_DCMOTOR_CW:

            APP_ErrorStatus |= GPIO_SetChannelLogic(&(DcMotorInitPtr->IN1), GPIO_HIGH);
            APP_ErrorStatus |= GPIO_SetChannelLogic(&(DcMotorInitPtr->IN2), GPIO_LOW);
            break;

        default:
            loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

void APP_RX_Handler(void)
{
    APP_ErrorStatus |= EUSART_ReadStringBlocking(&UART, APP_Frame, 8);
 
    APP_ErrorStatus |= LCD_ClearRow(&LCD, 2);
    APP_ErrorStatus |= LCD_WriteString(&LCD, "Frame: ");
    APP_ErrorStatus |= LCD_WriteString(&LCD, APP_Frame);

    APP_FrameStatus = APP_isDataFrameValid(APP_Frame);

    if (APP_FrameStatus == APP_FRAME_OK)
    {
        APP_ErrorStatus |= LCD_ClearRow(&LCD, 0);
        APP_ErrorStatus |= LCD_WriteString(&LCD, "Speed:");
        APP_ErrorStatus |= LCD_WriteInt(&LCD, APP_DutyCycle);
        APP_ErrorStatus |= LCD_WriteChar(&LCD, '%');

        APP_ErrorStatus |= LCD_WriteString(&LCD, "Dir:");
        APP_ErrorStatus |= LCD_WriteInt(&LCD, APP_StepperAngle);

        APP_ErrorStatus |= LCD_ClearRow(&LCD, 3);
        APP_ErrorStatus |= LCD_WriteString(&LCD, "State: Accepted"); 
    }
    else
    {
        APP_ErrorStatus |= LCD_ClearRow(&LCD, 0);
        APP_ErrorStatus |= LCD_WriteString(&LCD, "Speed:");
        APP_ErrorStatus |= LCD_WriteInt(&LCD, 0);
        APP_ErrorStatus |= LCD_WriteChar(&LCD, '%');

        APP_ErrorStatus |= LCD_WriteString(&LCD, "Dir:");
        APP_ErrorStatus |= LCD_WriteInt(&LCD, 0);

        APP_ErrorStatus |= LCD_ClearRow(&LCD, 3);
        APP_ErrorStatus |= LCD_WriteString(&LCD, "State: Ignored");    
    }
}

void APP_TIMER0_Handler(void)
{
    static uint8 counter; // static local variable initialized to zero at startup

    if (APP_FrameStatus == APP_FRAME_OK)
    {
        if (0 == counter)
            APP_ErrorStatus |= GPIO_SetChannelLogic(&(APP_DcMotor.EN), GPIO_HIGH);

        if (APP_DutyCycle == counter)
            APP_ErrorStatus |= GPIO_SetChannelLogic(&(APP_DcMotor.EN), GPIO_LOW);
    }
    else { APP_ErrorStatus |= GPIO_SetChannelLogic(&(APP_DcMotor.EN), GPIO_LOW); }

    if (++counter == 100)
        counter = 0;
}