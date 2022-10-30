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
        //MCU::TWI_::send_Byte(i2c_address, addr);
        uint8_t raw_byte;
        MCU::TWI_::set_ACK_enabled();
        MCU::TWI_::send_Start();
        /*
        Serial.print(F("TWSR: 0x "));
        Serial.println(TWSR, HEX);          //0x08
        */
	    MCU::TWI_::send_SLA_W(i2c_address);
        /*
        Serial.print(F("TWSR: 0x"));
        Serial.println(TWSR, HEX);  
        */

	    MCU::TWI_::send_Data_byte(address);
        /*
        Serial.print(F("TWSR: 0x"));
        Serial.println(TWSR, HEX); 
        */              
        MCU::TWI_::send_Start();
        /*
        Serial.print(F("TWSR: 0x"));
        Serial.println(TWSR, HEX); 
        */
        MCU::TWI_::send_SLA_R(i2c_address);
        MCU::TWI_::set_ACK_disabled();

        while (!(MCU::TWI_::TWCR_::GetBit(MCU::TWI_::TWCR_::b_TWINT))); //while TWINT == 0
        /*
        Serial.print(F("TWSR: 0x"));
        Serial.println(TWSR, HEX); 
        */
        raw_byte = MCU::TWI_::TWDR_::Get();
       
        MCU::TWI_::send_Stop();
        /*
        Serial.print(F("TWSR: 0x"));
        Serial.println(TWSR, HEX); 
        */
        return raw_byte;
    }

    static void send_Byte(uint8_t reg_addr, uint8_t byte_)
    {
        MCU::TWI_::set_ACK_enabled();
        MCU::TWI_::send_Start();

        MCU::TWI_::send_SLA_W(i2c_address);
        MCU::TWI_::send_Data_byte(reg_addr);
        MCU::TWI_::send_Data_byte(byte_);
        MCU::TWI_::send_Stop();
    }
};

#endif //DS3231_REGISTER_HPP