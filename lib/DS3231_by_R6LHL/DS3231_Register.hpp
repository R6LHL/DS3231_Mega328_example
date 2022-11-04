#ifndef DS3231_REGISTER_HPP
#define DS3231_REGISTER_HPP

#include <Arduino.h>
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
        uint8_t raw_byte;
        raw_byte = MCU::TWI_::read_Reg_Byte(i2c_address, address);
        return raw_byte;
    }

    static void send_Byte(uint8_t byte_)
    {
        MCU::TWI_::send_Reg_Byte(i2c_address, address, byte_);
    }
};

#endif //DS3231_REGISTER_HPP