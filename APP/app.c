/**
 * @file app.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 22.07.23
 */

#include "app.h"

void CCP1_Handler(void);

TIMER2_InitTypeDef TIMER2 = {
    .Mode = TIMER2_MODE_NORMAL,
    .Prescaler = TIMER2_PRESCALER_16,
    .Postscaler = TIMER2_POSTSCALER_10,
};

CCP1_InitTypeDef CCP1 = {
    .Mode = CCP1_MODE_PWM,
    .TIMER2Ptr = &TIMER2,
    .InterruptHandler = CCP1_Handler,
};

Std_ReturnType ErrorStatus = E_OK;

int main(void)
{
    INTI_EnableInterrupts();

    TIMER2_Init(&TIMER2);
    CCP1_Init(&CCP1);

    CCP1_PWM_SetFrequency(&CCP1, 500);
    CCP1_PWM_SetDutyCycle(&CCP1, 75);

    CCP1_PWM_Start(&CCP1);

    while (1)
    {

    }

    return 0;
}

void CCP1_Handler(void)
{

}
