#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Year::get_Value()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    uint8_t year_10 = raw_byte & Register::year_10_mask;
    year_10 >>=  Register::year_10_shift;
    year_10 = year_10 * 10;

    uint8_t year = raw_byte & Register::year_mask;
    return year_10 + year;
}

void DS3231_RTC::Year::set_Value(uint8_t y)
{
    if (y > Register::year_max) y = Register::year_max;
    else if (y < Register::year_min) y = Register::year_min;

    uint8_t msb = y / 10;
    uint8_t lsb = y % 10;

    msb <<= 4;
    msb &= Register::year_10_mask;

    lsb &= Register::year_mask;
    Register::send_Byte(msb+lsb);
}