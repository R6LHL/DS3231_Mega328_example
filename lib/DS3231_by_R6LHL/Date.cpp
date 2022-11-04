#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Date::get_Value(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    uint8_t date_10 = raw_byte & Register::date_10_mask;
    date_10 >>= Register::date_10_shift;
    date_10 = date_10 * 10;

    uint8_t date = raw_byte & Register::date_mask;
    return date_10 + date;
}

void DS3231_RTC::Date::set_Value(uint8_t d)
{
    if (d > Register::date_max) d = Register::date_mask;
    else if (d < Register::date_min) d = Register::date_min;
    
    uint8_t msb = d / 10;
    uint8_t lsb = d % 10;

    Register::send_Byte(msb+lsb);
}