#ifndef DS3231_REGISTER_HPP
#define DS3231_REGISTER_HPP

#include <avr/io.h>
#include <MCU_Mega_328.hpp>

template <uint8_t addr>
struct DS3231_Register
{
    static const uint8_t i2c_address = 0b11010000;
    static const uint8_t address = addr;

    static const uint8_t error = 60;

    static uint8_t get_RAW_Byte(void)
    {
        MCU::TWI_::send_Byte(i2c_address, addr);
        if (MCU::TWI_::error != MCU::TWI_::Error::NO_ERROR) return error;
        else
        {
            uint8_t raw_byte;
            raw_byte = MCU::TWI_::read_Byte(i2c_address);
            if (MCU::TWI_::error != MCU::TWI_::Error::NO_ERROR) return error;
            else return raw_byte;
        }
    }
};

#endif //DS3231_REGISTER_HPP