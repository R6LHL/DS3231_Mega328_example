#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Century_Month::get_Value()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    uint8_t month_10 = raw_byte & Register::month_10_mask;
    month_10 >>= Register::month_10_shift;
    month_10 = month_10 * 10;

    uint8_t month = raw_byte & Register::month_mask;
    return month_10 + month;
}

void DS3231_RTC::Century_Month::set_Value(bool c, uint8_t m)
{
    if (m > Register::month_max) m = Register::month_max;
    else if (m < Register::month_min) m = Register::month_min;
    
    uint8_t msb = m / 10;
    uint8_t lsb = m % 10;

    msb <<= 4;
    if (c == false) {(msb &= ~(1<<7));}
    else {msb |= (1<<7);}
    Register::send_Byte(msb+lsb);
}

bool DS3231_RTC::Century_Month::is_century22(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::century_mask;
    return (bool)raw_byte;
}