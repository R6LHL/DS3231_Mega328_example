#include "MCU_Mega_328.hpp"

void MCU::TC0_::powerUp(void){MCU::Core::PRR_::ClearBit(MCU::Core::PRR_::b_PRTIM0);}
void MCU::TC0_::powerDown(void){MCU::Core::PRR_::SetBit(MCU::Core::PRR_::b_PRTIM0);}