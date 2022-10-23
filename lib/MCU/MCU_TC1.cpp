#include "MCU_Mega_328.hpp"

void MCU::TC1_::powerUp(void){MCU::Core::PRR_::ClearBit(MCU::Core::PRR_::b_PRTIM1);}
void MCU::TC1_::powerDown(void){MCU::Core::PRR_::SetBit(MCU::Core::PRR_::b_PRTIM1);}