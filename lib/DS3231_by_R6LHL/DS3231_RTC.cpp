#include "DS3231_RTC.hpp"

int8_t DS3231_RTC::Aging_offset::get_Value()
{
    return (int8_t)Register::get_RAW_Byte();
}

int8_t DS3231_RTC::MSB_of_temp::get_Value()
{
    return (int8_t)Register::get_RAW_Byte();
}

uint8_t DS3231_RTC::LSB_of_temp::get_Value()
{
    return (uint8_t)Register::get_RAW_Byte();
}