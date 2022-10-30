#ifndef DS3231_RTC_HPP
#define DS3231_RTC_HPP

#include <DS3231_Register.hpp>

typedef const unsigned char bit_number;
typedef const unsigned char bit_mask;

namespace DS3231_RTC
{  
    namespace Seconds
    {
        struct Register : public DS3231_Register<0x00>
        {
            static bit_mask sec_10_mask =  0b01110000;
            static bit_mask sec_mask =     0b00001111;
        
            static bit_number sec_10_shift = 4;
        
            static const uint8_t seconds_min = 0;
            static const uint8_t seconds_max = 59;
            static const uint8_t seconds_error = 60;
        };
        
        uint8_t get_Value(void);
        void set_Value(uint8_t seconds);
    }
    
    namespace Minutes
    {
        struct Register : public DS3231_Register<0x01>
        {
            static bit_mask mins_10_mask = 0b01110000;
            static bit_mask mins_mask =    0b00001111;

            static const uint8_t mins_10_shift = 4;

            static const uint8_t minutes_min = 0;
            static const uint8_t minutes_max = 59;
            static const uint8_t minutes_error = 60;
        };

        uint8_t get_Value(void);
        void set_Value(uint8_t minutes);
    }

    namespace Hours
    {
        struct Register : public DS3231_Register<0x02>
        {
            static bit_mask c12_24_mask =      0b01000000;
            static bit_mask am_pm_mask =       0b00100000;
            static bit_mask hours_24_mask =    0b00110000;
            static bit_mask hours_12_mask =    0b00010000;
            static bit_mask hours_mask =       0b00001111;

            static const uint8_t c12_24_shift = 6;
            static const uint8_t am_pm_shift =  5;
            static const uint8_t hours_24_shift = 3;
            static const uint8_t hours_12_shift = 3;

            static const uint8_t hours12_min = 1;
            static const uint8_t hours24_min = 0;
            static const uint8_t hours_12_max = 12;
            static const uint8_t hours_24_max = 23;
            static const uint8_t hours_error = 24;
        };

       //static bool is_pm;
        
       uint8_t get_Value(void);
       void set_Value(bool set24, bool set_pm, uint8_t hours);
       void set_24_mode(void);
       void set_12_mode(void);
    };

    struct Day : public DS3231_Register<0x03>
    {
        static bit_mask day = 0b00000111;

        static const uint8_t day_min = 1;
        static const uint8_t day_max = 7;
        static const uint8_t day_error = 8;

        uint8_t get_Value(void);
        void set_Value(uint8_t day);
    };

    struct Date : public DS3231_Register<0x04>
    {   
        static bit_mask date_10_mask = 0b00110000;
        static bit_mask date_mask =    0b00001111;

        const uint8_t date_10_shift = 4;

        static const uint8_t date_min = 1;
        static const uint8_t date_max = 31;
        static const uint8_t date_error = 32;

        uint8_t get_Value(void);
        void set_Value(uint8_t date);
    };

    struct Century_Month : public DS3231_Register<0x05>
    {
        static bit_mask month_10_mask =    0b00010000;
        static bit_mask month_mask =       0b00001111;
        static bit_mask century_mask =     0b10000000;

        static const uint8_t month_10_shift =   4;

        static const uint8_t month_min = 1;
        static const uint8_t month_max = 12;

        bool is_century22;

        uint8_t get_Value(void);
        void set_Value(bool century, uint8_t month);
    };

    struct Year : public DS3231_Register<0x06>
    {
        static bit_mask year_10_mask = 0b11110000;
        static bit_mask year_mask =    0b00001111;

        static const uint8_t year_10_shift = 4;

        static const uint8_t year_min = 0;
        static const uint8_t year_max = 99;

        uint8_t get_Value(void);
        uint8_t set_Value(uint8_t year);
    };

    struct Alarm1Seconds : private DS3231_Register<0x07>
    {
        static bit_mask a1m1_mask =    0b10000000;
        static bit_mask sec_10_mask =  0b01110000;
        static bit_mask sec_mask =     0b00001111;

        static const uint8_t sec_10_shift = 4;

        static bit_number b_a1m1 = 7;

        static const uint8_t seconds_min = 0;
        static const uint8_t seconds_max = 59;

        bool is_a1m1_set;

        uint8_t get_Value(void);
        void set_Value(bool a1m1_set, uint8_t seconds);
        void set_a1m1(void);
        void clear_a1m1(void);
    };

    struct Alarm1Minutes : public DS3231_Register<0x08>
    {
        static bit_mask a1m2_mask =    0b10000000;
        static bit_mask mins_10_mask = 0b01110000;
        static bit_mask mins_mask =    0b00001111;

        static const uint8_t mins_10_shift = 4;

        static const uint8_t minutes_min = 0;
        static const uint8_t minutes_max = 59;
  
        bool is_a1m2_set;

        uint8_t get_Value(void);
        void set_Value(bool a1m2_set, uint8_t minutes);
    };

    struct Alarm1Hours : public DS3231_Register<0x09>
    {
        static bit_mask a1m3_mask =        0b10000000;
        static bit_mask c12_24_mask =      0b01000000;
        static bit_mask am_pm_mask =       0b00100000;
        static bit_mask hours_24_mask =    0b00110000;
        static bit_mask hours_12_mask =    0b00010000;
        static bit_mask hours_mask =       0b00001111;

        static const uint8_t hours_24_shift = 3;
        static const uint8_t hours_12_shift = 3;

        static const uint8_t hours12_min = 1;
        static const uint8_t hours24_min = 0;
        static const uint8_t hours_12_max = 12;
        static const uint8_t hours_24_max = 23;

        bool is_pm;
        bool is_a1m3_set;

        uint8_t get_Value(void);
        void set_Value(bool a1m3_set, bool am_pm, uint8_t hour);
        void set_Value(bool a1m3, uint8_t hour);
    };

    struct Alarm1Day_Date : public DS3231_Register<0x0a>
    {
       static bit_mask a1m4_mask =        0b10000000;
       static bit_mask day_date_mask =    0b01000000;
       static bit_mask date_mask =        0b00111111;
       static bit_mask day_mask =         0b00001111;

       static const uint8_t day_date_shift =   6;

       static const uint8_t day_min = 1;
       static const uint8_t day_max = 7;

       static const uint8_t date_min = 1;
       static const uint8_t date_max = 31;

       public:
       
       bool is_date;
       bool is_a1m4_set;

       uint8_t get_Value(void);
       void set_Day(bool a1m4, uint8_t day);
       void set_Date(bool a1m4, uint8_t date);
    };

    struct Alarm2Minutes : public DS3231_Register<0x0b>
    {
        static bit_mask a2m2_mask =    0b10000000;
        static bit_mask mins_10_mask = 0b01110000;
        static bit_mask mins_mask =    0b00001111;

        static const uint8_t mins_10_shift = 4;

        static const uint8_t minutes_min = 0;
        static const uint8_t minutes_max = 59;

        bool is_a2m2_set;
       
        uint8_t get_Value(void);
        void set_Value(bool a2m2_set, uint8_t minutes);
    };

    struct Alarm2Hours : public DS3231_Register<0x0c>
    {
        static bit_mask a2m3_mask =        0b10000000;
        static bit_mask c12_24_mask =      0b01000000;
        static bit_mask am_pm_mask =       0b00100000;
        static bit_mask hours_24_mask =    0b00110000;
        static bit_mask hours_12_mask =    0b00010000;
        static bit_mask hours_mask =       0b00001111;

        static const uint8_t hours_24_shift = 3;
        static const uint8_t hours_12_shift = 3;

        static const uint8_t hours12_min = 1;
        static const uint8_t hours24_min = 0;
        static const uint8_t hours_12_max = 12;
        static const uint8_t hours_24_max = 23;

        static bool is_pm;
        static bool is_a2m3_set;

        static uint8_t get_Value(void);
        static void set_Day(bool a2m3, uint8_t day);
        static void set_Date(bool a2m3, uint8_t date);
    };

    struct Alarm2Day_Date : public DS3231_Register<0x0d>
    {
        static bit_mask a2m4_mask =            0b10000000;
        static bit_mask day_date_mask =         0b01000000;
        static bit_mask date_mask =             0b00111111;
        static bit_mask day_mask =              0b00001111;

        static const uint8_t day_date_shift =   6;

        static const uint8_t day_min = 1;
        static const uint8_t day_max = 7;

        static const uint8_t date_min = 1;
        static const uint8_t date_max = 31;

        static bool is_date;
        static bool is_a2m4_set;

        static uint8_t get_Value(void);
        static void set_Day(bool a2m4, uint8_t day);
        static void set_Date(bool a2m4, uint8_t date);
    };

    struct Control : public DS3231_Register<0x0e>
    {
        static bit_mask EOSC_mask =        0b10000000;
        static bit_mask BBSQW_mask =       0b01000000;
        static bit_mask CONV_mask =        0b00100000;
        static bit_mask RateSelect_mask =  0b00011000;
        static bit_mask INTCN_mask =       0b00000100;
        static bit_mask A2IE_mask =        0b00000010;
        static bit_mask A1IE_mask =        0b00000001;

        static bit_number b_EOSC =         7;
        static bit_number b_BBSQW =        6;
        static bit_number b_CONV =         5;
        static bit_number b_RS2 =          4;
        static bit_number b_RS1 =          3;
        static bit_number b_INTCN =        2;
        static bit_number b_A2IE =         1;
        static bit_number b_A1IE =         0;

        static void enable_EOSC(void);
        static void disable_EOSC(void);
        
        static void enable_BBSQW(void);
        static void disable_BBSQW(void);

        static void start_temp_CONV(void);

        static void set_SQW_Rate_1Hz(void);
        static void set_SQW_Rate_1024Hz(void);
        static void set_SQW_Rate_4096Hz(void);
        static void set_SQW_Rate_8132Hz(void);

        static void enable_INT(void);
        static void enable_SQW(void);

        static void enable_A1_INT(void);
        static void enable_A2_INT(void);

        static void disable_A1_INT(void);
        static void disable_A2_INT(void);

        static void set_config(uint8_t conf);
        static uint8_t get_config(void);
    };

    struct Control_Status : public DS3231_Register<0x0f>
    {
        static bit_mask OSF_mask =         0b10000000;
        static bit_mask EN32kHz_mask =     0b00001000;
        static bit_mask BSY_mask =         0b00000100;
        static bit_mask A2F_mask =         0b00000010;
        static bit_mask A1F_mask =         0b00000001;

        static bit_number b_OSF = 7;
        static bit_number b_EN32kHZ = 3;
        static bit_number b_BSY = 2;
        static bit_number b_A2F = 1;
        static bit_number b_A1F = 0;
        
        static void enable_32kHz(void);
        static void disable_32kHz(void);

        static bool is_BUSY(void);
        
        static bool is_Alarm1_Event(void);
        static bool is_Alarm2_Event(void);

        static void clear_Alarm1_Event(void);
        static void clear_Alarm2_Event(void);

        static void set_config(uint8_t);
        static uint8_t get_config(void);
        
    };

    struct Aging_offset : public DS3231_Register<0x10>
    {
        private:
        
        static bit_mask sign_mask =         0b10000000;
        static bit_mask data_mask =         0b01111111;

        public:

        int8_t get_Value(void);
    };

    struct MSB_of_temp : public DS3231_Register<0x11>
    {
        private:
        
        static bit_mask sign_mask =         0b10000000;
        static bit_mask data_mask =         0b01111111;

        public:

        int8_t get_Value(void);
    };

    struct LSB_of_temp : public DS3231_Register<0x12>
    {
        private:
        
        static bit_mask data_mask =         0b11000000;

        public:

        uint8_t get_Value(void);
    };

}

#endif //DS3231_RTC_BASIC_HPP