#ifndef DS3231_REGISTER_HPP
#define DS3231_REGISTER_HPP

#include <avr/io.h>
#include <MCU_Mega_328.hpp>

template <uint8_t addr>
struct DS3231_Register
{   
    static const uint8_t i2c_address = 0b11010000; //0x68
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
            MCU::TWI_::send_Stop();
            if (MCU::TWI_::error != MCU::TWI_::Error::NO_ERROR) return error;
            else return raw_byte;
        }
    }

    static void send_Byte(uint8_t reg_addr, uint8_t byte_)
    {
        MCU::TWI_::send_Reg_Byte(i2c_address, reg_addr, byte_);
    }
};

#endif //DS3231_REGISTER_HPP