#include "MCU_Mega_328.hpp"

bool MCU::Watchdog::is_I_Flag_Set(void)
{
    if (!(WDTCSR_::GetBit(WDTCSR_::b_WDIF))) return false;
	else return true;
}

void MCU::Watchdog::set_I_Flag(void){WDTCSR_::SetBit(WDTCSR_::b_WDIF);}
void MCU::Watchdog::clear_I_Flag(void){WDTCSR_::ClearBit(WDTCSR_::b_WDIF);}

void MCU::Watchdog::Interrupt_Enable(void){WDTCSR_::SetBit(WDTCSR_::b_WDIE);}
void MCU::Watchdog::Interrupt_Disable(void){WDTCSR_::ClearBit(WDTCSR_::b_WDIE);}

bool MCU::Watchdog::is_InterruptEnabled(void)
{
	if (!(WDTCSR_::GetBit(WDTCSR_::b_WDIE))) return false;
	else return true;
}

void MCU::Watchdog::Change_Enable(void){WDTCSR_::SetBit(WDTCSR_::b_WDCE);}
void MCU::Watchdog::Change_Disable(void){WDTCSR_::ClearBit(WDTCSR_::b_WDCE);}

void MCU::Watchdog::System_reset_enable(void)
{
    Change_Enable();
	WDTCSR_::SetBit(WDTCSR_::b_WDE);
}
		
void MCU::Watchdog::System_reset_disable(void)
{
	MCU::Core::MCUSR_::ClearBit(MCU::Core::MCUSR_::b_WDRF);
	Change_Enable();
	WDTCSR_::ClearBit(WDTCSR_::b_WDE);
}

void MCU::Watchdog::Prescaler::set_2048(void) 				//16ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP2)|
                            (1<<WDTCSR_::b_WDP1)|(1<<WDTCSR_::b_WDP0));
	Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_4096(void)				//32ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP2)|(1<<WDTCSR_::b_WDP1));
	byte_ |= (1<<WDTCSR_::b_WDP0);
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_8192(void)				//64ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP2)|(1<<WDTCSR_::b_WDP0));
	byte_ |= (1<<WDTCSR_::b_WDP1);
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_16348(void)				//128ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP2));
	byte_ |= ((1<<WDTCSR_::b_WDP1)|(1<<WDTCSR_::b_WDP0));
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_32768(void)				//256ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP1)|(1<<WDTCSR_::b_WDP0));
	byte_ |= (1<<WDTCSR_::b_WDP2);
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_65536(void)				//512ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP1));
	byte_ |= ((1<<WDTCSR_::b_WDP2)|(1<<WDTCSR_::b_WDP2));
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
			
void MCU::Watchdog::Prescaler::set_131072(void)				//1024ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP0));
	byte_ |= ((1<<WDTCSR_::b_WDP2)|(1<<WDTCSR_::b_WDP1));
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_262144(void)				//2048ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~(1<<WDTCSR_::b_WDP3);
	byte_ |= ((1<<WDTCSR_::b_WDP2)|(1<<WDTCSR_::b_WDP1)|(1<<WDTCSR_::b_WDP0));
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_524288(void)				//4096ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP2)|(1<<WDTCSR_::b_WDP1)|(1<<WDTCSR_::b_WDP0));
	byte_ |= (1<<WDTCSR_::b_WDP3);
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Prescaler::set_1048576(void)				//8192ms at 5v power supply
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDP2)|(1<<WDTCSR_::b_WDP1));
	byte_ |= ((1<<WDTCSR_::b_WDP3)|(1<<WDTCSR_::b_WDP0));
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}

void MCU::Watchdog::Mode::stop(void)
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~((1<<WDTCSR_::b_WDIE)|(1<<WDTCSR_::b_WDE));
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Mode::interrupt(void)
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ &= ~(1<<WDTCSR_::b_WDE);
	byte_ |= (1<<WDTCSR_::b_WDIE);
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Mode::SystemReset(void)
{
    uint8_t byte_ = WDTCSR_ ::Get();
    byte_ &= ~(1<<WDTCSR_::b_WDIE);
    byte_ |= (1<<WDTCSR_::b_WDE);
    MCU::Watchdog::Change_Enable();
    WDTCSR_ ::Set(byte_);
}
		
void MCU::Watchdog::Mode::Interrupt_And_SystemReset(void)
{
	uint8_t byte_ = WDTCSR_ ::Get();
	byte_ |= ((1<<WDTCSR_::b_WDIE)|(1<<WDTCSR_::b_WDE));
	MCU::Watchdog::Change_Enable();
	WDTCSR_ ::Set(byte_);
}