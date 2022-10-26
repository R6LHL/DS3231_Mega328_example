#include "DS3231_RTC.hpp"

void DS3231_RTC::Seconds::get_Value(void)
{
    MCU::TWI_::send_Byte(i2c_address,address);
    if (MCU::TWI_::error != MCU::TWI_::Error::NO_ERROR) return;
    else 
    {
        uint8_t raw_byte;
        uint8_t sec_10;
        uint8_t sec;

        raw_byte = MCU::TWI_::read_Byte(i2c_address);

        sec_10 = raw_byte & sec_10_mask;
        sec_10 >>= sec_10_shift;
        sec_10 = sec_10 *10;

        sec = raw_byte & sec_mask;

        value = sec_10 + sec;
    }
}

void DS3231_RTC::Minutes::get_Value(void)
{
    MCU::TWI_::send_Byte(i2c_address,address);
    if (MCU::TWI_::error != MCU::TWI_::Error::NO_ERROR) return;
    else 
    {
        uint8_t raw_byte;
        uint8_t mins_10;
        uint8_t mins;

        raw_byte = MCU::TWI_::read_Byte(i2c_address);

        mins_10 = raw_byte & mins_10_mask;
        mins_10 >>= mins_10_shift;
        mins_10 = mins_10 * 10;

        mins = raw_byte & mins_mask;

        value = mins_10 + mins;
    }
}

