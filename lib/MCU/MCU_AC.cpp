#include "MCU_Mega_328.hpp"

void MCU::AC_::digital_Input_Enable(uint8_t ac_pin_number)
{
    if ((ac_pin_number == 0) || (ac_pin_number == 1))
	{
		DIDR1_::ClearBit(ac_pin_number);
	}
		else return;
	}
		
void MCU::AC_::digital_Input_Disable(uint8_t ac_pin_number)
{
	if ((ac_pin_number == 0) || (ac_pin_number == 1))
	{
		DIDR1_::SetBit(ac_pin_number);
	}
    	else return;
}

void MCU::AC_::powerDown(void)
{
	ACSR_::SetBit(ACSR_::ACD_);
}

void MCU::AC_::powerUp(void)
{
	ACSR_::ClearBit(ACSR_::ACD_);
}