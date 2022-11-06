#include "Tasks.hpp"
#include "functions.hpp"

void Tasks::System::periph_power_on(void)
{
    Serial.println(F("Wake up Neo..."));
    digitalWrite(PWR_CTRL_PIN, HIGH);
    
    OS.SetTask_(Display::print_Time, 100);
}

void Tasks::System::periph_power_off(void)
{
    Serial.println(F("Sleeping..."));
    digitalWrite(PWR_CTRL_PIN, LOW);

    OS.SetTask_(sleep, do_now);
}

void Tasks::System::sleep(void)
{
    DS3231_RTC::Control::enable_A1_INT();

    MCU::Core::powerDown_All_Peripherials();
    MCU::Core::BrownOut_Disable();

    MCU::Watchdog::Interrupt_Disable();
    MCU::Watchdog::Mode::stop();

    MCU::EXINT_::INT0_Enable();
    MCU::Sleep_::Enable();
    MCU::Sleep_::Go();
}

void Tasks::System::wakeUp_Prepare(void)
{
    MCU::Sleep_::Disable();
    MCU::EXINT_::INT0_Disable();
    MCU::Watchdog::Mode::interrupt();
    MCU::Watchdog::Interrupt_Enable();
    Setup_Power();
    DS3231_RTC::Control_Status::clear_Alarm_Events();

    OS.SetTask_(Tasks::System::periph_power_on, 10);
}