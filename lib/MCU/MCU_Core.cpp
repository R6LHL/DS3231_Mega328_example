#include "MCU_Mega_328.hpp"

void MCU::Core::powerDown_All_Peripherials(void)
{
    PRR_::Set(0b11111111);
    MCU::AC_::powerDown();
}