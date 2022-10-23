#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_

#include <avr/io.h>
#include <Arduino.h>

#include <TaskManager.hpp>

#include "config.hpp"

extern uint8_t some_var;
typedef TaskManager<task_queue_size> TaskManager5;
extern TaskManager5 OS;

uint8_t day;
uint8_t month;
uint16_t year;

uint8_t hour;
uint8_t minute;

#endif //VARIABLES_HPP_