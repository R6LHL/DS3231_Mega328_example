#include "MCU_Mega_328.hpp"

void MCU::EXINT_::INT0_Enable(void){EIMSK_::SetBit(EIMSK_::b_INT0);}
void MCU::EXINT_::INT0_Disable(void){EIMSK_::ClearBit(EIMSK_::b_INT0);}

void MCU::EXINT_::INT0_Mode::low_level(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte &= ~(1<<MCU::EXINT_::EICRA_::b_ISC01)|(1<<MCU::EXINT_::EICRA_::b_ISC00);
    EICRA_::Set(raw_byte);
}

void MCU::EXINT_::INT0_Mode::any_change(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte &= ~(1<<MCU::EXINT_::EICRA_::b_ISC01);
    raw_byte |= (1<<MCU::EXINT_::EICRA_::b_ISC00);
    EICRA_::Set(raw_byte);
}

void MCU::EXINT_::INT0_Mode::falling_edge(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte &= ~(1<<MCU::EXINT_::EICRA_::b_ISC00);
    raw_byte |= (1<<MCU::EXINT_::EICRA_::b_ISC01);
    EICRA_::Set(raw_byte);
}

void MCU::EXINT_::INT0_Mode::rising_edge(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte |= (1<<MCU::EXINT_::EICRA_::b_ISC01)|(1<<MCU::EXINT_::EICRA_::b_ISC00);
    EICRA_::Set(raw_byte);
}

void MCU::EXINT_::INT1_Enable(void){EIMSK_::SetBit(EIMSK_::b_INT1);}
void MCU::EXINT_::INT1_Disable(void){EIMSK_::ClearBit(EIMSK_::b_INT1);}

void  MCU::EXINT_::INT1_Mode::low_level(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte &= ~(1<<MCU::EXINT_::EICRA_::b_ISC11)|(1<<MCU::EXINT_::EICRA_::b_ISC10);
    EICRA_::Set(raw_byte);
}

void MCU::EXINT_::INT1_Mode::any_change(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte &= ~(1<<MCU::EXINT_::EICRA_::b_ISC11);
    raw_byte |= (1<<MCU::EXINT_::EICRA_::b_ISC10);
    EICRA_::Set(raw_byte);
}

void MCU::EXINT_::INT1_Mode::falling_edge(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte &= ~(1<<MCU::EXINT_::EICRA_::b_ISC10);
    raw_byte |= (1<<MCU::EXINT_::EICRA_::b_ISC11);
    EICRA_::Set(raw_byte);
}

void MCU::EXINT_::INT1_Mode::rising_edge(void)
{
    uint8_t raw_byte = EICRA_::Get();
    raw_byte |= (1<<MCU::EXINT_::EICRA_::b_ISC11)|(1<<MCU::EXINT_::EICRA_::b_ISC10);
    EICRA_::Set(raw_byte);
}