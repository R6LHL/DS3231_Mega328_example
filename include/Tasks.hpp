#ifndef TASKS_HPP
#define TASKS_HPP

#include <MCU_Mega_328.hpp>
#include <DS3231_RTC.hpp>

#include "variables.hpp"

namespace Tasks
{
    namespace System
    {
        void periph_power_on (void);
        void periph_power_off(void);
        void sleep(void);
        void wakeUp_Prepare(void);
    }
    
    namespace Display
    {
        void print_Time(void);
        void print_Date(void);
    }
}

#endif //TASKS_HPP