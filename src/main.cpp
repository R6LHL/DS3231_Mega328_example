#include "variables.hpp"
#include "Tasks.hpp"

TaskManager5 OS;

#ifdef TASKMANAGER_HPP
  ISR(WDT_vect){OS.TimerTaskService_();}
#endif //TASKMANAGER_HPP

void setup() {

  #ifdef DEBUG_ON
    Serial.begin(9600);
  #endif //DEBUG_ON

  #ifdef MCU_Mega328_HPP
    //IO pins setup
    MCU::IO_::PORTB_::pullupAll();
    MCU::IO_::PORTC_::pullupAll();
    MCU::IO_::PORTD_::pullupAll();

    MCU::IO_::PORTB_::DDR_::SetBit(5);

    MCU::TWI_::TWBR_::Set(72);
    MCU::TWI_::Prescaler::Set_1(); // scl 100 kHz

    //Watchdog setup for TaskManager
    MCU::Watchdog::System_reset_disable();
    MCU::Watchdog::Prescaler::set_2048();
    MCU::Watchdog::Mode::interrupt();
    MCU::Watchdog::Interrupt_Enable();

    //Sleep mode setup
    #ifdef SLEEP_ENABLED
      MCU::Sleep_::Mode::PowerDown();
    #endif //SLEEP_ENABLED

    #ifdef DS3231_RTC_HPP //RTC Setup
      DS3231_RTC::Control::disable_BBSQW();
      DS3231_RTC::Control::disable_EOSC();
      DS3231_RTC::Control::enable_INT();
      DS3231_RTC::Control_Status::disable_32kHz();
    
      #ifdef DEBUG_TIME_SET
      DS3231_RTC::Year::set_Value(22);
      DS3231_RTC::Century_Month::set_Value(0, BUILD_MONTH);
      DS3231_RTC::Date::set_Value(BUILD_DAY);

      DS3231_RTC::Hours::set_24_mode();
      DS3231_RTC::Hours::set_Value(BUILD_HOUR);

      DS3231_RTC::Minutes::set_Value(BUILD_MIN);
      DS3231_RTC::Seconds::set_Value(BUILD_SEC);
      #endif //DEBUG_TIME_SET
    #endif //DS3231_RTC_HPP

  #endif //MCU_Mega328_HPP

  #ifdef TASKMANAGER_HPP
    OS.SetTask_(led_on, led_on_period_ts);
    #ifdef DEBUG_TIME_SET
      OS.SetTask_(print_Time, time_print_period_ts);
    #endif //DEBUG_TIME_SET
  #endif // TASKMANAGER_HPP
}

void loop() {
  #ifdef TASKMANAGER_HPP
    OS.ProcessTaskQueue_();
  #endif //TASKMANAGER_HPP
}