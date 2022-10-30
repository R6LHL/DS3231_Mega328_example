#include "Tasks.hpp"

void led_on(void)
{
    MCU::IO_::PORTB_::PORT_::SetBit(5);
    OS.SetTask_(led_off, led_off_period_ts);
    //Serial.println(F("Led on"));
}

void led_off(void)
{
    MCU::IO_::PORTB_::PORT_::ClearBit(5);
    OS.SetTask_(led_on, led_off_period_ts);
    //Serial.println(F("Led off"));
}

void print_Time(void)
{
    Serial.print(DS3231_RTC::Minutes::get_Value());
    Serial.print(F(":"));
    Serial.println(DS3231_RTC::Seconds::get_Value());

    OS.SetTask_(print_Time, time_print_period_ts);
}