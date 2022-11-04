#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Alarm1Day_Date::get_Value()
{
    uint8_t raw_byte = Register::get_RAW_Byte();

    Register::is_a1m4_set = raw_byte & Register::a1m4_mask;
    Register::is_date = raw_byte & Register::day_date_mask;

    uint8_t day_or_date;

    if (Register::is_date == true) return (day_or_date & Register::date_mask);
    else return  day_or_date & Register::day_mask;
}

void DS3231_RTC::Alarm1Day_Date::set_Day(uint8_t day)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::day_mask;
    Register::send_Byte(raw_byte);
    set_day_alarm();
}

void DS3231_RTC::Alarm1Day_Date::set_Date(uint8_t date)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::date_mask;
    Register::send_Byte(raw_byte);
    set_date_alarm();
}

void DS3231_RTC::Alarm1Day_Date::set_day_alarm(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_dy_dt);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Alarm1Day_Date::set_date_alarm(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_dy_dt);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Alarm1Day_Date::set_a1m4(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_a1m4);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Alarm1Day_Date::clear_a1m4(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_a1m4);
    Register::send_Byte(raw_byte);
}