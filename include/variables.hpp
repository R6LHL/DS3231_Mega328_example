#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_

#include <avr/io.h>
#include <Arduino.h>

#include <TaskManager.hpp>
#include <Buffer.hpp>

#include "config.hpp"

typedef TaskManager<task_queue_size> TaskManager5;
extern TaskManager5 OS;

typedef Buffer<twi_buffer_size> Buffer8;
extern Buffer8 twi_buffer;

extern uint8_t day;
extern uint8_t month;
extern uint16_t year;

extern uint8_t hour;
extern uint8_t minute;

#endif //VARIABLES_HPP_