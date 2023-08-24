/**
 * @file EUSART.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief 
 * 
 * @version 0.1
 * @date 23.08.23
 */

#ifndef _EUSART_H_
#define _EUSART_H_

#include "../Interrupts/Interrupts.h"
#include "EUSART_Config.h"

typedef enum
{
#if (EUSART_SYNCHRONOUS_MODE == STD_OFF)

    EUSART_MODE_TXRX = 0,
    EUSART_MODE_TX,
    EUSART_MODE_RX,
    EUSART_MODE_LIMIT

#elif (EUSART_SYNCHRONOUS_MODE == STD_ON)

    EUSART_MODE_SLAVE = 0,
    EUSART_MODE_MASTER,
    EUSART_MODE_LIMIT

#endif

} EUSART_ModeTypeDef;

typedef enum
{
    EUSART_BRG_RESOLUTION_8BIT = 0,
    EUSART_BRG_RESOLUTION_16BIT,
    EUSART_BRG_RESOLUTION_LIMIT

} EUSART_BrgResolutionTypeDef;

typedef enum
{
    EUSART_BRG_SPEED_LOW = 0,
    EUSART_BRG_SPEED_HIGH,
    EUSART_BRG_SPEED_LIMIT

} EUSART_BrgSpeedTypeDef;

typedef enum
{
    EUSART_TX_DATA_FRAME_8BIT = 0,
    EUSART_TX_DATA_FRAME_9BIT,
    EUSART_TX_DATA_FRAME_LIMIT

} EUSART_TxDataFrameTypeDef;

typedef enum
{
    EUSART_RX_DATA_FRAME_8BIT = 0,
    EUSART_RX_DATA_FRAME_9BIT,
    EUSART_RX_DATA_FRAME_LIMIT

} EUSART_RxDataFrameTypeDef;

typedef enum
{
    EUSART_NO_PARITY = 0,
    EUSART_PARITY_ODD,
    EUSART_PARITY_EVEN,
    EUSART_PARITY_LIMIT

} EUSART_ParityTypeDef;

typedef struct 
{
    EUSART_ModeTypeDef              Mode;
    EUSART_TxDataFrameTypeDef       TxDataFrame;
    EUSART_RxDataFrameTypeDef       RxDataFrame;
    EUSART_ParityTypeDef            Parity;
    EUSART_BrgResolutionTypeDef     BrgResolution;
    EUSART_BrgSpeedTypeDef          BrgSpeed;

#if (INTERRUPTS_EUSART_INTERRUPTS_FEATURE == STD_ON)
    #if (INTERRUPTS_EUSART_TX_INTERRUPTS_FEATURE == STD_ON)
    void (*TxInterruptHandler)(void);
    
        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        INTERRUPTS_PriorityTypeDef      TxHandlerPriority; 
        #endif
    #endif

    #if (INTERRUPTS_EUSART_RX_INTERRUPTS_FEATURE == STD_ON)
    void (*RxInterruptHandler)(void);
    void (*FrameErrorInterruptHandler)(void);
    void (*OverrunErrorInterruptHandler)(void);

        #if (INTERRUPTS_PRIORITY_FEATURE == STD_ON)
        INTERRUPTS_PriorityTypeDef      RxHandlerPriority; 
        #endif
    #endif
#endif
} EUSART_InitTypeDef;

Std_ReturnType EUSART_Init(const EUSART_InitTypeDef * const InitPtr, const uint32 BaudRate);
Std_ReturnType EUSART_DeInit(const EUSART_InitTypeDef * const InitPtr);

Std_ReturnType EUSART_SendDataFrameBlocking(const EUSART_InitTypeDef * const InitPtr, const uint16 Data);
Std_ReturnType EUSART_SendDataFrameNonBlocking(const EUSART_InitTypeDef * const InitPtr, const uint16 Data);

Std_ReturnType EUSART_SendStringBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const String);
Std_ReturnType EUSART_SendStringNonBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const String);

Std_ReturnType EUSART_ReadDataFrameBlocking(const EUSART_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr);
Std_ReturnType EUSART_ReadDataFrameNonBlocking(const EUSART_InitTypeDef * const InitPtr, uint16 * const DataBufferPtr);

Std_ReturnType EUSART_ReadStringBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr, const uint8 maxLen);
Std_ReturnType EUSART_ReadStringNonBlocking(const EUSART_InitTypeDef * const InitPtr, uint8 * const DataBufferPtr, const uint8 maxLen);

#endif /* _EUSART_H_ */