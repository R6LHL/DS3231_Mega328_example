#ifndef TASKS_HPP
#define TASKS_HPP

#include <MCU_Mega_328.hpp>
#include <DS3231_RTC.hpp>

#include "variables.hpp"

void led_on (void);
void led_off(void);

void print_Time(void);

#endif //TASKS_HPP