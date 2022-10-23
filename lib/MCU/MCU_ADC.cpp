#include "MCU_Mega_328.hpp"

void MCU::ADC_::Reference::AREF(void)
{
	uint8_t byte_ = ADMUX_::Get();
	byte_ &= ~((1<<7)|(1<<6));
	ADMUX_::Set(byte_);
}
			
void MCU::ADC_::Reference::AVCC(void)
{
	uint8_t byte_ = ADMUX_::Get();
	byte_ &= ~(1<<7);
	byte_ |= (1<<6);
	ADMUX_::Set(byte_);
}
			
void MCU::ADC_::Reference::Internal_1V1(void)
{
	uint8_t byte_ = ADMUX_::Get();
	byte_ |= ((1<<7)|(1<<6));
	ADMUX_::Set(byte_);
}

void MCU::ADC_::Adjust_Result::Left(void){ADMUX_::SetBit(5);}
void MCU::ADC_::Adjust_Result::Right(void){ADMUX_::ClearBit(5);}
bool MCU::ADC_::Adjust_Result::is_Result_Left_Adjusted(void){return ADMUX_::GetBit(5);}

 void MCU::ADC_::Select_Channel_(uint8_t ch)
{
    uint8_t byte_ = ADMUX_::Get();
	byte_ &= ~((1<<3)|(1<<2)|(1<<1)|(1<<0));
		
	if ((ch >=0) && (ch <= 7)){byte_ |= ch;}
	else {ch = 0;}
	ADMUX_::Set(byte_);
	return;
}

void MCU::ADC_::Enable(void){ADCSRA_::SetBit(7);}
void MCU::ADC_::Disable(void){ADCSRA_::ClearBit(7);}
void MCU::ADC_::Start_Conversion(void){ADCSRA_::SetBit(6);}
bool MCU::ADC_::Is_Conversion_Running(void){return ADCSRA_::GetBit(6);}
void MCU::ADC_::Auto_Trigger_Enable(void){ADCSRA_::SetBit(5);}
void MCU::ADC_::Interrupt_Enable(void){ADCSRA_::SetBit(3);}
void MCU::ADC_::Interrupt_Disable(void){ADCSRA_::ClearBit(3);}

void MCU::ADC_::Prescaler::Set_2(void)
{
	uint8_t config_byte = ADCSRA_::Get();
	config_byte &= ~((1<<2)|(1<<1)|(1<<0));
	ADCSRA_::Set(config_byte);
}
			
void MCU::ADC_::Prescaler::Set_4(void)
{
	uint8_t config_byte = ADCSRA_::Get();
	config_byte &= ~((1<<2)|(1<<0));
	config_byte |= (1<<1);
	ADCSRA_::Set(config_byte);
}
			
void MCU::ADC_::Prescaler::Set_8(void)
{
	uint8_t config_byte = ADCSRA_::Get();
	config_byte &= ~(1<<2);
	config_byte |= ((1<<1)|(1<<0));
	ADCSRA_::Set(config_byte);
}
			
void MCU::ADC_::Prescaler::Set_16(void)
{
	uint8_t config_byte = ADCSRA_::Get();
	config_byte &= ~((1<<1)|(1<<0));
	config_byte |= (1<<2);
	ADCSRA_::Set(config_byte);
}
			
void MCU::ADC_::Prescaler::Set_32(void)
{
	uint8_t config_byte = ADCSRA_::Get();
	config_byte &= ~(1<<1);
	config_byte |= ((1<<2)|(1<<0));
	ADCSRA_::Set(config_byte);
}
			
void MCU::ADC_::Prescaler::Set_64(void)
{
	uint8_t config_byte = ADCSRA_::Get();
	config_byte &= ~(1<<0);
	config_byte |= ((1<<2)|(1<<1));
	ADCSRA_::Set(config_byte);
}
			
void MCU::ADC_::Prescaler::Set_128(void)
{
	uint8_t config_byte = ADCSRA_::Get();
	config_byte |= ((1<<2)|(1<<1)|(1<<0));
	ADCSRA_::Set(config_byte);
}

void MCU::ADC_::Trigger_Source::Free_running(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte &= ~((1<<2)|(1<<1)|(1<<0));
	ADCSRB_::Set(config_byte);
}
			
void MCU::ADC_::Trigger_Source::AC_(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte &= ~((1<<2)|(1<<1));
	config_byte |= (1<<0);
	ADCSRB_::Set(config_byte);
}
			
void MCU::ADC_::Trigger_Source::EXINT0_(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte &= ~((1<<2)|(1<<0));
	config_byte |= (1<<1);
	ADCSRB_::Set(config_byte);
}
			
void MCU::ADC_::Trigger_Source::TC0_Comp_Match_A(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte &= ~(1<<2);
	config_byte |= ((1<<1)|(1<<0));
	ADCSRB_::Set(config_byte);
}
			
void MCU::ADC_::Trigger_Source::TC0_Overflow(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte &= ~((1<<1)|(1<<0));
	config_byte |= (1<<2);
	ADCSRB_::Set(config_byte);
}
			
void MCU::ADC_::Trigger_Source::TC1_Comp_Match_B(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte &= ~(1<<1);
	config_byte |= ((1<<2)|(1<<0));
	ADCSRB_::Set(config_byte);
}
			
void MCU::ADC_::Trigger_Source::TC1_Overflow(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte &= ~(1<<0);
	config_byte |= ((1<<2)|(1<<1));
	ADCSRB_::Set(config_byte);
}
			
void MCU::ADC_::Trigger_Source::TC1_Capture_Event(void)
{
	uint8_t config_byte = ADCSRB_::Get();
	config_byte |= ((1<<2)|(1<<1)|(1<<0));
	ADCSRB_::Set(config_byte);
}

uint16_t MCU::ADC_::Get_Value(void)
{
	while(!Is_Conversion_Running());
	uint8_t low_byte = ADCL_::Get();
	uint8_t high_byte = ADCH_::Get();
	uint16_t value = 0;
	if(! (Adjust_Result::is_Result_Left_Adjusted()))
	{
		value |= (high_byte<<8)|(low_byte);
	}
	else {value |= (high_byte<<14)|(low_byte<<6);}
	return value;
}


void MCU::ADC_::digital_Input_Disable(uint8_t adc_pin_number)
{
	if ((adc_pin_number >= 0) && (adc_pin_number <= 5))
	{
		DIDR0_::SetBit(adc_pin_number);
	}
	else return;
}
		
void MCU::ADC_::digital_Input_Enable(uint8_t adc_pin_number)
{
	if ((adc_pin_number >= 0) && (adc_pin_number <= 5))
	{
		DIDR0_::ClearBit(adc_pin_number);
	}
	else return;
}

void MCU::ADC_::powerUp(void){MCU::Core::PRR_::ClearBit(MCU::Core::PRR_::b_PRADC);}
void MCU::ADC_::powerDown(void){MCU::Core::PRR_::SetBit(MCU::Core::PRR_::b_PRADC);}

