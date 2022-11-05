#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Alarm2Hours::get_Value()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    bool c24;
    uint8_t hours10;
    uint8_t hours;

    c24 = raw_byte & Register::c12_24_mask;
    Register::is_pm = raw_byte & Register::am_pm_mask;

    Register::is_a2m3_set = raw_byte & Register::a2m3_mask;

    if (c24 == false)
    {
        hours10 = raw_byte & Register::hours_24_mask;
        hours10 >>= Register::hours_24_shift;
    }
    else
    {
        hours10 = raw_byte & Register::hours_12_mask;
        hours10 >>= Register::hours_12_shift;
    }

    hours10 = hours10 * 10;
    hours = raw_byte & Register::hours_mask;

    return hours10 + hours;
}

void DS3231_RTC::Alarm2Hours::set_Value(uint8_t h)
{
    if (get_c12_24() == 0)
    {
        if (h > Register::hours_24_max) h = Register::hours_24_max;
        else if (h < Register::hours_24_min) h = Register::hours_24_min;
    }
    else
    {
        if (h > Register::hours_12_max) h = Register::hours_12_max;
        else if (h < Register::hours_12_min) h = Register::hours_12_min;
    }
        
    uint8_t msb = h / 10;
    uint8_t lsb = h % 10;
    
    msb <<= 4;
    
    lsb &= Register::hours_mask;

    Register::send_Byte(msb+lsb);
}

void DS3231_RTC::Alarm2Hours::set_12_mode()
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ |= (1<<Register::b_c12_24);
    Register::send_Byte(byte_);
}

void DS3231_RTC::Alarm2Hours::set_24_mode()
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ &= ~(1<<Register::b_c12_24);
    Register::send_Byte(byte_);
}

void DS3231_RTC::Alarm2Hours::set_am(void)
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ &= ~(1<<Register::b_am_pm);
    Register::send_Byte(byte_);
}

void DS3231_RTC::Alarm2Hours::set_pm(void)
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ |= (1<<Register::b_am_pm);
    Register::send_Byte(byte_);
}

void DS3231_RTC::Alarm2Hours::set_a2m3(void)
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ |= (1<<Register::b_a2m3);
    Register::send_Byte(byte_);
}

void DS3231_RTC::Alarm2Hours::clear_a2m3(void)
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ &= ~(1<<Register::b_a2m3);
    Register::send_Byte(byte_);
}