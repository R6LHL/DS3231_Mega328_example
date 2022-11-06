#include "DS3231_RTC.hpp"

void DS3231_RTC::Control::enable_EOSC(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_EOSC);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::disable_EOSC(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_EOSC);
    Register::send_Byte(raw_byte);
}
        
void DS3231_RTC::Control::enable_BBSQW(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_BBSQW);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::disable_BBSQW(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_BBSQW);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::start_temp_CONV(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_CONV);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::set_SQW_Rate_1Hz(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~((1<<Register::b_RS2)|(1<<Register::b_RS1));
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::set_SQW_Rate_1024Hz(void)
{
   uint8_t raw_byte = Register::get_RAW_Byte();
   raw_byte &= ~(1<<Register::b_RS1);
   raw_byte |=(1<<Register::b_RS2);
   Register::send_Byte(raw_byte); 
}

void DS3231_RTC::Control::set_SQW_Rate_4096Hz(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_RS2);
    raw_byte |=(1<<Register::b_RS1);
    Register::send_Byte(raw_byte); 
}

void DS3231_RTC::Control::set_SQW_Rate_8132Hz(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |=((1<<Register::b_RS2)|(1<<Register::b_RS1));
    Register::send_Byte(raw_byte); 
}

void DS3231_RTC::Control::enable_INT(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |=(1<<Register::b_INTCN);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::enable_SQW(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_INTCN);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::enable_A1_INT(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_A1IE)|(1<<Register::b_INTCN);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::enable_A2_INT(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::b_A2IE)|(1<<Register::b_INTCN);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Control::disable_A1_INT(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_A1IE)|(1<<Register::b_INTCN);
    Register::send_Byte(raw_byte);
    DS3231_RTC::Control_Status::clear_Alarm1_Event();
}

void DS3231_RTC::Control::disable_A2_INT(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::b_A2IE)|(1<<Register::b_INTCN);
    Register::send_Byte(raw_byte);
    DS3231_RTC::Control_Status::clear_Alarm2_Event();
}

void DS3231_RTC::Control::set_config(uint8_t conf)
{
    Register::send_Byte(conf);
}

uint8_t DS3231_RTC::Control::get_config(void)
{
    return (uint8_t)Register::get_RAW_Byte();
}