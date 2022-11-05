#include "Tasks.hpp"

void periph_power_on(void)
{
    digitalWrite(PWR_CTRL_PIN, HIGH);
    OS.SetTask_(print_Time, do_now);
}
void periph_power_off(void)
{
    digitalWrite(PWR_CTRL_PIN, LOW);
    OS.SetTask_(system_sleep, do_now);
}

#ifdef DEBUG_TIME_SET
void print_Time(void)
{
    uint8_t hours = DS3231_RTC::Hours::get_Value();
    uint8_t minutes = DS3231_RTC::Minutes::get_Value();
    uint8_t seconds = DS3231_RTC::Seconds::get_Value();

    if (hours < 10)
    {
        Serial.print(F("0"));
    }
    Serial.print(hours);
    Serial.print(F(":"));

    if (minutes < 10)
    {
        Serial.print(F("0"));
    }
    
    Serial.print(minutes);
    Serial.print(F(":"));

    if (seconds < 10)
    {
        Serial.print(F("0"));
    }
    Serial.println(DS3231_RTC::Seconds::get_Value());

    OS.SetTask_(print_Date, time_print_period_ts);
}

void print_Date(void)
{
    uint8_t day = DS3231_RTC::Date::get_Value();
    uint8_t month = DS3231_RTC::Century_Month::get_Value();
    uint8_t year = DS3231_RTC::Year::get_Value();

    if (day < 10)
    {
        Serial.print(F("0"));
    }

    Serial.print(day);
    Serial.print(F("-"));

    if (month < 10)
    {
        Serial.print(F("0"));
    }

    Serial.print(month);
    Serial.print(F("-"));

    Serial.print(F("20"));
    Serial.println(year);

    OS.SetTask_(periph_power_off, time_print_period_ts);
}
#endif //DEBUG_TIME_SET

void system_sleep(void)
{
    asm("sleep");
}