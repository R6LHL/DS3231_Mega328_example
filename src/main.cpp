
#include "variables.hpp"
#include "functions.hpp"
#include "Tasks.hpp"

TaskManager5 OS;

ISR(INT0_vect){Tasks::System::wakeUp_Prepare();}

#ifdef TASKMANAGER_HPP
  ISR(WDT_vect){OS.TimerTaskService_();}
#endif //TASKMANAGER_HPP

void setup() {

  #ifdef MCU_Mega328_HPP
     
    #ifdef DEBUG_ON
      Protective_startup_delay();
    #endif //DEBUG_ON

    Setup_TWI();
    //MCU::Core::powerDown_All_Peripherials();
    //Setup_Power();

    #ifdef DS3231_RTC_HPP //RTC Setup
      Setup_DS3231();
    #endif //DS3231_RTC_HPP

    Setup_Watchdog();
    MCU::EXINT_::INT0_Mode::low_level();
    
  #endif //MCU_Mega328_HPP

  #ifdef TASKMANAGER_HPP
    OS.SetTask_(Tasks::System::periph_power_on, do_now);
  #endif // TASKMANAGER_HPP
}

void loop() {
  #ifdef TASKMANAGER_HPP
    OS.ProcessTaskQueue_();
  #endif //TASKMANAGER_HPP
}