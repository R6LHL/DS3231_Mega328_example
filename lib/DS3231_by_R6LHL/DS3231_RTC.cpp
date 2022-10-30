#include "DS3231_RTC.hpp"

uint8_t DS3231_RTC::Seconds::get_Value(void)
{
    volatile uint8_t raw_byte = Register::get_RAW_Byte();
      
    uint8_t sec_10;
    uint8_t sec;

    sec_10 = raw_byte & Register::sec_10_mask;
    sec_10 >>= Register::sec_10_shift;
    sec_10 = sec_10 * 10;

    sec = raw_byte & Register::sec_mask;
    return sec_10 + sec;
    
    //return raw_byte;
}

void DS3231_RTC::Seconds::set_Value(uint8_t s)
{
    uint8_t msb = s / 10;
    uint8_t lsb = s % 10;

    msb <<= Register::sec_10_shift;
    msb &= Register::sec_10_mask;

    lsb &= Register::sec_mask;
    Register::send_Byte(msb+lsb);
}

uint8_t DS3231_RTC::Minutes::get_Value(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    
    uint8_t mins_10;
    uint8_t mins;

    mins_10 = raw_byte & Register::mins_10_mask;
    mins_10 >>= Register::mins_10_shift;
    mins_10 = mins_10 * 10;

    mins = raw_byte & Register::mins_mask;
    return mins_10 + mins;
    
    //return raw_byte;
}

void DS3231_RTC::Minutes::set_Value(uint8_t m)
{
    uint8_t msb = m / 10;
    uint8_t lsb = m % 10;

    msb <<= Register::mins_10_shift;
    msb &= Register::mins_10_mask;

    lsb &= Register::mins_mask;
    Register::send_Byte(msb+lsb);
}

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

void DS3231_RTC::Hours::set_am_pm(bool b)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (b<<Register::am_pm_shift);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Hours::set_24_mode(void)
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte &= ~(1<<Register::c12_24_shift);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Hours::set_12_mode()
{
    uint8_t raw_byte = Register::get_RAW_Byte();
    raw_byte |= (1<<Register::c12_24_shift);
    Register::send_Byte(raw_byte);
}

void DS3231_RTC::Hours::set_Value(uint8_t h)
{
    uint8_t msb = h / 10;
    uint8_t lsb = h % 10;
    
    /*
    bool c12_14 = get_c12_24();
    if(c12_14 == 0)
    {
        msb <<= Register::hours_12_shift;
        msb &= Register::hours_12_mask;
        
        if (h > 12)
        {
            set_am_pm(true);
        }
        else set_am_pm(false);
    }
    else
    {
        msb <<= Register::hours_24_shift;
        msb &= Register::hours_24_mask;
    }
    */
    msb <<= 4;
    //msb &= 0b00110000;;

    lsb &= Register::hours_mask;

    Register::send_Byte(msb+lsb);
}

uint8_t DS3231_RTC::Day::get_Value(void) 
{
    return get_RAW_Byte();
}

uint8_t DS3231_RTC::Date::get_Value(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    uint8_t date_10 = raw_byte & date_10_mask;
    date_10 >>= date_10_shift;
    date_10 = date_10 * 10;

    uint8_t date = raw_byte & date_mask;
    return date_10 + date;
}

uint8_t DS3231_RTC::Century_Month::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();
    uint8_t month_10 = raw_byte & month_10_mask;
    month_10 >>= month_10_shift;
    month_10 = month_10 * 10;

    is_century22 = raw_byte & century_mask;

    uint8_t month = raw_byte & month_mask;
    return month_10 + month;
}

uint8_t DS3231_RTC::Year::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();
    uint8_t year_10 = raw_byte & year_10_mask;
    year_10 >>=  year_10_shift;
    year_10 = year_10 * 10;

    uint8_t year = raw_byte & year_mask;
    return year_10 + year;
}

uint8_t DS3231_RTC::Alarm1Seconds::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();
    uint8_t sec_10;
    uint8_t sec;

    sec_10 = raw_byte & sec_10_mask;
    sec_10 >>= sec_10_shift;
    sec_10 = sec_10 * 10;

    is_a1m1_set = raw_byte & a1m1_mask;

    sec = raw_byte & sec_mask;
    return sec_10 + sec;
}

void DS3231_RTC::Alarm1Seconds::set_a1m1(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |= (1 << b_a1m1);
    send_Byte(raw_byte);
}

void DS3231_RTC::Alarm1Seconds::clear_a1m1(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1 << b_a1m1);
    send_Byte(raw_byte);
}

uint8_t DS3231_RTC::Alarm1Minutes::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();
    uint8_t mins_10;
    uint8_t mins;

    mins_10 = raw_byte & mins_10_mask;
    mins_10 >>= mins_10_shift;
    mins_10 = mins_10 * 10;

    is_a1m2_set = raw_byte & a1m2_mask;

    mins = raw_byte & mins_mask;
    return mins_10 + mins;
}

uint8_t DS3231_RTC::Alarm1Hours::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();
    bool c24;
    uint8_t hours10;
    uint8_t hours;

    c24 = raw_byte & c12_24_mask;
    is_pm = raw_byte & am_pm_mask;

    is_a1m3_set = raw_byte & a1m3_mask;

    if (c24 == true)
    {
        hours10 = raw_byte & hours_24_mask;
        hours10 >>= hours_24_shift;
    }
    else
    {
        hours10 = raw_byte & hours_12_mask;
        hours10 >>= hours_12_shift;
    }

    hours10 = hours10 * 10;
    hours = raw_byte & hours_mask;

    return hours10 + hours;
}

uint8_t DS3231_RTC::Alarm1Day_Date::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();

    is_a1m4_set = raw_byte & a1m4_mask;
    is_date = raw_byte & day_date_mask;

    uint8_t day_or_date;

    if (is_date == true) return (day_or_date & date_mask);
    else return  day_or_date & day_mask;
}

uint8_t DS3231_RTC::Alarm2Minutes::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();
    uint8_t mins_10;
    uint8_t mins;

    mins_10 = raw_byte & mins_10_mask;
    mins_10 >>= mins_10_shift;
    mins_10 = mins_10 * 10;

    is_a2m2_set = raw_byte & a2m2_mask;

    mins = raw_byte & mins_mask;
    return mins_10 + mins;
}

uint8_t DS3231_RTC::Alarm2Hours::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();
    bool c24;
    uint8_t hours10;
    uint8_t hours;

    c24 = raw_byte & c12_24_mask;
    is_pm = raw_byte & am_pm_mask;

    is_a2m3_set = raw_byte & a2m3_mask;

    if (c24 == true)
    {
        hours10 = raw_byte & hours_24_mask;
        hours10 >>= hours_24_shift;
    }
    else
    {
        hours10 = raw_byte & hours_12_mask;
        hours10 >>= hours_12_shift;
    }

    hours10 = hours10 * 10;
    hours = raw_byte & hours_mask;

    return hours10 + hours;
}

uint8_t DS3231_RTC::Alarm2Day_Date::get_Value()
{
    uint8_t raw_byte = get_RAW_Byte();

    is_a2m4_set = raw_byte & a2m4_mask;
    is_date = raw_byte & day_date_mask;

    uint8_t day_or_date;

    if (is_date == true) return (day_or_date & date_mask);
    else return  day_or_date & day_mask;
}

void DS3231_RTC::Control::enable_EOSC(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |= (1<<b_EOSC);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::disable_EOSC(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_EOSC);
    send_Byte(raw_byte);
}
        
void DS3231_RTC::Control::enable_BBSQW(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |= (1<<b_BBSQW);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::disable_BBSQW(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_BBSQW);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::start_temp_CONV(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |= (1<<b_CONV);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::set_SQW_Rate_1Hz(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~((1<<b_RS2)|(1<<b_RS1));
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::set_SQW_Rate_1024Hz(void)
{
   uint8_t raw_byte = get_RAW_Byte();
   raw_byte &= ~(1<<b_RS1);
   raw_byte |=(1<<b_RS2);
   send_Byte(raw_byte); 
}

void DS3231_RTC::Control::set_SQW_Rate_4096Hz(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_RS2);
    raw_byte |=(1<<b_RS1);
    send_Byte(raw_byte); 
}

void DS3231_RTC::Control::set_SQW_Rate_8132Hz(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |=((1<<b_RS2)|(1<<b_RS1));
    send_Byte(raw_byte); 
}

void DS3231_RTC::Control::enable_INT(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |=(1<<b_INTCN);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::enable_SQW(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_INTCN);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::enable_A1_INT(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |= (1<<b_A1IE);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::enable_A2_INT(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |= (1<<b_A2IE);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::disable_A1_INT(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_A1IE);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::disable_A2_INT(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_A2IE);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control::set_config(uint8_t conf)
{
    send_Byte(conf);
}

uint8_t DS3231_RTC::Control::get_config(void)
{
    return (uint8_t)get_RAW_Byte();
}

void DS3231_RTC::Control_Status::enable_32kHz()
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte |= (1<<b_EN32kHZ);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control_Status::disable_32kHz()
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_EN32kHZ);
    send_Byte(raw_byte);
}

bool DS3231_RTC::Control_Status::is_BUSY(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= BSY_mask;
    return raw_byte;
}
        
bool DS3231_RTC::Control_Status::is_Alarm1_Event(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= A1F_mask;
    return raw_byte; 
}

bool DS3231_RTC::Control_Status::is_Alarm2_Event(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= A2F_mask;
    return raw_byte;
}

void DS3231_RTC::Control_Status::clear_Alarm1_Event(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_A1F);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control_Status::clear_Alarm2_Event(void)
{
    uint8_t raw_byte = get_RAW_Byte();
    raw_byte &= ~(1<<b_A2F);
    send_Byte(raw_byte);
}

void DS3231_RTC::Control_Status::set_config(uint8_t conf)
{
     send_Byte(conf);
}

uint8_t DS3231_RTC::Control_Status::get_config(void)
{
    return (uint8_t)get_RAW_Byte();
}

int8_t DS3231_RTC::Aging_offset::get_Value()
{
    return (int8_t)get_RAW_Byte();
}

int8_t DS3231_RTC::MSB_of_temp::get_Value()
{
    return (int8_t)get_RAW_Byte();
}

uint8_t DS3231_RTC::LSB_of_temp::get_Value()
{
    return (uint8_t)get_RAW_Byte();
}