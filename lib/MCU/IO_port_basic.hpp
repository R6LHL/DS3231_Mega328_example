#ifndef _IO_PORT_BASIC
#define _IO_PORT_BASIC

#include <RegisterBase.hpp>

template <uint8_t T_PIN, uint8_t T_DDR, uint8_t T_PORT>
struct IO_port_basic
{
	struct PIN_ : public RegisterBase<T_PIN> {};
		
	struct DDR_ : public RegisterBase<T_DDR> {};
		
	struct PORT_ : public RegisterBase<T_PORT> {};
			
	static void pullupAll(void)
	{
		DDR_::Set(0x00);
		PORT_::Set(0xff);
	}
			
	static void Hi_Z_All(void)
	{
		DDR_::Set(0x00);
		PORT_::Set(0x00);
	}
};


#endif// _IO_PORT_BASIC
