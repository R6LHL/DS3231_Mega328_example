#include "MCU_Mega_328.hpp"

void MCU::TWI_::powerUp(void){MCU::Core::PRR_::ClearBit(MCU::Core::PRR_::b_PRTWI0);}
void MCU::TWI_::powerDown(void){MCU::Core::PRR_::SetBit(MCU::Core::PRR_::b_PRTWI0);}

uint8_t MCU::TWI_::get_status(void)
{
	uint8_t byte_ = TWSR_::Get();
	const uint8_t mask_ = ((1<<TWSR_::b_TWS4)|(1<<TWSR_::b_TWS3)|
                            (1<<TWSR_::b_TWS2)|(1<<TWSR_::b_TWS1)|
                            (1<<TWSR_::b_TWS0));
	byte_ &= mask_;
	return byte_;
}

uint8_t MCU::TWI_::get_prescaler(void)
{
	uint8_t byte_ = TWSR_::Get();
	const uint8_t mask_ = ((1<<TWSR_::b_TWPS1)|(1<<TWSR_::b_TWPS0));
	byte_ &= mask_;
	return byte_;
}
	
void MCU::TWI_::send_start(void)
{
	uint8_t byte_ = TWCR_::Get();
	byte_ |= (1<<TWSR_::b_TWS4)|(1<<TWSR_::b_TWS2);
	TWCR_::Set(byte_);
}

void MCU::TWI_::Prescaler::Set_1(void)
{
	uint8_t byte_ = TWSR_::Get();
	byte_ &= ~((1<<TWSR_::b_TWPS1)|(1<<TWSR_::b_TWPS0));
	TWSR_::Set(byte_);
}

void MCU::TWI_::Prescaler::Set_4(void)
{
	uint8_t byte_ = TWSR_::Get();
	byte_ &= ~(1<<TWSR_::b_TWPS1);
	byte_ |= (1<<TWSR_::b_TWPS0);
	TWSR_::Set(byte_);
}

void MCU::TWI_::Prescaler::Set_16(void)
{
	uint8_t byte_ = TWSR_::Get();
	byte_ &= ~(1<<TWSR_::b_TWPS0);
	byte_ |= (1<<TWSR_::b_TWPS1);
	TWSR_::Set(byte_);
}

void MCU::TWI_::Prescaler::Set_64(void)
{
	uint8_t byte_ = TWSR_::Get();
	byte_ |= (1<<TWSR_::b_TWPS1)|(1<<TWSR_::b_TWPS0);
	TWSR_::Set(byte_);
}