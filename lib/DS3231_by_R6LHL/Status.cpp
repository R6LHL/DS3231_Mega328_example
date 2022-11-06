#include "DS3231_RTC.hpp"

void DS3231_RTC::Control_Status::enable_32kHz()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_EN32kHZ);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control_Status::disable_32kHz()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_EN32kHZ);
    Register::send_Byte(raw_byte);
}

bool DS3231_RTC::Control_Status::is_BUSY(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::BSY_mask;
    return raw_byte;
}
        
bool DS3231_RTC::Control_Status::is_Alarm1_Event(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::A1F_mask;
    return raw_byte; 
}

bool DS3231_RTC::Control_Status::is_Alarm2_Event(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= Register::A2F_mask;
    return raw_byte;
}

void DS3231_RTC::Control_Status::clear_Alarm1_Event(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_A1F);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control_Status::clear_Alarm2_Event(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_A2F);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control_Status::clear_Alarm_Events(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_A2F)|(1<<Register::b_A1F);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control_Status::set_config(uint8_t conf)
{
    Register::send_Byte(conf);
}

uint8_t DS3231_RTC::Control_Status::get_config(void)
{
    return (uint8_t)Register::get_RAW_Byte();
}