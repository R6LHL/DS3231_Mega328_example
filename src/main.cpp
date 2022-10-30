#include "variables.hpp"
#include "Tasks.hpp"

TaskManager5 OS;
//DS3231 RTC;
//bool century = false;
//bool h12Flag = false;
//bool pmFlag = false;

#ifdef TASKMANAGER_HPP
ISR(WDT_vect)
{
  //Serial.println("Interrupt is working");
  OS.TimerTaskService_();
}
#endif //TASKMANAGER_HPP

void setup() {

  Serial.begin(9600);
  //Wire.begin();

  #ifdef MCU_Mega328_HPP
  //IO pins setup
  MCU::IO_::PORTB_::pullupAll();
  MCU::IO_::PORTC_::pullupAll();
  MCU::IO_::PORTD_::pullupAll();

  MCU::IO_::PORTB_::DDR_::SetBit(5);

  MCU::TWI_::TWBR_::Set(72);
  MCU::TWI_::Prescaler::Set_1(); // scl 100 kHz
  //MCU::TWI_::TWCR_::SetBit(MCU::TWI_::TWCR_::b_TWEA);

  Serial.println("Serial is working");
  //Watchdog setup for TaskManager
  MCU::Watchdog::System_reset_disable();
  MCU::Watchdog::Prescaler::set_2048();
  MCU::Watchdog::Mode::interrupt();
  MCU::Watchdog::Interrupt_Enable();
  Serial.println("Watchdog is working");

  //Sleep mode setup
  //MCU::Sleep_::Mode::PowerDown();

    #ifdef DS3231_RTC_HPP //RTC Setup
    
    DS3231_RTC::Control::disable_BBSQW();
    DS3231_RTC::Control::disable_EOSC();
    DS3231_RTC::Control::enable_INT();
    DS3231_RTC::Control_Status::disable_32kHz();

    #endif //DS3231_RTC_HPP

  #endif //MCU_Mega328_HPP

  #ifdef TASKMANAGER_HPP
  OS.SetTask_(led_on, led_on_period_ts);
  OS.SetTask_(print_Time, time_print_period_ts);
  #endif // TASKMANAGER_HPP
}

void loop() {
  //Serial.println("Loop is working");
  #ifdef TASKMANAGER_HPP
  OS.ProcessTaskQueue_();
  //Serial.println("Main loop is working");
  #endif //TASKMANAGER_HPP
}