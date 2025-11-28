#pragma once
#include <stdint.h>
struct ASMR_Entry
{
    union
    {
        uint8_t : 2;
        struct 
        {
            uint8_t cyc_type : 2;
            uint8_t stidle_mode : 6;
        }stidle;

        struct
        {
            uint8_t cyc_type : 2;
            uint8_t forw_mode : 1;
            uint8_t forwdist : 5;
        }forw;
        struct
        {
            uint8_t cyc_type : 2;
            uint8_t turn_mode: 2;
            uint8_t turn_source : 1;
            uint8_t turn_angle : 2;
            uint8_tturn_dif :1;
        }turn;
    };
};