#include "Tasks.hpp"

void periph_power_on(void)
{
    //MCU::EXINT_::INT0_Disable();
    //DS3231_RTC::Control::disable_A2_INT();
    
    //MCU::Core::powerUp_All_Peripherials();
    Serial.println(F("Waking..."));
    digitalWrite(PWR_CTRL_PIN, HIGH);
    OS.SetTask_(print_Time, 100);
}

void periph_power_off(void)
{
    OS.SetTask_(system_sleep, do_now);
    Serial.println(F("Sleeping..."));

    //MCU::EXINT_::INT0_Enable();
    //MCU::EXINT_::EIFR_::ClearBit(MCU::EXINT_::EIFR_::b_INTF0);
    //DS3231_RTC::Control::enable_A2_INT();
    //MCU::EXINT_::EIFR_::ClearBit(MCU::EXINT_::EIFR_::b_INTF0);

    //MCU::Core::powerDown_All_Peripherials();
    digitalWrite(PWR_CTRL_PIN, LOW);
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

    OS.SetTask_(print_Date, do_now);
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

    OS.SetTask_(periph_power_off, do_now);
}
#endif //DEBUG_TIME_SET

void system_sleep(void){asm("sleep");}