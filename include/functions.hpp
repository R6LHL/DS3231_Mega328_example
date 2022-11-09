#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "variables.hpp"

void Setup_DS3231(void);
void Protective_startup_delay(void);
void Setup_IO_Pins(void);
void Setup_TWI(void);
void Setup_Power(void);
void Setup_Sleep(void);
void Setup_Watchdog(void);
void Setup_USART(void);

#endif //FUNCTIONS_HPP