#include "variables.hpp"
#include "Tasks.hpp"

TaskManager5 OS;
Buffer8 twi_buffer;

#ifdef TASKMANAGER_HPP
ISR(WDT_vect)
{
  //Serial.println("Interrupt is working");
  OS.TimerTaskService_();
}
#endif //TASKMANAGER_HPP

void setup() {

  #ifdef MCU_Mega328_HPP
  //IO pins setup
  MCU::IO_::PORTB_::pullupAll();
  MCU::IO_::PORTC_::pullupAll();
  MCU::IO_::PORTD_::pullupAll();

  //Power setup
  MCU::Core::powerDown_All_Peripherials();
  MCU::USART_::powerUp();
  MCU::TWI_::powerUp();

  //Watchdog setup for TaskManager
  MCU::Watchdog::System_reset_disable();
  MCU::Watchdog::Prescaler::set_2048();
  MCU::Watchdog::Mode::interrupt();
  MCU::Watchdog::Interrupt_Enable();

  //Sleep mode setup
  MCU::Sleep_::Mode::PowerDown();
  #endif //MCU_Mega328_HPP

  /*
  #ifdef BUFFER_HPP
  twi_buffer.flush();
  #endif // BUFFER_HPP
  */

  #ifdef TASKMANAGER_HPP
  OS.SetTask_(led_on, led_on_period_ts);
  #endif // TASKMANAGER_HPP
}

void loop() {
  //Serial.println("Loop is working");
  #ifdef TASKMANAGER_HPP
  OS.ProcessTaskQueue_();
  #endif //TASKMANAGER_HPP
}