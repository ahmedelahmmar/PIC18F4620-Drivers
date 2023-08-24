/**
 * @file EUSART.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 23.08.23
 */

#include "EUSART_Private.h"
#include "EUSART.h"

#if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)

    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
    static void (*EUSART_TxInterruptHandler)(void) = NULL_PTR;
    #endif

    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
    static void (*EUSART_RxInterruptHandler)(void) = NULL_PTR;
    static void (*EUSART_FrameErrorInterruptHandler)(void) = NULL_PTR;
    static void (*EUSART_OverrunErrorInterruptHandler)(void) = NULL_PTR;
    #endif

static Std_ReturnType EUSART_InitInterruptHandlers(const EUSART_InitTypeDef * const loc_initPtr);
static Std_ReturnType EUSART_DeInitInterruptHandlers(void);
#endif

static Std_ReturnType EUSART_InitBaudRate(const EUSART_InitTypeDef * const loc_initPtr, const uint32 loc_baudrate);

Std_ReturnType EUSART_Init(const EUSART_InitTypeDef * const InitPtr, const uint32 BaudRate)
{
    Std_ReturnType loc_ret = E_OK;

#if (EUSART_SYNCHRONOUS_MODE == STD_OFF)

    if (NULL_PTR != InitPtr)
    {
        EUSART_PrivDisableModule();

        loc_ret = EUSART_InitBaudRate(InitPtr, BaudRate);

        EUSART_PrivEnableAsyncMode();

        #if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
        loc_ret |= EUSART_InitInterruptHandlers(InitPtr);
        #endif

        switch (InitPtr->Mode)
        {
            case EUSART_MODE_TXRX:
                EUSART_PrivEnableTx();
                EUSART_PrivEnableRx();

                #if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
                    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
                    INTI_EUSART_EnableTxInterrupt();

                        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
                        INTI_EUSART_SetTxPriority(InitPtr->TxHandlerPriority);
                        #endif
                    #endif

                    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
                    INTI_EUSART_EnableRxInterrupt();

                        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
                        INTI_EUSART_SetRxPriority(InitPtr->RxHandlerPriority);
                        #endif
                    #endif

                #endif
                break;

            case EUSART_MODE_TX:
                EUSART_PrivEnableTx();

                #if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
                    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
                    INTI_EUSART_EnableTxInterrupt();

                        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
                        INTI_EUSART_SetTxPriority(InitPtr->TxHandlerPriority);
                        #endif
                    #endif
                #endif
                break;

            case EUSART_MODE_RX:
                EUSART_PrivEnableRx();
                
                #if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
                    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
                    INTI_EUSART_EnableRxInterrupt();

                        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
                        INTI_EUSART_SetRxPriority(InitPtr->RxHandlerPriority);
                        #endif
                    #endif
                #endif
                break;

            default:
                loc_ret = E_NOT_OK;
        }

        if ((InitPtr->TxDataFrame < EUSART_TX_DATA_FRAME_LIMIT) && (InitPtr->RxDataFrame < EUSART_RX_DATA_FRAME_LIMIT))
        {
            EUSART_PrivConfigTxDataFrame(InitPtr->TxDataFrame);
            EUSART_PrivConfigRxDataFrame(InitPtr->RxDataFrame);
        }
        else { loc_ret = E_NOT_OK; }

        EUSART_PrivEnableModule();
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

#elif (EUSART_SYNCHRONOUS_MODE == STD_ON)

#endif
    return loc_ret;
}

Std_ReturnType EUSART_DeInit(const EUSART_InitTypeDef * const InitPtr)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL_PTR != InitPtr)
    {
        EUSART_PrivDisableModule();
        EUSART_PrivDisableRx();
        EUSART_PrivDisableTx();
        EUSART_PrivDisableWakeUpMode();

        #if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
        loc_ret |= EUSART_DeInitInterruptHandlers();

            #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
            INTI_EUSART_DisableTxInterrupt();
                #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
                INTI_EUSART_DeInitTxPriority();
                #endif

            #endif

            #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
            INTI_EUSART_DisableRxInterrupt();
                #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
                INTI_EUSART_DeInitRxPriority();
                #endif
            #endif
        #endif
    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

//Parity
Std_ReturnType EUSART_SendDataFrameBlocking(const EUSART_InitTypeDef * const InitPtr, const uint16 Data)
{
    Std_ReturnType loc_ret = E_OK;

    switch (InitPtr->TxDataFrame)
    {
        case EUSART_TX_DATA_FRAME_8BIT:

            switch (InitPtr->Parity)
            {
                case EUSART_NO_PARITY:

                    while (!EUSART_PrivIsTxShiftRegEmpty());
                    EUSART_PrivSendRegister = (uint8)(Data & 0xFF);

                    break;  

                case EUSART_PARITY_ODD:
                    break;

                case EUSART_PARITY_EVEN:
                    break;

                default:
                    loc_ret = E_NOT_OK;
            }

            break;

        case EUSART_TX_DATA_FRAME_9BIT:

                while (!EUSART_PrivIsTxShiftRegEmpty());
                EUSART_PrivSendTxNinthBit(((Data >> 8) & 1));
                EUSART_PrivSendRegister = (uint8)(Data & 0xFF);

            break;

        default:
            loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType EUSART_SendDataFrameNonBlocking(const EUSART_InitTypeDef * const InitPtr, const uint16 Data);

Std_ReturnType EUSART_SendStringBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const String);
Std_ReturnType EUSART_SendStringNonBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const String);

Std_ReturnType EUSART_ReadDataFrameBlocking(const EUSART_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr)
{
    Std_ReturnType loc_ret = E_OK;

    switch (InitPtr->RxDataFrame)
    {
        case EUSART_RX_DATA_FRAME_8BIT:

            switch (InitPtr->Parity)
            {
                case EUSART_NO_PARITY:
                    
                    while (!INTI_EUSART_RxFlag());
                    
                    *DataBufferPtr = (uint8)(EUSART_PrivReadRegister);

                    break;  

                case EUSART_PARITY_ODD:
                    break;

                case EUSART_PARITY_EVEN:
                    break;

                default:
                    loc_ret = E_NOT_OK;
            }

            break;

        case EUSART_RX_DATA_FRAME_9BIT:

                while (!INTI_EUSART_RxFlag());

                *DataBufferPtr = (uint16)(EUSART_PrivReadRxNinthBit() << 8);
                *DataBufferPtr |= (uint8)(EUSART_PrivReadRegister);

            break;

        default:
            loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType EUSART_ReadDataFrameNonBlocking(const EUSART_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr);

Std_ReturnType EUSART_ReadStringBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr, const uint8 maxLen)
{
    Std_ReturnType loc_ret = E_OK;

    uint8 loc_charCounter = 0;
    volatile uint8 loc_buffer = 0;

    switch (InitPtr->RxDataFrame)
    {
        case EUSART_RX_DATA_FRAME_8BIT:

            switch (InitPtr->Parity)
            {
                case EUSART_NO_PARITY:
                    
                    do
                    {
                        while (!(INTI_EUSART_RxFlag()));
                        loc_buffer = EUSART_PrivReadRegister;

                        if ((loc_buffer == BACKSPACE) && (loc_charCounter > 0))
                        {
                            loc_charCounter--;
                        }

                        if ((loc_buffer != ENTER) && (loc_buffer != BACKSPACE))
                        {
                            DataBufferPtr[loc_charCounter++] = loc_buffer;
                        }          
                    }
                    while ((loc_buffer != ENTER) && (loc_charCounter < (maxLen - 1)));
                    DataBufferPtr[loc_charCounter] = '\0';

                    break;  

                case EUSART_PARITY_ODD:
                    break;

                case EUSART_PARITY_EVEN:
                    break;

                default:
                    loc_ret = E_NOT_OK;
            }

            break;

        default:
            loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType EUSART_ReadStringNonBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr, const uint8 maxLen);

static Std_ReturnType EUSART_InitBaudRate(const EUSART_InitTypeDef * const loc_initPtr, const uint32 loc_baudrate)
{
    Std_ReturnType loc_ret = E_OK;

    if ((loc_initPtr->BrgSpeed < EUSART_BRG_SPEED_LIMIT) && (loc_initPtr->BrgResolution < EUSART_BRG_RESOLUTION_LIMIT))
    {
       EUSART_PrivConfigBrgSpeed(loc_initPtr->BrgSpeed);
       EUSART_PrivConfigBrgResolution(loc_initPtr->BrgResolution);

#if (EUSART_SYNCHRONOUS_MODE == STD_OFF)

       switch (loc_initPtr->BrgResolution)
       {
            case EUSART_BRG_RESOLUTION_8BIT:
                
                if (EUSART_BRG_SPEED_LOW == loc_initPtr->BrgSpeed)
                {
                    EUSART_PrivBrgRegisterLow = (uint8)( FOSC / (uint32)(64 * (loc_baudrate + 1)));
                }
                else if (EUSART_BRG_SPEED_HIGH == loc_initPtr->BrgSpeed)
                {
                    EUSART_PrivBrgRegisterLow = (uint8)( FOSC / (uint32)(16 * (loc_baudrate + 1)));
                }

                break;

            case EUSART_BRG_RESOLUTION_16BIT:

                if (EUSART_BRG_SPEED_LOW == loc_initPtr->BrgSpeed)
                {
                    uint16 loc_brgVal = (uint16)( FOSC / (uint32)(16 * (loc_baudrate + 1)));

                    EUSART_PrivBrgRegisterHigh = (uint8)(loc_brgVal >> 8);
                    EUSART_PrivBrgRegisterLow = (uint8)(loc_brgVal & 0xFF);
                }
                else if (EUSART_BRG_SPEED_HIGH == loc_initPtr->BrgSpeed)
                {
                    uint16 loc_brgVal = (uint16)( FOSC / (uint32)(4 * (loc_baudrate + 1)));

                    EUSART_PrivBrgRegisterHigh = (uint8)(loc_brgVal >> 8);
                    EUSART_PrivBrgRegisterLow = (uint8)(loc_brgVal & 0xFF); 
                }

                break;

            default:
                loc_ret = E_NOT_OK;
       }

#elif (EUSART_SYNCHRONOUS_MODE == STD_ON)

        uint16 loc_brgVal = (uint16)( FOSC / (uint32)(4 * (loc_baudrate + 1)));

        if (EUSART_BRG_RESOLUTION_16BIT == loc_initPtr->BrgResolution)
        {
            EUSART_PrivBrgRegisterHigh = (uint8)(loc_brgVal >> 8);
        }

        EUSART_PrivBrgRegisterLow = (uint8)(loc_brgVal & 0xFF);

#endif

    }
    else 
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

#if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
static Std_ReturnType EUSART_InitInterruptHandlers(const EUSART_InitTypeDef * const loc_initPtr)
{
    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
    EUSART_TxInterruptHandler = loc_initPtr->TxInterruptHandler;
    #endif

    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
    EUSART_RxInterruptHandler = loc_initPtr->RxInterruptHandler;
    EUSART_FrameErrorInterruptHandler = loc_initPtr->FrameErrorInterruptHandler;
    EUSART_OverrunErrorInterruptHandler = loc_initPtr->OverrunErrorInterruptHandler;
    #endif

    return E_OK;
}

static Std_ReturnType EUSART_DeInitInterruptHandlers(void)
{
    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
    EUSART_TxInterruptHandler = NULL_PTR;
    #endif

    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
    EUSART_RxInterruptHandler = NULL_PTR;
    EUSART_FrameErrorInterruptHandler = NULL_PTR;
    EUSART_OverrunErrorInterruptHandler = NULL_PTR;
    #endif

    return E_OK;
}

#if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
void EUSART_RX_ISR(void)
{
    if (NULL_PTR != EUSART_RxInterruptHandler)
    {
        EUSART_RxInterruptHandler();
    }

    if (NULL_PTR != EUSART_FrameErrorInterruptHandler)
    {
        EUSART_FrameErrorInterruptHandler();
    }

    if (NULL_PTR != EUSART_OverrunErrorInterruptHandler)
    {
        EUSART_OverrunErrorInterruptHandler();
    }    
}
#endif

#if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
void EUSART_TX_ISR(void)
{
    if (NULL_PTR != EUSART_TxInterruptHandler)
    {
        EUSART_TxInterruptHandler();
    }  
}
#endif

#endif