#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Day::get_Value(void) 
{
    return Register::get_RAW_Byte();
}

void DS3231_RTC::Day::set_Value(uint8_t d)
{
    if (d > Register::day_max) d = Register::day_max;
    else if (d < Register::day_min) d = Register::day_max;

    Register::send_Byte(d);
}