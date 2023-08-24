/**
 * @file EUSART_Private.h
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * 
 * @brief 
 * 
 * @version 0.1
 * @date 23.08.23
 */

#ifndef _EUSART_PRIVATE_H_
#define _EUSART_PRIVATE_H_

#include "../mcu_registers.h"
#include "../mcu_config.h"

#define ENTER                                                        0x0D
#define BACKSPACE                                                    0x08

#define EUSART_PrivEnableModule()                                    RCSTAbits.SPEN = 1;\
                                                                     TRISCbits.RC6 = 1;\
                                                                     TRISCbits.RC7 = 1

#define EUSART_PrivDisableModule()                                  (RCSTAbits.SPEN = 0)

#define EUSART_PrivEnableWakeUpMode()                               (BAUDCONbits.WUE = 1)
#define EUSART_PrivDisableWakeUpMode()                              (BAUDCONbits.WUE = 0)

#define EUSART_PrivEnableTx()                                       (TXSTAbits.TXEN = 1)
#define EUSART_PrivDisableTx()                                      (TXSTAbits.TXEN = 0)

#define EUSART_PrivEnableRx()                                       (RCSTAbits.CREN = 1)
#define EUSART_PrivDisableRx()                                      (RCSTAbits.CREN = 0)

#define EUSART_PrivEnableAsyncMode()                                (TXSTAbits.SYNC = 0)
#define EUSART_PrivEnableSyncMode()                                 (TXSTAbits.SYNC = 1)

#define EUSART_PrivSendBreakChar()                                  (TXSTAbits.SENDB = 1)
#define EUSART_PrivIsTxShiftRegEmpty()                              (TXSTA1bits.TRMT)

#define EUSART_PrivFramingErrorStatus()                             (RCSTAbits.FERR)
#define EUSART_PrivOverrunErrorStatus()                             (RCSTAbits.OERR)

#define EUSART_PrivSyncModeEnableSingleMasterRecieve()              (RCSTAbits.SREN = 1)

#define EUSART_PrivSyncModeConfigClockSource(x)                     (TXSTAbits.CSRC = x)

#define EUSART_PrivConfigTxDataFrame(x)                             (TXSTAbits.TX9 = x) 
#define EUSART_PrivConfigRxDataFrame(x)                             (RCSTAbits.RX9 = x)

#define EUSART_PrivConfigBrgResolution(x)                           (BAUDCONbits.BRG16 = x)
#define EUSART_PrivConfigBrgSpeed(x)                                (TXSTAbits.BRGH = x)
#define EUSART_PrivBrgRegisterHigh                                  (SPBRGH)
#define EUSART_PrivBrgRegisterLow                                   (SPBRG)

#define EUSART_PrivSendTxNinthBit(x)                                (TXSTA1bits.TX9D = x)
#define EUSART_PrivReadRxNinthBit()                                 (RCSTAbits.RX9D)       

#define EUSART_PrivReadRegister                                     (RCREG)
#define EUSART_PrivSendRegister                                     (TXREG)

     

#endif /* _EUSART_PRIVATE_H_ */