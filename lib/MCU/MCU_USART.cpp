#include "MCU_Mega_328.hpp"

bool MCU::USART_::is_RX_Complete(void){return UCSR0A_::GetBit(7);}
bool MCU::USART_::is_TX_Complete(void){return UCSR0A_::GetBit(6);}
void MCU::USART_::TX_Complete(void){UCSR0A_::ClearBit(6);}
bool MCU::USART_::is_Data_Register_Empty(void){return UCSR0A_::GetBit(5);}
bool MCU::USART_::is_Frame_Error(void){return UCSR0A_::GetBit(4);}
bool MCU::USART_::is_Data_Overrun(void){return UCSR0A_::GetBit(3);}
bool MCU::USART_::is_Parity_Error(void){return UCSR0A_::GetBit(2);}

uint8_t MCU::USART_::RX(void)
{
	while (!is_RX_Complete());
	return UDR0_::Get();
}
		
uint16_t MCU::USART_::RX_9bit(void)
{
	while (!is_RX_Complete());
	uint16_t word = UDR0_::Get();
	uint8_t byte = UCSR0B_::GetBit(1);
	word |= (byte<<8);
	return word;
}
		
void MCU::USART_::TX(uint8_t value)
{
	while (!is_Data_Register_Empty());
	UDR0_::Set(value);
}
		
void MCU::USART_::TX_9bit(uint16_t value)
{
	while (!is_Data_Register_Empty());
	bool bit = value & 0b0000000100000000;
	uint16_t word_ = value & 0b0000000011111111;
	UDR0_::Set(word_);
	if (bit==true)UCSR0B_::SetBit(0);
	else UCSR0B_::ClearBit(0);
}

void MCU::USART_::Interrupts::RX_Complete_Enable(void){UCSR0B_::SetBit(7);}
void MCU::USART_::Interrupts::RX_Complete_Disable(void){UCSR0B_::ClearBit(7);}
		
void MCU::USART_::Interrupts::TX_Complete_Enable(void){UCSR0B_::SetBit(6);}
void MCU::USART_::Interrupts::TX_Complete_Disable(void){UCSR0B_::ClearBit(6);}
		
void MCU::USART_::Interrupts::Data_reg_Empty_Enable(void){UCSR0B_::SetBit(5);}
void MCU::USART_::Interrupts::Data_reg_Empty_Disable(void){UCSR0B_::ClearBit(5);}
		
void MCU::USART_::RX_Enable(void){UCSR0B_::SetBit(4);}
void MCU::USART_::RX_Disable(void){UCSR0B_::ClearBit(4);}
		
void MCU::USART_::TX_Enable(void){UCSR0B_::SetBit(3);}
void MCU::USART_::TX_Disable(void)
{
	while (!is_Data_Register_Empty());
	while (!is_TX_Complete());
	UCSR0B_::ClearBit(3);
}

void MCU::USART_::Set::BuadRate_div_16(void){UCSR0A_::ClearBit(1);}
void MCU::USART_::Set::BuadRate_div_8(void){UCSR0A_::SetBit(1);}
void MCU::USART_::Set::Multiprocessor_Mode(void){UCSR0A_::SetBit(0);}
void MCU::USART_::Set::noMultiprocessor_Mode(void){UCSR0A_::ClearBit(0);}
			
void MCU::USART_::Set::Stop_1bit(void){UCSR0C_::ClearBit(3);}
void MCU::USART_::Set::Stop_2bits(void){UCSR0C_::SetBit(3);}
			
void MCU::USART_::Set::Clock_polarity0(void){UCSR0C_::ClearBit(0);}
void MCU::USART_::Set::Clock_polarity1(void){UCSR0C_::SetBit(0);}

void MCU::USART_::Set::Character_size::b5_bit(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte &= ~((1<<2)|(1<<1));
	UCSR0C_::Set(config_byte);
			
	config_byte = UCSR0B_::Get();
	config_byte &= ~(1<<3);
	UCSR0B_::Set(config_byte);
}
				
void MCU::USART_::Set::Character_size::b6_bit(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte &= ~(1<<2);
	config_byte |= (1<<1);
	UCSR0C_::Set(config_byte);
					
	config_byte = UCSR0B_::Get();
	config_byte &= ~(1<<3);
	UCSR0B_::Set(config_byte);
}
				
void MCU::USART_::Set::Character_size::b7_bit(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte &= ~(1<<1);
	config_byte |= (1<<2);
	UCSR0C_::Set(config_byte);
		
	config_byte = UCSR0B_::Get();
	config_byte &= ~(1<<3);
	UCSR0B_::Set(config_byte);
}
				
void MCU::USART_::Set::Character_size::b8_bit(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte |= (1<<2)|(1<<1);
	UCSR0C_::Set(config_byte);
					
	config_byte = UCSR0B_::Get();
	config_byte &= ~(1<<3);
	UCSR0B_::Set(config_byte);
}
				
void MCU::USART_::Set::Character_size::b9_bit(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte |= ((1<<2)|(1<<1));
	UCSR0C_::Set(config_byte);
			
	config_byte = UCSR0B_::Get();
	config_byte |= (1<<3);
	UCSR0B_::Set(config_byte);
}

void MCU::USART_::Set::Mode::Asynchronous(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte &= ~((1<<7)|(1<<6));
	UCSR0C_::Set(config_byte);
}
				
void MCU::USART_::Set::Mode::Synchronous(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte &= ~(1<<7);
	config_byte |= (1<<6);
	UCSR0C_::Set(config_byte);
}
				
void MCU::USART_::Set::Mode::MasterSPI(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte |= (1<<7)|(1<<6);
	UCSR0C_::Set(config_byte);
}

uint8_t MCU::USART_::Set::Mode::get(void)
{
	uint8_t byte_ = UCSR0C_::Get();
	byte_ &= 0b11000000;
	return byte_;
}

void MCU::USART_::Set::Parity_control::disable(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte &= ~((1<<5)|(1<<4));
	UCSR0C_::Set(config_byte);
}
				
void MCU::USART_::Set::Parity_control::even(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte &= ~(1<<4);
	config_byte |= (1<<5);
	UCSR0C_::Set(config_byte);
}
				
void MCU::USART_::Set::Parity_control::odd(void)
{
	uint8_t config_byte = UCSR0C_::Get();
	config_byte |= ((1<<5)|(1<<4));
	UCSR0C_::Set(config_byte);
}

void MCU::USART_::Set::BaudRate(uint32_t f_cpu, uint16_t baud)
{
	uint16_t ubrr;

	switch (Mode::get())
	{
	case 0b00000000:
		if(MCU::USART_::UCSR0A_::GetBit(1) == 0)
		{
			ubrr = (f_cpu / 16 / baud) - 1;
		}
		else ubrr = (f_cpu / 8 / baud) - 1;
		break;
	
	case 0b01000000:
		ubrr = (f_cpu / 2 / baud) - 1;
		break;
	
	default:
		break;
	}
	
	uint8_t ubrrh = ubrr >> 8;
	uint8_t ubrrl = ubrr;

	MCU::USART_::UBRR0H_::Set(ubrrh);
	MCU::USART_::UBRR0L_::Set(ubrrl);
	
}

void MCU::USART_::powerUp(void){MCU::Core::PRR_::ClearBit(MCU::Core::PRR_::b_PRUSART0);}	
void MCU::USART_::powerDown(void){MCU::Core::PRR_::SetBit(MCU::Core::PRR_::b_PRUSART0);}
