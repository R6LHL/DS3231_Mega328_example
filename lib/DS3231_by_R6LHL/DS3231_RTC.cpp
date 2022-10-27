#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Seconds::get_Value(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    uint8_t sec_10;
    uint8_t sec;

    sec_10 = raw_byte & sec_10_mask;
    sec_10 >>= sec_10_shift;
    sec_10 = sec_10 * 10;

    sec = raw_byte & sec_mask;
    return sec_10 + sec;

}

uint8_t DS3231_RTC::Minutes::get_Value(void)
{
    uint8_t raw_byte;
    uint8_t mins_10;
    uint8_t mins;

    mins_10 = raw_byte & mins_10_mask;
    mins_10 >>= mins_10_shift;
    mins_10 = mins_10 * 10;

    mins = raw_byte & mins_mask;
    return mins_10 + mins;
}

uint8_t DS3231_RTC::Hours::get_Value(void)
{
    MCU::TWI_::send_Byte(i2c_address,address);
    if (MCU::TWI_::error != MCU::TWI_::Error::NO_ERROR) return hours_error;
    else
    {
        uint8_t raw_byte;
        bool c24;
        uint8_t hours10;
        uint8_t hours;

        raw_byte = MCU::TWI_::read_Byte(i2c_address);
        c24 = raw_byte & c12_24_mask;
        is_pm = raw_byte & am_pm_mask;

        if (c24 == true)
        {
            hours10 = raw_byte & hours_24_mask;
            hours10 >>= hours_24_shift;
        }
        else
        {
            hours10 = raw_byte & hours_12_mask;
            hours10 >>= hours_12_shift;
        }

        hours10 = hours * 10;
        hours = raw_byte & hours_mask;

        return hours10 + hours;
    }
}

uint8_t DS3231_RTC::Day::get_Value(void)
{
    MCU::TWI_::send_Byte(i2c_address,address);
    if (MCU::TWI_::error != MCU::TWI_::Error::NO_ERROR) return day_error;
    else return MCU::TWI_::read_Byte(i2c_address);
}

