#include "functions.hpp"

void Setup_DS3231(void)

{
    DS3231_RTC::Control::disable_A1_INT();
    DS3231_RTC::Control::disable_A2_INT();
    DS3231_RTC::Control::disable_BBSQW();
    DS3231_RTC::Control::disable_EOSC();
    DS3231_RTC::Control_Status::disable_32kHz();
    
    #ifdef DEBUG_TIME_SET
    DS3231_RTC::Year::set_Value(22);
    DS3231_RTC::Century_Month::set_Value(0, BUILD_MONTH);
    DS3231_RTC::Date::set_Value(BUILD_DAY);

    DS3231_RTC::Hours::set_24_mode();
    DS3231_RTC::Hours::set_Value(14);

    DS3231_RTC::Minutes::set_Value(0);
    DS3231_RTC::Seconds::set_Value(0);
    #endif //DEBUG_TIME_SET

    DS3231_RTC::Alarm1Day_Date::set_a1m4();
    DS3231_RTC::Alarm1Hours::set_a1m3();
    DS3231_RTC::Alarm1Minutes::set_a1m2();
    DS3231_RTC::Alarm1Seconds::set_Value(30);
    //DS3231_RTC::Alarm1Seconds::set_a1m1();
    DS3231_RTC::Alarm1Seconds::clear_a1m1();

    DS3231_RTC::Alarm2Day_Date::clear_a2m4();
    DS3231_RTC::Alarm2Hours::clear_a2m3();
    DS3231_RTC::Alarm2Minutes::clear_a2m2();
    
}

void Protective_startup_delay(void)
{
    MCU::Core::powerUp_All_Peripherials();
    delay(1000);
    Serial.begin(9600);
    Serial.println();
    Serial.println(F("You can reprogramm it now..."));
    delay(2000);
    Serial.println(F("Ok, let's work..."));
}

void Setup_IO_Pins(void)
{
    pinMode(PWR_CTRL_PIN, OUTPUT);
    pinMode(RTC_INT_PIN, INPUT_PULLUP);
}

void Setup_TWI(void){
    MCU::TWI_::TWBR_::Set(72);
    MCU::TWI_::Prescaler::Set_1(); // scl 100 kHz
}

void Setup_Power(void)
{
    MCU::TWI_::powerUp();
    MCU::USART_::powerUp();
    MCU::TC0_::powerUp();
}

void Setup_Sleep(void)
{
    MCU::Core::BrownOut_Disable();
    MCU::Sleep_::Mode::PowerDown();
}

void Setup_Watchdog(void)
{
    MCU::Watchdog::System_reset_disable();
    MCU::Watchdog::Prescaler::set_2048();
    MCU::Watchdog::Mode::interrupt();
    MCU::Watchdog::Interrupt_Enable();
}

void Setup_USART(void)
{
    MCU::USART_::Set::BaudRate(16000000, 9600);
}