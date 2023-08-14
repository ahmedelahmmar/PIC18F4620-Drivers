/**
 * @file EEPROM.c
 * @author Ahmed Alaa (4hmedalaa@gmail.com)
 * @version 0.1
 * @date 13.08.23
 */

#include "EEPROM_Private.h"
#include "EEPROM.h"

static void EEPROM_WriteAddressToAddressRegisters(const uint16 loc_addres);
static void EEPROM_InitPreWritingSequence(void);

Std_ReturnType EEPROM_ReadByte(const uint16 loc_address, uint8 * const loc_data_ret)
{
    Std_ReturnType loc_ret = E_OK;

    if (NULL != loc_data_ret)
    {
        EEPROM_WriteAddressToAddressRegisters(loc_address);

        EEPROM_PointToEEPROM();
        EEPROM_AccessEEPROM();

        EEPROM_Read();

        // two no instruction operations are required for latency at high clock frequencies.
        NOP();
        NOP();

        *loc_data_ret = EEPROM_DataRegister;
    }
    else
    {
        loc_ret = E_NOT_OK;
    }

    return loc_ret;
}

Std_ReturnType EEPROM_WriteByte(const uint16 loc_address, const uint8 loc_data)
{
    Std_ReturnType loc_ret = E_OK;

    EEPROM_WriteAddressToAddressRegisters(loc_address);

    EEPROM_DataRegister = loc_data;

    EEPROM_PointToEEPROM();
    EEPROM_AccessEEPROM();

    EEPROM_EnableWriting();

    uint8 loc_globalInterruptsStatus = INTERRUPTS_GlobalInterruptsFlag;
    INTERRUPTS_DisableAllGlobalInterrupts();

    // Critical Section
    EEPROM_InitPreWritingSequence();
    EEPROM_Write();
    while (EEPROM_isWriting());

    INTERRUPTS_GlobalInterruptsFlag = loc_globalInterruptsStatus;

    EEPROM_DisableWriting();

    return loc_ret;
}

static void EEPROM_WriteAddressToAddressRegisters(const uint16 loc_addres)
{
    EEPROM_LowerAddressRegister = (uint8)(loc_addres & EEPROM_LowerAddressRegisterMask);
    EEPROM_HigherAddressRegister = (uint8)((loc_addres >> 8) & EEPROM_HigherAddressRegisterMask);
}

static void EEPROM_InitPreWritingSequence(void)
{
    EECON2 = 0x55;
    EECON2 = 0xAA;
}