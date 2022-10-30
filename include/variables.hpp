#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_

#include <avr/io.h>
#include <Arduino.h>
#include <Wire.h>

#include <TaskManager.hpp>

#include <DS3231_RTC.hpp>

#include "config.hpp"

typedef TaskManager<task_queue_size> TaskManager5;
extern TaskManager5 OS;

//extern DS3231 RTC;

//extern bool century;
//extern bool h12Flag;
//extern bool pmFlag;

#endif //VARIABLES_HPP_