#include "MCU_Mega_328.hpp"

void MCU::TC2_::powerUp(void){MCU::Core::PRR_::ClearBit(MCU::Core::PRR_::b_PRTIM2);}	
void MCU::TC2_::powerDown(void){MCU::Core::PRR_::SetBit(MCU::Core::PRR_::b_PRTIM2);}

void MCU::TC2_::TimerStop(void)
{
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ &= ~((1<<2)|(1<<1)|(1<<0));
	TCCR2B_ ::Set(byte_);
}

void MCU::TC2_::Prescaler::reset(void){MCU::Core::GTCCR_::SetBit(1);}
void MCU::TC2_::Prescaler::set_1(void)
{
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ &= ~((1<<2));
	byte_ |= (1<<0);
	TCCR2B_ ::Set(byte_);
}
		
void MCU::TC2_::Prescaler::set_8(void)
{
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ &= ~((1<<2)|(1<<0));
	byte_ |= (1<<1);
	TCCR2B_ ::Set(byte_);
}
			
void MCU::TC2_::Prescaler::set_32(void)
{
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ &= ~(1<<2);
	byte_ |= ((1<<1)|(1<<0));
	TCCR2B_ ::Set(byte_);
}
			
void MCU::TC2_::Prescaler::set_64(void)
{			
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ &= ~((1<<1)|(1<<0));
	byte_ |= (1<<2);
	TCCR2B_ ::Set(byte_);
}
			
void MCU::TC2_::Prescaler::set_128(void)
{
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ &= ~(1<<1);
	byte_ |= ((1<<2)|(1<<0));
	TCCR2B_ ::Set(byte_);
}
			
void MCU::TC2_::Prescaler::set_256(void)
{
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ &= ~(1<<0);
	byte_ |= ((1<<2)|(1<<1));
	TCCR2B_ ::Set(byte_);
}
			
void MCU::TC2_::Prescaler::set_1024(void)
{
	uint8_t byte_ = TCCR2B_ ::Get();
	byte_ |= ((1<<2)|(1<<1)|(1<<0));
	TCCR2B_ ::Set(byte_);
}

void MCU::TC2_::Interrupt_source::Overflow_Enable(void){TIMSK2_::SetBit(0);}
void MCU::TC2_::Interrupt_source::Overflow_Disable(void){TIMSK2_::ClearBit(0);}

