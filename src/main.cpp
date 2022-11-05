
#include "variables.hpp"
#include "Tasks.hpp"

TaskManager5 OS;

ISR(INT0_vect)
{
  Serial.println(F("Wake up Neo..."));
  OS.SetTask_(periph_power_on, 10);
}

#ifdef TASKMANAGER_HPP
  ISR(WDT_vect){OS.TimerTaskService_();}
#endif //TASKMANAGER_HPP

void setup() {

  #ifdef MCU_Mega328_HPP
    
    //emergency power up MCU peripherials
    MCU::Core::powerUp_All_Peripherials();
    
    //protective delay for emergency reprogramming
    //#define F_CPU 16000000
    #ifdef DEBUG_ON
      Serial.begin(9600);
      Serial.println(F("You can reprogramm it now..."));
      delay(3000);
      Serial.println(F("Ok, let's work..."));
    #endif //DEBUG_ON

    //IO pins setup
    pinMode(PWR_CTRL_PIN, OUTPUT);
    pinMode(RTC_INT_PIN, INPUT_PULLUP);

    MCU::TWI_::TWBR_::Set(72);
    MCU::TWI_::Prescaler::Set_1(); // scl 100 kHz

    /*
    //Power mangement
    MCU::Core::powerDown_All_Peripherials();
    MCU::TWI_::powerUp();
    MCU::USART_::powerUp();
    MCU::TC0_::powerUp();
    */

    //Sleep mode setup
    #ifdef SLEEP_ENABLED
      MCU::Sleep_::Mode::PowerDown();
    #endif //SLEEP_ENABLED

    #ifdef DS3231_RTC_HPP //RTC Setup
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

      DS3231_RTC::Alarm1Day_Date::set_a1m4();
      DS3231_RTC::Alarm1Hours::set_a1m3();
      DS3231_RTC::Alarm1Minutes::set_a1m2();
      DS3231_RTC::Control::disable_A1_INT();
      //DS3231_RTC::Alarm1Seconds::set_Value(30);
      //DS3231_RTC::Alarm1Seconds::set_a1m1();

      #endif //DEBUG_TIME_SET
    #endif //DS3231_RTC_HPP

    //Watchdog setup for TaskManager
    MCU::Watchdog::System_reset_disable();
    MCU::Watchdog::Prescaler::set_2048();
    MCU::Watchdog::Mode::interrupt();
    MCU::Watchdog::Interrupt_Enable();

    MCU::EXINT_::INT0_Mode::low_level();
    MCU::EXINT_::INT0_Enable();
    DS3231_RTC::Control::enable_A1_INT();

  #endif //MCU_Mega328_HPP

  #ifdef TASKMANAGER_HPP
    OS.SetTask_(periph_power_on, do_now);
  #endif // TASKMANAGER_HPP
}

void loop() {
  #ifdef TASKMANAGER_HPP
    OS.ProcessTaskQueue_();
  #endif //TASKMANAGER_HPP
}