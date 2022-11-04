#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Alarm1Seconds::get_Value()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    uint8_t sec_10;
    uint8_t sec;

    sec_10 = raw_byte & Register::sec_10_mask;
    sec_10 >>= Register::sec_10_shift;
    sec_10 = sec_10 * 10;

    Register::is_a1m1_set = raw_byte & Register::a1m1_mask;

    sec = raw_byte & Register::sec_mask;
    return sec_10 + sec;
}

void DS3231_RTC::Alarm1Seconds::set_Value(uint8_t s)
{
    if (s > Register::seconds_max) s = Register::seconds_max;
    else if (s < Register::seconds_min) s = Register::seconds_min;
    
    uint8_t msb = s / 10;
    uint8_t lsb = s % 10;

    msb <<= Register::sec_10_shift;
    msb &= Register::sec_10_mask;

    lsb &= Register::sec_mask;
    Register::send_Byte(msb+lsb);
}

void DS3231_RTC::Alarm1Seconds::set_a1m1(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1 << Register::b_a1m1);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Alarm1Seconds::clear_a1m1(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1 << Register::b_a1m1);
    Register::send_Byte(raw_byte);
}

