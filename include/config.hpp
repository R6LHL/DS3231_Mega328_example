#ifndef CONFIG_HPP
#define CONFIG_HPP

#define MEGA328
//#define MEGA168

//DEBUG MODE
#define DEBUG_ON

#ifdef DEBUG_ON
    //#define DEBUG_TIME_SET
#endif //DEBUG_ON

#define SLEEP_ENABLED

#include <avr/io.h>

#ifdef MEGA328
#include <MCU_Mega_328.hpp>
#endif //MEGA328

const uint32_t FOSC = 16000000;

//Task Manager config
const uint8_t task_queue_size = 5;
//const uint8_t os_min_timeslot_ms = 16;

//Pin layout
typedef const uint8_t pin_number;
pin_number PWR_CTRL_PIN = 13;    // PORT_B.5
pin_number RTC_INT_PIN = 2;     // PORT_D.2
// Tasks periods
// timeslot = period_you_need / os_min_timeslot_ms
typedef const uint8_t task_delay;
task_delay do_now = 0;
//const uint8_t lcd_renew_period_ts = (uint8_t)(80 / os_min_timeslot_ms);
//const uint8_t encoder_check_period_ts = 1;
//const uint8_t button_check_period_ts = (uint8_t)(48 / os_min_timeslot_ms);

//Встроенный светодиод
const uint8_t led_on_period_ts = 20;
const uint8_t led_off_period_ts = 20;
const uint8_t time_print_period_ts = 62;

//UART Baudrate
const uint16_t UART_Baudrate = 9600;
constexpr uint8_t UBRR_value = FOSC/16/UART_Baudrate-1;

#endif //CONFIG_HPP