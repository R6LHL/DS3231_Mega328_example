#include "MCU_Mega_328.hpp"

void MCU::Sleep_::Go(void){asm("sleep");}

void MCU::Sleep_::Enable(void){SMCR_::SetBit(SMCR_::b_SE);}
void MCU::Sleep_::Disable(void){SMCR_::ClearBit(SMCR_::b_SE);}
bool MCU::Sleep_::is_Sleep_Enabled(void){return SMCR_::GetBit(SMCR_::b_SE);}

void MCU::Sleep_::Mode::Idle(void)
{
	uint8_t config_byte = SMCR_::Get();
	config_byte &= ~((1<<SMCR_::b_SM2)|(1<<SMCR_::b_SM1)|(1<<SMCR_::b_SM0));
	SMCR_::Set(config_byte);
}

void MCU::Sleep_::Mode::ADC_NoiseReduction(void)
{
    uint8_t config_byte = SMCR_::Get();
	config_byte &= ~((1<<SMCR_::b_SM2)|(1<<SMCR_::b_SM1));
	config_byte |= (1<<SMCR_::b_SM0);
	SMCR_::Set(config_byte);
}
		
void MCU::Sleep_::Mode::PowerDown(void)
{
	uint8_t config_byte = SMCR_::Get();
	config_byte &= ~((1<<SMCR_::b_SM2)|(1<<SMCR_::b_SM0));
	config_byte |= (1<<SMCR_::b_SM1);
	SMCR_::Set(config_byte);
}
		
void MCU::Sleep_::Mode::PowerSave(void)
{
	uint8_t config_byte = SMCR_::Get();
	config_byte &= ~(1<<SMCR_::b_SM2);
	config_byte |= ((1<<SMCR_::b_SM1)|(1<<SMCR_::b_SM0));
	SMCR_::Set(config_byte);
}	
		
void MCU::Sleep_::Mode::Standby(void)
{
	uint8_t config_byte = SMCR_::Get();
	config_byte &= ~(1<<SMCR_::b_SM0);
	config_byte |= ((1<<SMCR_::b_SM2)|(1<<SMCR_::b_SM1));
	SMCR_::Set(config_byte);
}
		
void MCU::Sleep_::Mode::ExtendedStandby(void)
{
    uint8_t config_byte = SMCR_::Get();
    config_byte |= ((1<<SMCR_::b_SM2)|(1<<SMCR_::b_SM1)|(1<<SMCR_::b_SM0));
    SMCR_::Set(config_byte);
}