#ifndef MCU_Mega328_HPP
#define MCU_Mega328_HPP

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#include <RegisterBase.hpp>
#include <IO_port_basic.hpp>

typedef const uint8_t bit_number;

// Atmega328 MicroController Unit
namespace MCU
{
	namespace IO_ //IO_ports
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
	
	namespace Sleep_ //Power save modes
	{
		// Sleep mode control register
		struct SMCR_ : public RegisterBase<0x53> 
		{
			static bit_number b_SM2 = 3;
			static bit_number b_SM1 = 2;
			static bit_number b_SM0 = 1;
			static bit_number b_SE = 0;
		};
				
		namespace Mode
		{
			void Idle(void);
			void ADC_NoiseReduction(void);
			void PowerDown(void);	
			void PowerSave(void);
			void Standby(void);
			void ExtendedStandby(void);
		}

		void Enable(void);
		void Disable(void);
		void Go(void);
		bool is_Sleep_Enabled(void);
		
	} // end Sleep mode control register
	
	namespace Core //MCU core
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
		struct MCUCR_ : public RegisterBase<0x55>
		{
			static bit_number b_BOD = 	6;
			static bit_number b_BODSE = 5;
			static bit_number b_PUD = 	4;
			static bit_number b_IVSEL = 1;
			static bit_number b_IVCE = 	0;
		};
		// end MCU control register
		
		// MCU status register - indicates which event is reset occured
		// 0x01 - if power-on
		// 0x02 - if external reset
		// 0x04 - if brown-out reset
		// 0x08 - if watchdog reset
		struct MCUSR_ : public RegisterBase<0x54> 
		{
			static bit_number b_WDRF = 3;
		};
		// end MCU status register
				
		// Oscillator calibration register
		struct OSCCAL_ : public RegisterBase<0x66> {};
		// end Oscillator calibration register
		
		//Clock Precaler register
		struct CLKPR_ : public RegisterBase<0x61> {};
		// end Clock Precaler register
		
		//Power reduction register
		struct PRR_ : public RegisterBase<0x64> 
		{
			static bit_number b_PRTWI0 = 7;
			static bit_number b_PRTIM2 = 6;
			static bit_number b_PRTIM0 = 5;
			static bit_number b_PRTIM1 = 3;
			static bit_number b_PRSPI0 = 2;
			static bit_number b_PRUSART0 = 1;
			static bit_number b_PRADC = 0;
		};

		//General TC control register
		struct GTCCR_ : public RegisterBase<0x43>	{};
		//end General TC control registe	
		/*
		inline void cli(void) {asm volatile ("cli");}
		inline void sei(void) {asm volatile ("sei");}
		*/

		void powerDown_All_Peripherials(void);
		void powerUp_All_Peripherials(void);
		void BrownOut_Disable(void);
		
	}// end MCU core control registers
		
	namespace Watchdog	//Watchdog timer
	{
		/////////////////////////////////////////////////////////////////
		//Watchdog timer control register
		struct WDTCSR_ : public RegisterBase<0x60> 
		{
			static const uint8_t b_WDIF = 7;
			static const uint8_t b_WDIE = 6;
			static const uint8_t b_WDP3 = 5;
			static const uint8_t b_WDCE = 4;
			static const uint8_t b_WDE = 3;
			static const uint8_t b_WDP2 = 2;
			static const uint8_t b_WDP1 = 1;
			static const uint8_t b_WDP0 = 0;
		};
		
		//WDT interrupt flag functions
		bool is_I_Flag_Set(void);
		void set_I_Flag(void);
		void clear_I_Flag(void);
		//end WDT interrupt flag functions
		
		//WDT interrupt enable flag functions
		void Interrupt_Enable(void);
		void Interrupt_Disable(void);
		bool is_InterruptEnabled(void);
		// end WDT interrupt enable flag functions
		
		// WDT Change enable flag functions
		void Change_Enable(void);
		void Change_Disable(void);
		// end WDT Change enable flag functions
		
		// WDT System reset enable flag functions
		void System_reset_enable(void);
		void System_reset_disable(void);
		// end WDT System reset enable flag functions
		
		namespace Prescaler
		{
			//WDT prescaler functions
			void set_2048(void); 			//16ms at 5v power supply
			void set_4096(void);				//32ms at 5v power supply
			void set_8192(void);				//64ms at 5v power supply
			void set_16348(void);			//128ms at 5v power supply
			void set_32768(void);			//256ms at 5v power supply	
			void set_65536(void);			//512ms at 5v power supply
			void set_131072(void);			//1024ms at 5v power supply	
			void set_262144(void);			//2048ms at 5v power supply
			void set_524288(void);			//4096ms at 5v power supply
			void set_1048576(void);			//8192ms at 5v power supply
		}
		//end WDT prescaler functions
		namespace Mode
		{
			//WDT Configurations if WDTON fuse bit is not set
			 void stop(void);
			 void interrupt(void);
			 void SystemReset(void);
			 void Interrupt_And_SystemReset(void);
		}
		//end WDT Configurations
		// end Watchdog timer control registerr
	}	
	
	namespace EXINT_ //external interrupts
	{
		//External interrupt control register A
		struct EICRA_ : public RegisterBase<0x69> 
		{
			static bit_number b_ISC00 = 0;
			static bit_number b_ISC01 = 1;
			static bit_number b_ISC10 = 2;
			static bit_number b_ISC11 = 3;
		};
		// end External interrupt control register A
		
		//External interrupt mask register
		struct EIMSK_ : public RegisterBase<0x3d> 
		{
			static bit_number b_INT0 = 0;
			static bit_number b_INT1 = 1;
		};
		// end External interrupt mask register
		
		//External interrupt flag register
		struct EIFR_ : public RegisterBase<0x3c> 
		{
			static bit_number b_INTF0 = 0;
			static bit_number b_INTF1 = 1;
		};
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
		
		namespace INT0_Mode
		{
			void low_level(void);
			void any_change(void);
			void falling_edge(void);
			void rising_edge(void);
		}

		namespace INT1_Mode
		{
			void low_level(void);
			void any_change(void);
			void falling_edge(void);
			void rising_edge(void);
		}
		
		void INT0_Enable(void);
		void INT0_Disable(void);

		void INT1_Enable(void);
		void INT1_Disable(void);

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
		void powerUp(void);
		void powerDown(void);
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
		 void powerUp(void);
		 void powerDown(void);
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
		void powerUp(void);
		void powerDown(void);
		//end Timer2 power management
			
		void TimerStop(void);

		namespace Prescaler
		{
			void reset(void);
			void set_1(void);
			void set_8(void);
			void set_32(void);
			void set_64(void);
			void set_128(void);
			void set_256(void);
			void set_1024(void);
		}
		
		namespace Interrupt_source
		{
			void Overflow_Enable(void);
			void Overflow_Disable(void);
		}
			
	}// end Timer-counter 2 8bit
	
	namespace SPI_ //Serial-peripherial interface
	{
		//SPI_ control register 0
		struct SPCR0_ : public RegisterBase<0x4c> {};
		//SPI_ status register 0
		struct SPSR0_ : public RegisterBase<0x4d> {};

		 bool is_TRX_Complete(void);
		 bool is_Data_Collision(void);
				
		 void Interrupt_Enable(void);
		 void Interrupt_Disable(void);
		
		 void Enable(void);
		 void Disable(void);
		
		 void Set_As_Master(void);
		 void Set_As_Slave(void);
						
		namespace Data_Order
		{
			 void MSB_first(void);
			 void LSB_first(void);
		}
		
		namespace Mode
		{
			void set_0(void);		
			void set_1(void);
			void set_2(void);			
			void set_3(void);
		}
		
		namespace Rate
		{
			void F_div_2(void);
			void F_div_4(void);
			void F_div_8(void);		
			void F_div_16(void);			
			void F_div_32(void);		
			void F_div_32x2(void);
			void F_div_64(void);
			void F_div_128(void);
		}
		//end SPI_ control register 0
		
		//SPI_ data register 0
		struct SPDR0_ : public RegisterBase<0x4e> {};
		
		 uint8_t recieve(void);
		 void transmit(uint8_t v);
		//end SPI_ data register 0
		
		//SPI power management
		 void powerUp(void);
		 void powerDown(void);
		//end SPI power management

	}// end Serial-peripherial interface
	
	namespace USART_ //Universal synchronous/asynchronous receiver/transmitter
	{
		//USART0 data register
		struct UDR0_ : public RegisterBase<0xc6> {};

		//USART control and status register 0A
		struct UCSR0A_ : public RegisterBase<0xc0> {};

		//USART control and status register 0B
		struct UCSR0B_ : public RegisterBase<0xc1> {};
		
		bool is_RX_Complete(void);
		bool is_TX_Complete(void);
		void TX_Complete(void);
		bool is_Data_Register_Empty(void);
		bool is_Frame_Error(void);
		bool is_Data_Overrun(void);
		bool is_Parity_Error(void);
		
		uint8_t RX(void);	
		uint16_t RX_9bit(void);
		void TX(uint8_t value);
		void TX_9bit(uint16_t value);

		namespace Interrupts
		{
			void RX_Complete_Enable(void);
			void RX_Complete_Disable(void);
		
			void TX_Complete_Enable(void);
			void TX_Complete_Disable(void);
		
			void Data_reg_Empty_Enable(void);
			void Data_reg_Empty_Disable(void);
		}

		void RX_Enable(void);
		void RX_Disable(void);
		
		void TX_Enable(void);
		void TX_Disable(void);
		//end USART control and status register 0B

		//USART control and status register 0C
		struct UCSR0C_ : public RegisterBase<0xc2> {};
		
		namespace Set
		{
			 void BaudRate(uint32_t fosc, uint16_t baudrate);
			 void BuadRate_div_16(void);
			 void BuadRate_div_8(void);
			 void Multiprocessor_Mode(void);
			 void noMultiprocessor_Mode(void);
			
			 void Stop_1bit(void);
			 void Stop_2bits(void);
			
			 void Clock_polarity0(void);
			 void Clock_polarity1(void);
			
			namespace Character_size
			{
				void b5_bit(void);
				void b6_bit(void);
				void b7_bit(void);
				void b8_bit(void);
				void b9_bit(void);
			}
			
			namespace Mode
			{
				void Asynchronous(void);
				void Synchronous(void);
				void MasterSPI(void);
				uint8_t get(void);
			}
			
			namespace Parity_control
			{
				void disable(void);
				void even(void);
				void odd(void);
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
		void powerUp(void);
		void powerDown(void);
		//end USART0 power management
			
	}// end Universal synchronous/asynchronous receiver/transmitter
	
	namespace TWI_ // Two-wire interface
	{	
		//TWI Bit rate register
		struct TWBR_ : public RegisterBase<0xb8>{};
		// end TWI Bit rate register
		
		//TWI status register
		struct TWSR_ : public RegisterBase<0xb9> 
		{
			static const uint8_t b_TWS4 = 7;
			static const uint8_t b_TWS3 = 6;
			static const uint8_t b_TWS2 = 5;
			static const uint8_t b_TWS1 = 4;
			static const uint8_t b_TWS0 = 3;
			static const uint8_t b_TWPS1 = 1;
			static const uint8_t b_TWPS0 = 0;

			static const uint8_t status_mask = 0b11111100;

			//Master transmitter mode
			static const uint8_t START_t = 				0x08;
			static const uint8_t REP_START_t = 			0x10;
			static const uint8_t MT_SLAW_t_ACK_r = 		0x18;
			static const uint8_t MT_SLAW_t_NACK_r = 	0x20;
			static const uint8_t MT_DATA_t_ACK_r = 		0x28;
			static const uint8_t MT_DATA_t_NACK_r = 	0x30;
			static const uint8_t MT_ARBIT_lost = 		0x38;
			//Master receiver mode
			static const uint8_t MR_SLAR_t_ACK_r = 		0x40;
			static const uint8_t MR_SLAR_t_NACK_r = 	0x48;
			static const uint8_t MR_DATA_r_ACK_t = 		0x50;
			static const uint8_t MR_DATA_r_NACK_t = 	0x58;
			//Slave transmitter mode
			static const uint8_t ST_Own_SLAR_r_ACK_t = 				0xa8;
			static const uint8_t ST_ARBIT_Lost_Own_SLAR_r_ACK_t = 	0xb0;
			static const uint8_t ST_DATA_t_ACK_r = 					0xb8;
			static const uint8_t ST_DATA_t_NACK_r = 				0xc0;
			static const uint8_t ST_Last_DATA_t_ACK_r = 			0xc8;
			//Slave receiver mode
			static const uint8_t SR_OwnSLAW_r_ACK_t = 					0x60;
			static const uint8_t SR_ARBIT_Lost_Own_SLAW_r_ACK_t = 		0x68;
			static const uint8_t SR_General_call_r_ACK_t = 				0x70;
			static const uint8_t SR_ARBIT_Lost_General_call_r_ACK_t =	0x78;
			static const uint8_t SR_PrevAdd_own_SLAW_Data_r_ACK_t =		0x80;
			static const uint8_t SR_PrevAdd_own_SLAW_Data_r_NACK_t = 	0x88;
			static const uint8_t SR_PrevAdd_Gen_call_DATA_r_ACK_t = 	0x90;
			static const uint8_t SR_PrevAdd_Gen_call_DATA_r_NACK_t = 	0x98;
			static const uint8_t STOP_or_REP_START_r = 					0xa0;
		};
		// end TWI status register
		
		//TWI(slave) address register
		struct TWAR_ : public RegisterBase<0xba> 
		{
			static const uint8_t slave_address_mask = 		0b11111110;
			static const uint8_t general_call_flag_mask = 	0b00000001;

			static const uint8_t b_TWGCE = 0;
		};
		// end TWI(slave) address register

		//TWI data register
		struct TWDR_ : public RegisterBase<0xbb> {};
		// end TWI data register
		
		//TWI control register
		struct TWCR_ : public RegisterBase<0xbc> 
		{
			static const uint8_t b_TWINT = 7;
			static const uint8_t b_TWEA = 6;
			static const uint8_t b_TWSTA = 5;
			static const uint8_t b_TWSTO = 4;
			static const uint8_t b_TWWC = 3;
			static const uint8_t b_TWEN = 2;
			static const uint8_t b_TWIE = 0;
		};
		// end TWI control register
		
		//TWI(slave) address mask register
		struct TWAMR_ : public RegisterBase<0xbd> 
		{
			static const uint8_t slave_address_mask = 0b11111110;
		};
		
		//TWI power management
		 void powerUp(void);
		 void powerDown(void);
		//end TWI power management		

		//Get TWI Status
		 uint8_t get_status(void);

		// TWI bitrate prescaler
		namespace Prescaler
		{
			void Set_1(void);
			void Set_4(void);	
			void Set_16(void);
			void Set_64(void);
		} // end TWI bitrate prescaler
		
		//Get TWI prescaler
		uint8_t get_prescaler(void);

		void set_ACK_enabled(void);
		void set_ACK_disabled(void);

		void send_Start(void);
		void send_SLA_W(uint8_t slave_address);
		void send_SLA_R(uint8_t slave_address);
		void send_Data_byte(uint8_t data_byte);
		void send_Stop(void);

		void send_Reg_Byte(uint8_t dev_add, uint8_t reg_addr, uint8_t data_byte);

		uint8_t read_Reg_Byte(uint8_t dev_add, uint8_t reg_add);
	}// end Two-wire interface
	
	namespace AC_ //Analog comparator
	{
		/*
		//ADC control and status register B
		struct ADCSRB_ : public RegisterBase<0x7b, 8,  ReadWriteMode>{};
		// end ADC control and status register B
		*/
		
		//Analog comparator control and status register
		struct ACSR_ : public RegisterBase<0x50> 
		{
			static const uint8_t ACD_= 7;
		};
		// end Analog comparator control and status register
		
		//Digital input disable register 1
		struct DIDR1_ : public RegisterBase<0x7f> {};
		
	 	void digital_Input_Enable(uint8_t ac_pin_number);
		void digital_Input_Disable(uint8_t ac_pin_number);
		// end Digital input disable register 1

		void powerDown(void);
		void powerUp(void);
				
	}// end Analog comparator
	
	namespace ADC_ //Analog to digital converter
	{
		//ADC multiplexer selection register
		struct ADMUX_ : public RegisterBase<0x7c> {};
		
		namespace Reference
		{
			void AREF(void);
			void AVCC(void);
			void Internal_1V1(void);
		}
		
		namespace Adjust_Result
		{
			 void Left(void);
			 void Right(void);
			 bool is_Result_Left_Adjusted(void);
		}

		void Select_Channel_(uint8_t ch);
		// end ADC multiplexer selection register
		
		//ADC control and status register A
		struct ADCSRA_ : public RegisterBase<0x7a> {};
		
		 void Enable(void);
		 void Disable(void);
		 void Start_Conversion(void);
		 bool Is_Conversion_Running(void);
		 void Auto_Trigger_Enable(void);
		 void Interrupt_Enable(void);
		 void Interrupt_Disable(void);
		
		namespace Prescaler
		{
			void Set_2(void);
			void Set_4(void);
			void Set_8(void);
			void Set_16(void);
			void Set_32(void);
			void Set_64(void);
			void Set_128(void);
		}	
		// end ADC control and status register A
		
		//ADC control and status register B
		struct ADCSRB_ : public RegisterBase<0x7b> {};
		
		namespace Trigger_Source
		{
			void Free_running(void);
			void AC_(void);
			void EXINT0_(void);
			void TC0_Comp_Match_A(void);
			void TC0_Overflow(void);
			void TC1_Comp_Match_B(void);
			void TC1_Overflow(void);
			void TC1_Capture_Event(void);
		}
		// end ADC control and status register B
		
		//ADC data registers
		struct ADCL_ : public RegisterBase<0x78e> {};
		struct ADCH_ : public RegisterBase<0x79> {};
		
		 uint16_t Get_Value(void);
		// end ADC data registers
		
		//Digital input disable register 0
		struct DIDR0_ : public RegisterBase<0x7e> {};
		
		void digital_Input_Disable(uint8_t adc_pin_number);
		void digital_Input_Enable(uint8_t adc_pin_number);
		// end Digital input disable register 0

		//ADC power management
		void powerUp(void);
		void powerDown(void);
		//end ADC power management
	}// end Analog to digital converter
	
	namespace EEPROM_ //EEPROM
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

	namespace Self_programming //Self_programming
	{
		//Store program memory control and status register
		struct SPMCSR_ : public RegisterBase<0x57> {};
		//end Store program memory control and status register
		
	} //end Self_programming
};
// Atmega328 MicroController Unit 

#endif //_MCU_Mega328_HPP
