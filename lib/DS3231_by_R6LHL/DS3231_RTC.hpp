#ifndef DS3231_RTC_BASIC_HPP
#define DS3231_RTC_BASIC_HPP

#include <DS3231_Register.hpp>

namespace DS3231_RTC
{  
    struct  Seconds : public DS3231_Register<0x00>
    {      
        const uint8_t sec_10_mask =  0b01110000;
        const uint8_t sec_mask =     0b00001111;
        const uint8_t sec_10_shift = 4;

        const uint8_t seconds_min = 0;
        const uint8_t seconds_max = 59;
        const uint8_t seconds_error = 60;

        uint8_t get_Value(void);
    };

    struct Minutes : public DS3231_Register<0x01>
    {
        const uint8_t mins_10_mask = 0b01110000;
        const uint8_t mins_mask =    0b00001111;
        const uint8_t mins_10_shift = 4;

        const uint8_t minutes_min = 0;
        const uint8_t minutes_max = 59;
        const uint8_t minutes_error = 60;

        uint8_t get_Value(void);
    };

    struct Hours : public DS3231_Register<0x02>
    {
        const uint8_t c12_24_mask =      0b01000000;
        static const uint8_t c12_24_shift = 6;

        const uint8_t am_pm_mask =       0b00100000;
        const uint8_t am_pm_shift =  5;

        const uint8_t hours_24_mask =    0b00011000;
        const uint8_t hours_24_shift = 3;
        
        const uint8_t hours_12_mask =    0b00001000;
        const uint8_t hours_12_shift = 3;

        const uint8_t hours_mask =       0b00001111;

        const uint8_t hours12_min = 1;
        const uint8_t hours24_min = 0;
        const uint8_t hours_12_max = 12;
        const uint8_t hours_24_max = 23;
        const uint8_t hours_error = 24;

        bool is_pm;
        
        uint8_t get_Value(void);
    };

    struct Day : public DS3231_Register<0x03>
    {
        const uint8_t day = 0b00000111;

        const uint8_t day_min = 1;
        const uint8_t day_max = 7;
        const uint8_t day_error = 8;

        uint8_t get_Value(void);
    };

    struct Date : public DS3231_Register<0x04>
    {   
        const uint8_t date_10_mask = 0b00110000;
        const uint8_t date_mask =    0b00001111;

        const uint8_t date_min = 1;
        const uint8_t date_max = 31;
        const uint8_t date_error = 32;

        uint8_t get_Value(void);
    };

    struct Century_Month : public DS3231_Register<0x05>
    {
        static const uint8_t month_10_mask =    0b00010000;
        static const uint8_t month_mask =       0b00001111;
        static const uint8_t century_mask =     0b10000000;

        static const uint8_t month_min = 1;
        static const uint8_t month_max = 12;
    };

    struct Year : public DS3231_Register<0x06>
    {
        static const uint8_t year_10_mask = 0b11110000;
        static const uint8_t year_mask =    0b00001111;

        static const uint8_t year_min = 0;
        static const uint8_t year_max = 99;
    };

    struct Alarm1Seconds : public DS3231_Register<0x07>
    {
        static const uint8_t a1m1_mask =    0b10000000;
        static const uint8_t sec_10_mask =  0b01110000;
        static const uint8_t sec_mask =     0b00001111;

        static const uint8_t seconds_min = 0;
        static const uint8_t seconds_max = 59;
    };

    struct Alarm1Minutes : public DS3231_Register<0x08>
    {
        static const uint8_t a1m2_mask =    0b10000000;
        static const uint8_t mins_10_mask = 0b01110000;
        static const uint8_t mins_mask =    0b00001111;

        static const uint8_t minutes_min = 0;
        static const uint8_t minutes_max = 59;
    };

    struct Alarm1Hours : public DS3231_Register<0x09>
    {
        static const uint8_t a1m3_mask =        0b10000000;
        static const uint8_t c12_24_mask =      0b01000000;
        static const uint8_t am_pm_mask =       0b00100000;
        static const uint8_t hours_24_mask =    0b00011000;
        static const uint8_t hours_12_mask =    0b00001000;
        static const uint8_t hours_mask =       0b00001111;

        static const uint8_t hours12_min = 1;
        static const uint8_t hours24_min = 0;
        static const uint8_t hours_12_max = 12;
        static const uint8_t hours_24_max = 23;
    };

    struct Alarm1Day_Date : public DS3231_Register<0x0a>
    {
       static const uint8_t a1m4_mask =        0b10000000;
       static const uint8_t day_date_mask =    0b01000000;
       static const uint8_t date_mask =        0b00111111;
       static const uint8_t day_mask =         0b00001111;

       static const uint8_t day_min = 1;
       static const uint8_t day_max = 7;

       static const uint8_t date_min = 1;
       static const uint8_t date_max = 31;
    };

    struct Alarm2Minutes : public DS3231_Register<0x0b>
    {
        static const uint8_t a2m2_mask =    0b10000000;
        static const uint8_t mins_10_mask = 0b01110000;
        static const uint8_t mins_mask =    0b00001111;

        static const uint8_t minutes_min = 0;
        static const uint8_t minutes_max = 59;
    };

    struct Alarm2Hours : public DS3231_Register<0x0c>
    {
        static const uint8_t a2m3_mask =        0b10000000;
        static const uint8_t c12_24_mask =      0b01000000;
        static const uint8_t am_pm_mask =       0b00100000;
        static const uint8_t hours_24_mask =    0b00011000;
        static const uint8_t hours_12_mask =    0b00001000;
        static const uint8_t hours_mask =       0b00001111;

        static const uint8_t hours12_min = 1;
        static const uint8_t hours24_min = 0;
        static const uint8_t hours_12_max = 12;
        static const uint8_t hours_24_max = 23;
    };

    struct Alarm2Day_Date : public DS3231_Register<0x0d>
    {
        static const uint8_t a2m4_mask =        0b10000000;
        static const uint8_t day_date_mask =    0b01000000;
        static const uint8_t date_mask =        0b00111111;
        static const uint8_t day_mask =         0b00001111;

        static const uint8_t day_min = 1;
        static const uint8_t day_max = 7;

        static const uint8_t date_min = 1;
        static const uint8_t date_max = 31;
    };

    struct Control : public DS3231_Register<0x0e>
    {
        static const uint8_t EOSC_mask =        0b10000000;
        static const uint8_t BBSQW_mask =       0b01000000;
        static const uint8_t CONV_mask =        0b00100000;
        static const uint8_t RateSelect_mask =  0b00011000;
        static const uint8_t INTCN_mask =       0b00000100;
        static const uint8_t A2IE_mask =        0b00000010;
        static const uint8_t A1IE_mask =        0b00000001;
    };

    struct Control_Status : public DS3231_Register<0x0f>
    {
        static const uint8_t OSF_mask =         0b10000000;
        static const uint8_t EN32kHz_mask =     0b00001000;
        static const uint8_t BSY_mask =         0b00000100;
        static const uint8_t A2F_mask =         0b00000010;
        static const uint8_t A1F_mask =         0b00000001;
    };

    struct Aging_offset : public DS3231_Register<0x10>
    {
        static const uint8_t sign_mask =         0b10000000;
        static const uint8_t data_mask =         0b01111111;
    };

    struct MSB_of_temp : public DS3231_Register<0x11>
    {
        static const uint8_t sign_mask =         0b10000000;
        static const uint8_t data_mask =         0b01111111;
    };

    struct LSB_of_temp : public DS3231_Register<0x12>
    {
        static const uint8_t data_mask =         0b11000000;
    };

}

#endif //DS3231_RTC_BASIC_HPP