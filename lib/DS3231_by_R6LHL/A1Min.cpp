#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Alarm1Minutes::get_Value()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    uint8_t mins_10;
    uint8_t mins;

    mins_10 = raw_byte & Register::mins_10_mask;
    mins_10 >>= Register::mins_10_shift;
    mins_10 = mins_10 * 10;

    Register::is_a1m2_set = raw_byte & Register::a1m2_mask;

    mins = raw_byte & Register::mins_mask;
    return mins_10 + mins;
}

void DS3231_RTC::Alarm1Minutes::set_Value(uint8_t m)
{
    if (m > Register::minutes_max) m = Register::minutes_max;
    else if (m < Register::minutes_max) m = Register::minutes_max;
    
    uint8_t msb = m / 10;
    uint8_t lsb = m % 10;

    msb <<= Register::mins_10_shift;
    msb &= Register::mins_10_mask;

    lsb &= Register::mins_mask;
    Register::send_Byte(msb+lsb); 
}

void DS3231_RTC::Alarm1Minutes::set_a1m2(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1 << Register::b_a1m2);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Alarm1Minutes::clear_a1m2(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1 << Register::b_a1m2);
    Register::send_Byte(raw_byte);
}