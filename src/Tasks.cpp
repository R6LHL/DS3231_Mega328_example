#include "Tasks.hpp"

#include <MCU_Mega_328.hpp>
#include "variables.hpp"

void led_on(void)
{
    MCU::IO_::PORTB_::PORT_::SetBit(5);
    OS.SetTask_(led_off, led_off_period_ts);
}

void led_off(void)
{
    MCU::IO_::PORTB_::PORT_::ClearBit(5);
    OS.SetTask_(led_on, led_off_period_ts);
}
