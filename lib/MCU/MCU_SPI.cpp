#include "MCU_Mega_328.hpp"

bool MCU::SPI_::is_TRX_Complete(void){return SPSR0_::GetBit(7);}
bool MCU::SPI_::is_Data_Collision(void){return SPSR0_::GetBit(6);}
				
void MCU::SPI_::Interrupt_Enable(void){SPCR0_::SetBit(7);}
void MCU::SPI_::Interrupt_Disable(void){SPCR0_::ClearBit(7);}
	
void MCU::SPI_::Enable(void){SPCR0_::SetBit(6);}
void MCU::SPI_::Disable(void){SPCR0_::ClearBit(6);}
	
void MCU::SPI_::Set_As_Master(void){SPCR0_::SetBit(4);}
void MCU::SPI_::Set_As_Slave(void){SPCR0_::ClearBit(4);}

void MCU::SPI_::Data_Order::MSB_first(void){SPCR0_::ClearBit(5);}
void MCU::SPI_::Data_Order::LSB_first(void){SPCR0_::SetBit(5);}


void MCU::SPI_::Mode::set_0(void)
{
    uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~((1<<3)|(1<<2));
	SPCR0_::Set(config_byte);
}
			
void MCU::SPI_::Mode::set_1(void)
{
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~(1<<3);
	config_byte |= (1<<2);
	SPCR0_::Set(config_byte);
}
			
void MCU::SPI_::Mode::set_2(void)
{
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~(1<<2);
	config_byte |= (1<<3);
	SPCR0_::Set(config_byte);
}
			
void MCU::SPI_::Mode::set_3(void)
{
	uint8_t config_byte = SPCR0_::Get();
	config_byte |= ((1<<3)|(1<<2));
	SPCR0_::Set(config_byte);
}

void MCU::SPI_::Rate::F_div_2(void)
{
	SPSR0_::SetBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~((1<<1)|(1<<0));
	SPCR0_::Set(config_byte);
}
			
void MCU::SPI_::Rate::F_div_4(void)
{
	SPSR0_::ClearBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~(1<<1);
	config_byte |= (1<<0);
	SPCR0_::Set(config_byte);
}
			
void MCU::SPI_::Rate::F_div_8(void)
{
	SPSR0_::SetBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~(1<<0);
	config_byte |= (1<<1);
	SPCR0_::Set(config_byte);
}
				
void MCU::SPI_::Rate::F_div_16(void)
{
	SPSR0_::ClearBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte |= ((1<<1)|(1<<0));
	SPCR0_::Set(config_byte);
}
				
void MCU::SPI_::Rate::F_div_32(void)
{
	SPSR0_::SetBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~((1<<1)|(1<<0));
	SPCR0_::Set(config_byte);
}
				
void MCU::SPI_::Rate::F_div_32x2(void)
{
	SPSR0_::ClearBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~(1<<1);
	config_byte |= (1<<0);
	SPCR0_::Set(config_byte);
}
				
void MCU::SPI_::Rate::F_div_64(void)
{
	SPSR0_::SetBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte &= ~(1<<0);
	config_byte |= (1<<1);
	SPCR0_::Set(config_byte);
}
				
void MCU::SPI_::Rate::F_div_128(void)
{
	SPSR0_::ClearBit(0);
	uint8_t config_byte = SPCR0_::Get();
	config_byte |= ((1<<1)|(1<<0));
	SPCR0_::Set(config_byte);
}

 uint8_t MCU::SPI_::recieve(void)
{
	while(!is_TRX_Complete());
	return SPDR0_::Get();
}

void MCU::SPI_::transmit(uint8_t v)
{
	while(!is_TRX_Complete());
	SPDR0_::Set(v);
}

void MCU::SPI_::powerUp(void){MCU::Core::PRR_::ClearBit(MCU::Core::PRR_::b_PRSPI0);}	
void MCU::SPI_::powerDown(void){MCU::Core::PRR_::SetBit(MCU::Core::PRR_::b_PRSPI0);}