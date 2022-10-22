#include "variables.hpp"
#include "Tasks.hpp"

TaskManager5 OS;

#ifdef TASKMANAGER_HPP
ISR(WDT_vect)
{
  //Serial.println("Interrupt is working");
  OS.TimerTaskService_();
}
#endif //TASKMANAGER_HPP

void setup() {

  #ifdef MCU_Mega328_HPP
  MCU::IO_::PORTB_::pullupAll();
  MCU::IO_::PORTC_::pullupAll();
  MCU::IO_::PORTD_::pullupAll();

  MCU::SPI_::powerDown();
  MCU::USART_::USART0_powerDown();
  MCU::ADC_::ADC_powerDown();
  MCU::TC0_::powerDown();
  MCU::TC1_::powerDown();
  MCU::TC2_::powerDown();

  //MCU::TWI_::powerUp();

  MCU::Watchdog::System_reset_disable();
  MCU::Watchdog::Prescaler::set_2048();
  MCU::Watchdog::Mode::interrupt();
  MCU::Watchdog::Interrupt_Enable();

  #endif //MCU_Mega328_HPP

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