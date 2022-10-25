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

void MCU::TWI_::send_Start(void)
{
	error = Error::NO_ERROR;
    uint8_t byte_ = TWCR_::Get();
	byte_ |= (1<<TWCR_::b_TWINT)|(1<<TWCR_::b_TWSTA)|(1<<TWCR_::b_TWEN);
	TWCR_::Set(byte_);
	
    while (!(TWCR_::GetBit(TWCR_::b_TWINT))); //while TWINT == 0
	//Check start condition send
    if (get_status() != TWSR_::START_t) error = Error::NO_START;
	
}

void MCU::TWI_::send_SLA_W(uint8_t slave_address)
{
    if (error != Error::NO_ERROR) return;
	else
	{
		uint8_t byte_ = slave_address;
    	byte_ &= ~(1<<0); //set Write mode
    	TWDR_::Set(byte_);
		TWDR_::Set(byte_);
		byte_ = TWCR_::Get();
		byte_ |= (1<<TWCR_::b_TWINT)|(1<<TWCR_::b_TWEN); // start transmission SLA_W
		TWCR_::Set(byte_);
		
		while (!(TWCR_::GetBit(TWCR_::b_TWINT))); //while TWINT == 0

    	if (get_status() != TWSR_::MT_SLAW_t_ACK_r) error = Error::MT_SLAW_t_NACK_r;
		
	}
}

void MCU::TWI_::send_SLA_R(uint8_t slave_address)
{
	if (error != Error::NO_ERROR) return;
	else 
	{
		uint8_t byte_ = slave_address;
    	byte_ |= (1<<0); //set Read mode
    	TWDR_::Set(byte_);
		byte_ = TWCR_::Get();
		byte_ |= (1<<TWCR_::b_TWINT)|(1<<TWCR_::b_TWEN); // start transmission SLA_R
		TWCR_::Set(byte_);
		
		while (!(TWCR_::GetBit(TWCR_::b_TWINT))); //while TWINT == 0

    	if (get_status() != TWSR_::MR_SLAR_t_NACK_r) error = Error::MR_SLAR_t_NACK_r;
		
	}
}

void MCU::TWI_::send_Data_byte(uint8_t data_byte)
{
	if(error != Error::NO_ERROR) return;
	{
		TWDR_::Set(data_byte);
		
		while (!(TWCR_::GetBit(TWCR_::b_TWINT))); //while TWINT == 0

    	if (get_status() != TWSR_::MT_DATA_t_NACK_r) error = Error::MT_DATA_t_NACK_r;
		
	}
}

void MCU::TWI_::send_Stop(void)
{
    uint8_t byte_ = TWCR_::Get();
	byte_ |= (1<<TWCR_::b_TWINT)|(1<<TWCR_::b_TWSTA)|(1<<TWCR_::b_TWEN);
	TWCR_::Set(byte_);
	
    while (!(TWCR_::GetBit(TWCR_::b_TWINT))); //while TWINT == 0
	//Check start condition send
    if (get_status() != TWSR_::START_t) error = Error::NO_START;
	
}

/* !!!Как вариант!!!
#pragma vector = TWI_vect
SIGNAL(TWI_vect)
{
	uint8_t twi_status = MCU::TWI_::TWSR_::Get();

	switch (twi_status)
	{
	case MCU::TWI_::TWSR_::START_t:
		{
			if ()
			break;
		}

	
			
	default:
		MCU::TWI_::error = MCU::TWI_::get_status();
		break;
	}
}
*/
