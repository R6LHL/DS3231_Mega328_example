#ifndef VARIABLES_HPP_
#define VARIABLES_HPP_

#include <avr/io.h>
#include <Arduino.h>

#include <TaskManager.hpp>

#include "config.hpp"

extern uint8_t some_var;
typedef TaskManager<task_queue_size> TaskManager5;
extern TaskManager5 OS;

#endif //VARIABLES_HPP_