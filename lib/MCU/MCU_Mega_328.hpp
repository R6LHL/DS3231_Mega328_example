#ifndef MCU_Mega328_HPP
#define MCU_Mega328_HPP

#include <RegisterBase.hpp>
#include <IO_port_basic.hpp>

// Atmega328 MicroController Unit 
namespace MCU
{
		
	namespace IO_
	{
		struct PORTB_ : public IO_port_basic<0x23, 0x24, 0x25> {};
		struct PORTC_ : public IO_port_basic<0x26, 0x27, 0x28> {};
		struct PORTD_ : public IO_port_basic<0x29, 0x2A, 0x2B> {};
		
		//General purpose IO register 0
		struct GPIOR0_ : public RegisterBase<0x3e> {};
		//end General purpose IO register 0
		
		//General purpose IO register 1
		struct GPIOR1_ : public RegisterBase<0x4a> {};
		//end General purpose IO register 1
		
		//General purpose IO register 2
		struct GPIOR2_ : public RegisterBase<0x4b> {};
		//end General purpose IO register 2
		
	} // end IO
	
	namespace Sleep_
	{
		// Sleep mode control register
		struct SMCR_ : public RegisterBase<0x53> {};
		
		static void Enable(void){SMCR_::SetBit(0);}
		static void Disable(void){SMCR_::ClearBit(0);}
		static void Go(void){}
		
		namespace Mode
		{
			static void Idle(void)
			{
				uint8_t config_byte = SMCR_::Get();
				config_byte &= ~((1<<3)|(1<<2)|(1<<1));
				SMCR_::Set(config_byte);
			}
		
			static void ADC_NoiseReduction(void)
			{
				uint8_t config_byte = SMCR_::Get();
				config_byte &= ~((1<<3)|(1<<2));
				config_byte |= (1<<1);
				SMCR_::Set(config_byte);
			}
		
			static void PowerDown(void)
			{
				uint8_t config_byte = SMCR_::Get();
				config_byte &= ~((1<<3)|(1<<1));
				config_byte |= (1<<2);
				SMCR_::Set(config_byte);
			}
		
			static void PowerSave(void)
			{
				uint8_t config_byte = SMCR_::Get();
				config_byte &= ~(1<<3);
				config_byte |= ((1<<2)|(1<<1));
				SMCR_::Set(config_byte);
			}	
		
			static void Standby(void)
			{
				uint8_t config_byte = SMCR_::Get();
				config_byte &= ~(1<<1);
				config_byte |= ((1<<3)|(1<<2));
				SMCR_::Set(config_byte);
			}
		
			static void ExtendedStandby(void)
			{
				uint8_t config_byte = SMCR_::Get();
				config_byte |= ((1<<3)|(1<<2)|(1<<1));
				SMCR_::Set(config_byte);
			}
		}
		
	} // end Sleep mode control register
	
	namespace Core
	{
		// Status register
		struct SREG_ : public RegisterBase<0x5f> {};
		// end Status register
		
		// Stack pointer register low
		struct SPL_ : public RegisterBase<0x5d> {};
		// end Stack pointer register low
		
		// Stack pointer register low
		struct SPH_ : public RegisterBase<0x5e> {};
		// end Stack pointer register low
		
		// MCU control register
		struct MCUCR_ : public RegisterBase<0x55> {};
		// end MCU control register
		
		// MCU status register - indicates which event is reset occured
		// 0x01 - if power-on
		// 0x02 - if external reset
		// 0x04 - if brown-out reset
		// 0x08 - if watchdog reset
		struct MCUSR_ : public RegisterBase<0x54> {};
		// end MCU status register
				
		// Oscillator calibration register
		struct OSCCAL_ : public RegisterBase<0x66> {};
		// end Oscillator calibration register
		
		//Clock Precaler register
		struct CLKPR_ : public RegisterBase<0x61> {};
		// end Clock Precaler register
		
		//Power reduction register
		struct PRR_ : public RegisterBase<0x64> {};
			
		/*
		inline void cli(void) {asm volatile ("cli");}
		inline void sei(void) {asm volatile ("sei");}
		*/
		
	}// end MCU core control registers
		
	namespace Watchdog	
	{
		/////////////////////////////////////////////////////////////////
		//Watchdog timer control register
		struct WDTCSR_ : public RegisterBase<0x60> {};
		
		//WDT interrupt flag functions
		static bool is_I_Flag_Set(void)
		{
			if (!(WDTCSR_::GetBit(7))) return false;
			else return true;
		}
		
		static void set_I_Flag(void){WDTCSR_::SetBit(7);}
		static void clear_I_Flag(void){WDTCSR_::SetBit(7);}
		//end WDT interrupt flag functions
		
		//WDT interrupt enable flag functions
		static void Interrupt_Enable(void){WDTCSR_::SetBit(6);}
		static void Interrupt_Disable(void){WDTCSR_::ClearBit(6);}
		static bool is_InterruptEnabled(void)
		{
			if (!(WDTCSR_::GetBit(6))) return false;
			else return true;
		}
		// end WDT interrupt enable flag functions
		
		// WDT Change enable flag functions
		static void Change_Enable(void){WDTCSR_::SetBit(4);}
		static void Change_Disable(void){WDTCSR_::ClearBit(4);}
		// end WDT Change enable flag functions
		
		// WDT System reset enable flag functions
		static void System_reset_enable(void)
		{
			Change_Enable();
			WDTCSR_::SetBit(3);
		}
		
		static void System_reset_disable(void)
		{
			Change_Enable();
			WDTCSR_::ClearBit(3);
		}
		// end WDT System reset enable flag functions
		
		namespace Prescaler
		{
			//WDT prescaler functions
		  static void set_2048(void) 				//16ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<5)|(1<<2)|(1<<1)|(1<<0));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_4096(void)				//32ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<5)|(1<<2)|(1<<1));
				byte_ |= (1<<0);
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_8192(void)				//64ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<5)|(1<<2)|(1<<0));
				byte_ |= (1<<1);
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_16348(void)				//128ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<5)|(1<<2));
				byte_ |= ((1<<1)|(1<<0));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_32768(void)				//256ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<5)|(1<<1)|(1<<0));
				byte_ |= (1<<2);
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_65536(void)				//512ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<5)|(1<<1));
				byte_ |= ((1<<2)|(1<<0));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
			
			static void set_131072(void)				//1024ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<5)|(1<<0));
				byte_ |= ((1<<2)|(1<<1));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_262144(void)				//2048ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~(1<<5);
				byte_ |= ((1<<2)|(1<<1)|(1<<0));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_524288(void)				//4096ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<2)|(1<<1)|(1<<0));
				byte_ |= (1<<5);
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void set_1048576(void)				//8192ms at 5v power supply
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<2)|(1<<1));
				byte_ |= ((1<<5)|(1<<0));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		}
		//end WDT prescaler functions
		namespace Mode
		{
			//WDT Configurations if WDTON fuse bit is not set
			static void stop(void)
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~((1<<6)|(1<<3));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void interrupt(void)
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ &= ~(1<<3);
				byte_ |= (1<<6);
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		
			static void SystemReset(void)
			{
			uint8_t byte_ = WDTCSR_ ::Get();
			byte_ &= ~(1<<6);
			byte_ |= (1<<3);
			Change_Enable();
			WDTCSR_ ::Set(byte_);
			}
		
			static void Interrupt_And_SystemReset(void)
			{
				uint8_t byte_ = WDTCSR_ ::Get();
				byte_ |= ((1<<6)|(1<<3));
				Change_Enable();
				WDTCSR_ ::Set(byte_);
			}
		}
		//end WDT Configurations
		// end Watchdog timer control register
		
		//General TC control register
		struct GTCCR_ : public RegisterBase<0x43>	{};
		//end General TC control register
	}	
	
	namespace EXINT_ //external interrupts
	{
		//External interrupt control register A
		struct EICRA_ : public RegisterBase<0x69> {};
		// end External interrupt control register A
		
		//External interrupt mask register
		struct EIMSK_ : public RegisterBase<0x3d> {};
		// end External interrupt mask register
		
		//External interrupt flag register
		struct EIFR_ : public RegisterBase<0x3c> {};
		// end External interrupt flag register
		
		//Pin Change Interrupt Control register
		struct PCICR_ : public RegisterBase<0x68> {};
		// end Pin Change Interrupt Control register
		
		//Pin Change Interrupt flag register
		struct PCIFR_ : public RegisterBase<0x3b> {};
		// end Pin Change Interrupt flag register
		
		//Pin Change mask register 2
		struct PCMSK2_ : public RegisterBase<0x6d> {};
		// end Pin Change mask register 2
		
		//Pin Change mask register 1
		struct PCMSK1_ : public RegisterBase<0x6c> {};
		// end Pin Change mask register 1
		
		//Pin Change mask register 0
		struct PCMSK0_ : public RegisterBase<0x6b> {};
		// end Pin Change mask register 0
		
	}// end external interrupts
		
	namespace TC0_ // Timer-counter 0 8bit
	{
		//TC0_ flag register
		struct TIFR0_ : public RegisterBase<0x35> {};
		// end TC0_ flag register
	
		// TC0_ control register A
		struct TCCR0A_ : public RegisterBase<0x44> {};
		//end  TC0_ control register A
		
		// TC0_ control register B
		struct TCCR0B_ : public RegisterBase<0x45> {};
		//end TC0_ control register B
		
		// TC0_ interrupt mask register
		struct TIMSK0_ : public RegisterBase<0x6e> {};
		// end TC0_ interrupt mask register
			
		// TC0_ Counter value register
		struct TCNT0_ : public RegisterBase<0x46> {};
		// end TC0_ Counter value register
			
		// TC0_ output compare register A
		struct OCR0A_ : public RegisterBase<0x47> {};
		//end TC0_ output compare register A
			
		// TC0_ output compare register B
		struct OCR0B_ : public RegisterBase<0x48> {};
		//end TC0_ output compare register B
			
		//Timer0 power management
		static void powerUp(void){Core::PRR_::ClearBit(5);}
		static void powerDown(void){Core::PRR_::SetBit(5);}
		//end Timer0 power management
						
	} //end Timer-counter 0
		
	namespace TC1_ // Timer-counter 1 16bit
	{
		//TC1_ control register A
		struct TCCR1A_ : public RegisterBase<0x80> {}; 
		//end TC1_ control register A
			
		//TC1_ control register B
		struct TCCR1B_ : public RegisterBase<0x81> {};
		//end TC1_ control register B
			
		//TC1_ control register C
		struct TCCR1C_ : public RegisterBase<0x82> {};
		//end TC1_ control register C
			
		//?????????????????Access????????????????????????????????????
		// TC1_ Counter value low byte
		struct TCNT1L_ : public RegisterBase<0x84> {};
		//end TC1_ Counter value low byte
			
		// TC1_ Counter value high byte
		struct TCNT1H_ : public RegisterBase<0x85> {};
		//end TC1_ Counter value high byte
		//?????????????????Access????????????????????????????????????
			
		//?????????????????Access????????????????????????????????????
		// TC1_ input capture register 1 low byte
		struct ICR1L_ : public RegisterBase<0x86> {};
		//end TC1_ input capture register1 low byte
			
		// TC1_ input capture register 1 high byte
		struct ICR1H_ : public RegisterBase<0x87> {};
		//end TC1_ input capture register 1 high byte
		//?????????????????Access????????????????????????????????????
			
		//TC1_ Output compare register 1 A low byte
		struct OCR1AL_ : public RegisterBase<0x88> {};
		//end TC1_ Output compare register 1 A low byte
			
		//TC1_ Output compare register 1 A high byte
		struct OCR1AH_ : public RegisterBase<0x89> {};
		//end TC1_ Output compare register 1 A high byte
			
		//TC1_ Output compare register 1 B low byte
		struct OCR1BL_ : public RegisterBase<0x8a> {};
		//end TC1_ Output compare register 1 B low byte
			
		//TC1_ Output compare register 1 B high byte
		struct OCR1BH_ : public RegisterBase<0x8b> {};
		//end TC1_ Output compare register 1 B high byte
			
		//TC1_ interrupt mask register
		struct TIMSK1_ : public RegisterBase<0x6f> {};
		// end TC1_ interrupt mask register
			
		//TC1_ interrupt flag register
		struct TIFR1_ : public RegisterBase<0x36> {};
		// end TC1_ interrupt flag register
			
			
		//Timer1 power management
		static void powerUp(void){Core::PRR_::ClearBit(3);}
		static void powerDown(void){Core::PRR_::SetBit(3);}
		//end Timer1 power management
					
	}//end  Timer-counter 1 16bit
		
	namespace TC2_ // Timer-counter 2 8bit
	{	
		//TC2_ control register A
		struct TCCR2A_ : public RegisterBase<0xb0> {};
		// end TC2_ control register A
		
		//TC2_ control register B
		struct TCCR2B_ : public RegisterBase<0xb1> {};
		// end TC2_ control register B
		
		//TC2_ counter value register
		struct TCNT2_ : public RegisterBase<0xb2> {};
		// end TC2_ counter value register
			
		//TC2_ output compare register A
		struct OCR2A_ : public RegisterBase<0xb3> {};
		// end TC2_ output compare register A
			
		//TC2_ output compare register B
		struct OCR2B_ : public RegisterBase<0xb4e> {};
		// end TC2_ output compare register B
			
		//TC2_ iterrupt mask register
		struct TIMSK2_ : public RegisterBase<0x70> {};
		// end TC2_ iterrupt mask register
						
		//TC2_ iterrupt flag register
		struct TIFR2_ : public RegisterBase<0x37> {};
		// end TC2_ iterrupt flag register
			
		//Asynchronous status register
		struct ASSR_ : public RegisterBase<0xb6> {};
		//end Asynchronous status register
			
		//Timer2 power management
		static void powerUp(void){Core::PRR_::ClearBit(6);}	
		static void powerDown(void){Core::PRR_::SetBit(6);}
		//end Timer2 power management
			
		static void TimerStop(void)
		{
			uint8_t byte_ = TCCR2B_ ::Get();
			byte_ &= ~((1<<2)|(1<<1)|(1<<0));
			TCCR2B_ ::Set(byte_);
		}
		
		namespace Prescaler
		{
			static void reset(void){Watchdog::GTCCR_::SetBit(1);}
			
			static void set_1(void)
			{
				uint8_t byte_ = TCCR2B_ ::Get();
				byte_ &= ~((1<<2));
				byte_ |= (1<<0);
				TCCR2B_ ::Set(byte_);
			}
			
			static void set_8(void)
			{
				uint8_t byte_ = TCCR2B_ ::Get();
				byte_ &= ~((1<<2)|(1<<0));
				byte_ |= (1<<1);
				TCCR2B_ ::Set(byte_);
			}
			
			static void set_32(void)
			{
				uint8_t byte_ = TCCR2B_ ::Get();
				byte_ &= ~(1<<2);
				byte_ |= ((1<<1)|(1<<0));
				TCCR2B_ ::Set(byte_);
			}
			
			static void set_64(void)
			{			
				uint8_t byte_ = TCCR2B_ ::Get();
				byte_ &= ~((1<<1)|(1<<0));
				byte_ |= (1<<2);
				TCCR2B_ ::Set(byte_);
			}
			
			static void set_128(void)
			{
				uint8_t byte_ = TCCR2B_ ::Get();
				byte_ &= ~(1<<1);
				byte_ |= ((1<<2)|(1<<0));
				TCCR2B_ ::Set(byte_);
			}
			
			static void set_256(void)
			{
				uint8_t byte_ = TCCR2B_ ::Get();
				byte_ &= ~(1<<0);
				byte_ |= ((1<<2)|(1<<1));
				TCCR2B_ ::Set(byte_);
			}
			
			static void set_1024(void)
			{
				uint8_t byte_ = TCCR2B_ ::Get();
				byte_ |= ((1<<2)|(1<<1)|(1<<0));
				TCCR2B_ ::Set(byte_);
			}
		}
		
		namespace Interrupt_source
		{
			static void Overflow_Enable(void){TIMSK2_::SetBit(0);}
			static void Overflow_Disable(void){TIMSK2_::ClearBit(0);}
		}
			
	}// end Timer-counter 2 8bit

	
	
	//Serial-peripherial interface
	namespace SPI_
	{
		//SPI_ control register 0
		struct SPCR0_ : public RegisterBase<0x4c> {};
		//SPI_ status register 0
		struct SPSR0_ : public RegisterBase<0x4d> {};

		static bool is_TRX_Complete(void){return SPSR0_::GetBit(7);}
		static bool is_Data_Collision(void){return SPSR0_::GetBit(6);}
				
		static void Interrupt_Enable(void){SPCR0_::SetBit(7);}
		static void Interrupt_Disable(void){SPCR0_::ClearBit(7);}
		
		static void Enable(void){SPCR0_::SetBit(6);}
		static void Disable(void){SPCR0_::ClearBit(6);}
		
		static void Set_As_Master(void){SPCR0_::SetBit(4);}
		static void Set_As_Slave(void){SPCR0_::ClearBit(4);}
						
		namespace Data_Order
		{
			static void MSB_first(void){SPCR0_::ClearBit(5);}
			static void LSB_first(void){SPCR0_::SetBit(5);}
		}
		
		namespace Mode
		{
		
			static void set_0(void)
			{
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~((1<<3)|(1<<2));
				SPCR0_::Set(config_byte);
			}
			
			static void set_1(void)
			{
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~(1<<3);
				config_byte |= (1<<2);
				SPCR0_::Set(config_byte);
			}
			
			static void set_2(void)
			{
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~(1<<2);
				config_byte |= (1<<3);
				SPCR0_::Set(config_byte);
			}
			
			static void set_3(void)
			{
				uint8_t config_byte = SPCR0_::Get();
				config_byte |= ((1<<3)|(1<<2));
				SPCR0_::Set(config_byte);
			}
		}
		
		namespace Rate
		{
			static void F_div_2(void)
			{
				SPSR0_::SetBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~((1<<1)|(1<<0));
				SPCR0_::Set(config_byte);
			}
			
			static void F_div_4(void)
			{
				SPSR0_::ClearBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~(1<<1);
				config_byte |= (1<<0);
				SPCR0_::Set(config_byte);
			}
			
			static void F_div_8(void)
			{
				SPSR0_::SetBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~(1<<0);
				config_byte |= (1<<1);
				SPCR0_::Set(config_byte);
			}
				
			static void F_div_16(void)
			{
				SPSR0_::ClearBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte |= ((1<<1)|(1<<0));
				SPCR0_::Set(config_byte);
			}
				
			static void F_div_32(void)
			{
				SPSR0_::SetBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~((1<<1)|(1<<0));
				SPCR0_::Set(config_byte);
			}
				
			static void F_div_32x2(void)
			{
				SPSR0_::ClearBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~(1<<1);
				config_byte |= (1<<0);
				SPCR0_::Set(config_byte);
			}
				
			static void F_div_64(void)
			{
				SPSR0_::SetBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte &= ~(1<<0);
				config_byte |= (1<<1);
				SPCR0_::Set(config_byte);
			}
				
			static void F_div_128(void)
			{
				SPSR0_::ClearBit(0);
				uint8_t config_byte = SPCR0_::Get();
				config_byte |= ((1<<1)|(1<<0));
				SPCR0_::Set(config_byte);
			}
				
		}
		//end SPI_ control register 0
		
		//SPI_ data register 0
		struct SPDR0_ : public RegisterBase<0x4e> {};
		
		static uint8_t recieve(void)
		{
			while(!is_TRX_Complete());
			return SPDR0_::Get();
		}
		static void transmit(uint8_t v)
		{
			while(!is_TRX_Complete());
			SPDR0_::Set(v);
		}
		
		//end SPI_ data register 0
		
		//SPI power management
		static void powerUp(void){Core::PRR_::ClearBit(2);}	
		static void powerDown(void){Core::PRR_::SetBit(2);}
		//end SPI power management

	}// end Serial-peripherial interface
	
	//Universal synchronous/asynchronous receiver/transmitter
	namespace USART_
	{
		//USART0 data register
		struct UDR0_ : public RegisterBase<0xc6> {};

		//USART control and status register 0A
		struct UCSR0A_ : public RegisterBase<0xc0> {};

		//USART control and status register 0B
		struct UCSR0B_ : public RegisterBase<0xc1> {};
		
		static bool is_RX_Complete(void){return UCSR0A_::GetBit(7);}
		static bool is_TX_Complete(void){return UCSR0A_::GetBit(6);}
		static void TX_Complete(void){UCSR0A_::ClearBit(6);}
		static bool is_Data_Register_Empty(void){return UCSR0A_::GetBit(5);}
		static bool is_Frame_Error(void){return UCSR0A_::GetBit(4);}
		static bool is_Data_Overrun(void){return UCSR0A_::GetBit(3);}
		static bool is_Parity_Error(void){return UCSR0A_::GetBit(2);}
		
		static uint8_t RX(void)
		{
			while (!is_RX_Complete());
			return UDR0_::Get();
		}
		
		static uint16_t RX_9bit(void)
		{
			while (!is_RX_Complete());
			uint16_t word = UDR0_::Get();
			uint8_t byte = UCSR0B_::GetBit(1);
			word |= (byte<<8);
			return word;
		}
		
		static void TX(uint8_t value)
		{
			while (!is_Data_Register_Empty());
			UDR0_::Set(value);
		}
		
		static void TX_9bit(uint16_t value)
		{
			while (!is_Data_Register_Empty());
			bool bit = value & 0b0000000100000000;
			uint8_t byte = value & 0b0000000011111111;
			UDR0_::Set(value);
			if (bit==true)UCSR0B_::SetBit(0);
			else UCSR0B_::ClearBit(0);
		}
		
		static void RX_Complete_Interrupt_Enable(void){UCSR0B_::SetBit(7);}
		static void RX_Complete_Interrupt_Disable(void){UCSR0B_::ClearBit(7);}
		
		static void TX_Complete_Interrupt_Enable(void){UCSR0B_::SetBit(6);}
		static void TX_Complete_Interrupt_Disable(void){UCSR0B_::ClearBit(6);}
		
		static void Data_reg_Empty_Interrupt_Enable(void){UCSR0B_::SetBit(5);}
		static void Data_reg_Empty_Interrupt_Disable(void){UCSR0B_::ClearBit(5);}
		
		static void RX_Enable(void){UCSR0B_::SetBit(4);}
		static void RX_Disable(void){UCSR0B_::ClearBit(4);}
		
		static void TX_Enable(void){UCSR0B_::SetBit(3);}
		static void TX_Disable(void)
		{
			while (!is_Data_Register_Empty());
			while (!is_TX_Complete());
			UCSR0B_::ClearBit(3);
		}
		
		
		//end USART control and status register 0B
		
		//USART control and status register 0C
		struct UCSR0C_ : public RegisterBase<0xc2> {};
		
		namespace Set
		{
			static void BuadRate_div_16(void){UCSR0A_::ClearBit(1);}
			static void BuadRate_div_8(void){UCSR0A_::SetBit(1);}
			static void Multiprocessor_Mode(void){UCSR0A_::SetBit(0);}
			static void noMultiprocessor_Mode(void){UCSR0A_::ClearBit(0);}
			
			static void Stop_1bit(void){UCSR0C_::ClearBit(3);}
			static void Stop_2bits(void){UCSR0C_::SetBit(3);}
			
			static void Clock_polarity0(void){UCSR0C_::ClearBit(0);}
			static void Clock_polarity1(void){UCSR0C_::SetBit(0);}
			
			namespace Character_size
			{
				static void b5_bit(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte &= ~((1<<2)|(1<<1));
					UCSR0C_::Set(config_byte);
					
					config_byte = UCSR0B_::Get();
					config_byte &= ~(1<<3);
					UCSR0B_::Set(config_byte);
				}
				
				static void b6_bit(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte &= ~(1<<2);
					config_byte |= (1<<1);
					UCSR0C_::Set(config_byte);
					
					config_byte = UCSR0B_::Get();
					config_byte &= ~(1<<3);
					UCSR0B_::Set(config_byte);
				}
				
				static void b7_bit(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte &= ~(1<<1);
					config_byte |= (1<<2);
					UCSR0C_::Set(config_byte);
					
					config_byte = UCSR0B_::Get();
					config_byte &= ~(1<<3);
					UCSR0B_::Set(config_byte);
				}
				
				static void b8_bit(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte |= (1<<2)|(1<<1);
					UCSR0C_::Set(config_byte);
					
					config_byte = UCSR0B_::Get();
					config_byte &= ~(1<<3);
					UCSR0B_::Set(config_byte);
				}
				
				static void b9_bit(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte |= ((1<<2)|(1<<1));
					UCSR0C_::Set(config_byte);
					
					config_byte = UCSR0B_::Get();
					config_byte |= (1<<3);
					UCSR0B_::Set(config_byte);
				}
			}
			
			namespace Mode
			{
				static void Asynchronous(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte &= ~((1<<7)|(1<<6));
					UCSR0C_::Set(config_byte);
				}
				
				static void Synchronous(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte &= ~(1<<7);
					config_byte |= (1<<6);
					UCSR0C_::Set(config_byte);
				}
				
				static void MasterSPI(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte |= (1<<7)|(1<<6);
					UCSR0C_::Set(config_byte);
				}
			}
			
			namespace Parity_control
			{
				static void disable(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte &= ~((1<<5)|(1<<4));
					UCSR0C_::Set(config_byte);
				}
				
				static void even(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte &= ~(1<<4);
					config_byte |= (1<<5);
					UCSR0C_::Set(config_byte);
				}
				
				static void odd(void)
				{
					uint8_t config_byte = UCSR0C_::Get();
					config_byte |= ((1<<5)|(1<<4));
					UCSR0C_::Set(config_byte);
				}
			}
		}
		
		//end USART control and status register 0C
		
		//USART buad rate 0 register low
		struct UBRR0L_ : public RegisterBase<0xc4> {};
		// end USART buad rate 0 register low
		
		//USART buad rate 0 register high
		struct UBRR0H_ : public RegisterBase<0xc5> {};
		// end USART buad rate 0 register high
		
		//USART0 power management
		static void USART0_powerUp(void){Core::PRR_::ClearBit(1);}	
		static void USART0_powerDown(void){Core::PRR_::SetBit(1);}
		//end USART0 power management
			
	}// end Universal synchronous/asynchronous receiver/transmitter
	
	// Two-wire interface
	namespace TWI_
	{
		//TWI Bit rate register
		struct TWBR_ : public RegisterBase<0xb8> {};
		// end TWI Bit rate register
		
		//TWI status register
		struct TWSR_ : public RegisterBase<0xb9> {};
		// end TWI status register
		
		//TWI(slave) address register
		struct TWAR_ : public RegisterBase<0xba> {};
		// end TWI(slave) address register
		
		//TWI data register
		struct TWDR_ : public RegisterBase<0xbb> {};
		// end TWI data register
		
		//TWI control register
		struct TWCR_ : public RegisterBase<0xbc> {};
		// end TWI control register
		
		//TWI(slave) address mask register
		struct TWAMR_ : public RegisterBase<0xbd> {};
		//end TWI(slave) address mask register

		//TWI power management
		static void powerUp(void){Core::PRR_::ClearBit(7);}
		static void powerDown(void){Core::PRR_::SetBit(7);}
		//end TWI power management		

		//Get TWI Status
		static uint8_t get_status(void)
		{
			uint8_t byte_ = TWSR_::Get();
			const uint8_t mask_ = ((1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3)|(1<<2));
			byte_ &= mask_;
			return byte_;
		}

		//Get TWI prescaler
		static uint8_t get_prescaler(void)
		{
			uint8_t byte_ = TWSR_::Get();
			const uint8_t mask_ = ((1<<1)|(1<<0));
			byte_ &= mask_;
			return byte_;
		}
		
		//Send start condition
		static void send_start(void)
		{
			uint8_t byte_ = TWCR_::Get();
			byte_ |= (1<<7)|(1<<5)|(1<<2);
			TWCR_::Set(byte_);
		}
		//

		// TWI bitrate prescaler
		namespace Prescaler
		{
			static void Set_1(void)
			{
				uint8_t byte_ = TWSR_::Get();
				byte_ &= ~((1<<1)|(1<<0));
				TWSR_::Set(byte_);
			}

			static void Set_4(void)
			{
				uint8_t byte_ = TWSR_::Get();
				byte_ &= ~(1<<1);
				byte_ |= (1<<0);
				TWSR_::Set(byte_);
			}

			static void Set_16(void)
			{
				uint8_t byte_ = TWSR_::Get();
				byte_ &= ~(1<<0);
				byte_ |= (1<<1);
				TWSR_::Set(byte_);
			}

			static void Set_64(void)
			{
				uint8_t byte_ = TWSR_::Get();
				byte_ |= (1<<1)|(1<<0);
				TWSR_::Set(byte_);
			}
		} //// end TWI bitrate prescaler

		
		
	}// end Two-wire interface
	
	//Analog comparator
	namespace AC_
	{
		/*
		//ADC control and status register B
		struct ADCSRB_ : public RegisterBase<0x7b, 8,  ReadWriteMode>{};
		// end ADC control and status register B
		*/
		
		//Analog comparator control and status register
		struct ACSR_ : public RegisterBase<0x50> {};
		// end Analog comparator control and status register
		
		//Digital input disable register 1
		struct DIDR1_ : public RegisterBase<0x7f> {};
		
		static void digital_Input_Enable(uint8_t ac_pin_number)
		{
			if ((ac_pin_number == 0) || (ac_pin_number == 1))
			{
				DIDR1_::ClearBit(ac_pin_number);
			}
			else return;
		}
		
		static void digital_Input_Disable(uint8_t ac_pin_number)
		{
			if ((ac_pin_number == 0) || (ac_pin_number == 1))
			{
				DIDR1_::SetBit(ac_pin_number);
			}
			else return;
		}
		// end Digital input disable register 1
				
	}// end Analog comparator
	
	//Analog to digital converter
	namespace ADC_
	{
		//ADC multiplexer selection register
		struct ADMUX_ : public RegisterBase<0x7c> {};
		
		namespace Reference
		{
			static void AREF(void)
			{
				uint8_t byte_ = ADMUX_::Get();
				byte_ &= ~((1<<7)|(1<<6));
				ADMUX_::Set(byte_);
			}
			
			static void AVCC(void)
			{
				uint8_t byte_ = ADMUX_::Get();
				byte_ &= ~(1<<7);
				byte_ |= (1<<6);
				ADMUX_::Set(byte_);
			}
			
			static void Internal_1V1(void)
			{
				uint8_t byte_ = ADMUX_::Get();
				byte_ |= ((1<<7)|(1<<6));
				ADMUX_::Set(byte_);
			}
		}
		
		namespace Adjust_Result
		{
			static void Left(void)	{ADMUX_::SetBit(5);}
			static void Right(void){ADMUX_::ClearBit(5);}
			static bool is_Result_Left_Adjusted(void){return ADMUX_::GetBit(5);}
		}

		static void Select_Channel_(uint8_t ch)
		{
			uint8_t byte_ = ADMUX_::Get();
			byte_ &= ~((1<<3)|(1<<2)|(1<<1)|(1<<0));
			
			if ((ch >=0) && (ch <= 7)){byte_ |= ch;}
			else {ch = 0;}
			ADMUX_::Set(byte_);
			return;
		}
		// end ADC multiplexer selection register
		
		//ADC control and status register A
		struct ADCSRA_ : public RegisterBase<0x7a> {};
		
		static void Enable(void){ADCSRA_::SetBit(7);}
		static void Disable(void){ADCSRA_::ClearBit(7);}
		static void Start_Conversion(void){ADCSRA_::SetBit(6);}
		static bool Is_Conversion_Running(void){ADCSRA_::GetBit(6);}
		static void Auto_Trigger_Enable(void){ADCSRA_::SetBit(5);}
		static void Interrupt_Enable(void){ADCSRA_::SetBit(3);}
		static void Interrupt_Disable(void){ADCSRA_::ClearBit(3);}
		
		namespace Prescaler
		{
			static void Set_2(void)
			{
				uint8_t config_byte = ADCSRA_::Get();
				config_byte &= ~((1<<2)|(1<<1)|(1<<0));
				ADCSRA_::Set(config_byte);
			}
			
			static void Set_4(void)
			{
				uint8_t config_byte = ADCSRA_::Get();
				config_byte &= ~((1<<2)|(1<<0));
				config_byte |= (1<<1);
				ADCSRA_::Set(config_byte);
			}
			
			static void Set_8(void)
			{
				uint8_t config_byte = ADCSRA_::Get();
				config_byte &= ~(1<<2);
				config_byte |= ((1<<1)|(1<<0));
				ADCSRA_::Set(config_byte);
			}
			
			static void Set_16(void)
			{
				uint8_t config_byte = ADCSRA_::Get();
				config_byte &= ~((1<<1)|(1<<0));
				config_byte |= (1<<2);
				ADCSRA_::Set(config_byte);
			}
			
			static void Set_32(void)
			{
				uint8_t config_byte = ADCSRA_::Get();
				config_byte &= ~(1<<1);
				config_byte |= ((1<<2)|(1<<0));
				ADCSRA_::Set(config_byte);
			}
			
			static void Set_64(void)
			{
				uint8_t config_byte = ADCSRA_::Get();
				config_byte &= ~(1<<0);
				config_byte |= ((1<<2)|(1<<1));
				ADCSRA_::Set(config_byte);
			}
			
			static void Set_128(void)
			{
				uint8_t config_byte = ADCSRA_::Get();
				config_byte |= ((1<<2)|(1<<1)|(1<<0));
				ADCSRA_::Set(config_byte);
			}
		}	
		// end ADC control and status register A
		
		//ADC control and status register B
		struct ADCSRB_ : public RegisterBase<0x7b> {};
		
		namespace Trigger_Source
		{
			static void Free_running(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte &= ~((1<<2)|(1<<1)|(1<<0));
				ADCSRB_::Set(config_byte);
			}
			
			static void AC_(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte &= ~((1<<2)|(1<<1));
				config_byte |= (1<<0);
				ADCSRB_::Set(config_byte);
			}
			
			static void EXINT0_(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte &= ~((1<<2)|(1<<0));
				config_byte |= (1<<1);
				ADCSRB_::Set(config_byte);
			}
			
			static void TC0_Comp_Match_A(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte &= ~(1<<2);
				config_byte |= ((1<<1)|(1<<0));
				ADCSRB_::Set(config_byte);
			}
			
			static void TC0_Overflow(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte &= ~((1<<1)|(1<<0));
				config_byte |= (1<<2);
				ADCSRB_::Set(config_byte);
			}
			
			static void TC1_Comp_Match_B(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte &= ~(1<<1);
				config_byte |= ((1<<2)|(1<<0));
				ADCSRB_::Set(config_byte);
			}
			
			static void TC1_Overflow(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte &= ~(1<<0);
				config_byte |= ((1<<2)|(1<<1));
				ADCSRB_::Set(config_byte);
			}
			
			static void TC1_Capture_Event(void)
			{
				uint8_t config_byte = ADCSRB_::Get();
				config_byte |= ((1<<2)|(1<<1)|(1<<0));
				ADCSRB_::Set(config_byte);
			}
		}
		
		// end ADC control and status register B
		
		//ADC data registers
		struct ADCL_ : public RegisterBase<0x78e> {};
		struct ADCH_ : public RegisterBase<0x79> {};
		
		static uint16_t Get_Value(void)
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
		
		// end ADC data registers
		
		//Digital input disable register 0
		struct DIDR0_ : public RegisterBase<0x7e> {};
		
		static void digital_Input_Disable(uint8_t adc_pin_number)
		{
			if ((adc_pin_number >= 0) && (adc_pin_number <= 5))
			{
				DIDR0_::SetBit(adc_pin_number);
			}
			else return;
		}
		
		static void digital_Input_Enable(uint8_t adc_pin_number)
		{
			if ((adc_pin_number >= 0) && (adc_pin_number <= 5))
			{
				DIDR0_::ClearBit(adc_pin_number);
			}
			else return;
		}
		// end Digital input disable register 0

		//ADC power management
		static void ADC_powerUp(void){Core::PRR_::ClearBit(0);}
		static void ADC_powerDown(void){Core::PRR_::SetBit(0);}
		//end ADC power management
		
	}// end Analog to digital converter
	
	//EEPROM
	namespace EEPROM_
	{
		// EEPROM address register high
		struct EEARH_ : public RegisterBase<0x42e> {};
		// end EEPROM address register high
		
		// EEPROM address register low
		struct EEARL_ : public RegisterBase<0x41> {};
		// end EEPROM address register low
		
		// EEPROM data register
		struct EEDR_ : public RegisterBase<0x40> {};
		// end EEPROM data register
		
		// EEPROM control register
		struct EECR_ : public RegisterBase<0x3f> {};
		// end EEPROM control register
				
	}// end EEPROM

	
	//Self_programming
	namespace Self_programming
	{
		//Store program memory control and status register
		struct SPMCSR_ : public RegisterBase<0x57> {};
		//end Store program memory control and status register
		
	} //end Self_programming
}
// Atmega328 MicroController Unit 

#endif //_MCU_Mega328_HPP
