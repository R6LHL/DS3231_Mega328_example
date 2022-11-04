#ifndef CONFIG_HPP
#define CONFIG_HPP

#define MEGA328
//#define MEGA168

//DEBUG MODE
#define DEBUG_ON

#ifdef DEBUG_ON
    #define DEBUG_TIME_SET
    //#define SLEEP_ENABLED
#endif //DEBUG_ON

#include <avr/io.h>

#ifdef MEGA328
#include <MCU_Mega_328.hpp>
#endif //MEGA328

#ifdef DEBUG_TIME_SET
#include <build_time.h>
#endif //DEBUG_TIME_SET

//Task Manager config
const uint8_t task_queue_size = 5;
//const uint8_t os_min_timeslot_ms = 16;

//Pin layout
const uint8_t built_in_led_bit = 5;

// Tasks periods
// timeslot = period_you_need / os_min_timeslot_ms
//const uint8_t do_now = 0;
//const uint8_t lcd_renew_period_ts = (uint8_t)(80 / os_min_timeslot_ms);
//const uint8_t encoder_check_period_ts = 1;
//const uint8_t button_check_period_ts = (uint8_t)(48 / os_min_timeslot_ms);

//Встроенный светодиод
const uint8_t led_on_period_ts = 20;
const uint8_t led_off_period_ts = 20;
const uint8_t time_print_period_ts = 62;

//Настройки буферов
//const uint8_t twi_buffer_size = 8;

#endif //CONFIG_HPP