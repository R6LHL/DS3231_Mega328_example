#include "MCU_Mega_328.hpp"

void MCU::Core::powerDown_All_Peripherials(void)
{
    cli();
    PRR_::Set(0b11111111);
    MCU::AC_::powerDown();
    sei();
}

void MCU::Core::powerUp_All_Peripherials(void)
{
    cli();
    PRR_::Set(0b00000000);
    MCU::AC_::powerUp();
    sei();
}

void MCU::Core::BrownOut_Disable(void){
    cli();
    uint8_t byte_ = MCUCR_::Get();
    byte_ |= (1 << MCUCR_::b_BOD)|(1 << MCUCR_:: b_BODSE);
    MCUCR_::Set(byte_);
    sei();
}