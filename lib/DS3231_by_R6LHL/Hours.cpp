#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Hours::get_Value(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();

    bool c24;
    uint8_t hours10;
    uint8_t hours;

    c24 = (bool)(raw_byte & Register::c12_24_mask);
    //DS3231_RTC::Hours::is_pm = (bool)(raw_byte & Register::am_pm_mask);

    if (c24 == 0)
    {
        hours10 = raw_byte & Register::hours_24_mask;
        hours10 >>= 4;
    }
    else
    {
        hours10 = raw_byte & Register::hours_12_mask;
        hours10 >>= 4;
    }

    hours10 = hours10 * 10;
    hours = raw_byte & Register::hours_mask;

    return hours10 + hours;
    
   //return raw_byte;
}

bool DS3231_RTC::Hours::get_c12_24(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::c12_24_mask;
    return (bool)raw_byte;
}

bool DS3231_RTC::Hours::get_am_pm(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::am_pm_mask;
    return (bool)raw_byte;
}

void DS3231_RTC::Hours::set_am(void)
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ &= ~(1<<Register::b_am_pm);
    Register::send_Byte(byte_);
}

void DS3231_RTC::Hours::set_pm(void)
{
    uint8_t byte_ = Register::get_RAW_Byte();
    byte_ |= (1<<Register::b_am_pm);
    Register::send_Byte(byte_);
}

void DS3231_RTC::Hours::set_24_mode(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::c12_24_shift);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Hours::set_12_mode(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::c12_24_shift);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Hours::set_Value(uint8_t h)
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