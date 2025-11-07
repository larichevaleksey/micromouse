#pragma once

#include <Arduino.h>
#include "Config.h"

#define ENC_LEFT_CLK_A_PIN 2
#define ENC_LEFT_B_PIN 4

#define ENC_LEFT_DIR -1  //{-1;1}

int8_t enc_l_tt[4][4];//Transition table

#define ENC_TICK_TO_RAD (2* M_PI/(48*30))
float enc_l_phi = 0;
float enc_r_phi = 0;

#define ENC_RIGHT_CLK_A_PIN 3 
#define ENC_RIGHT_B_PIN 5
#define ENC_RIGHT_DIR 1
int8_t enc_r_tt[4][4];

volatile int enc_l_counter = 0;
volatile int enc_r_counter = 0;

void enc_l_interrupt()
{
    int lB = digitalRead(ENC_LEFT_B_PIN);
    int lCA = digitalRead(ENC_LEFT_CLK_A_PIN);
    int lA = lCA ^ lB;
    int lAB = lA << 1|lB;
    
    static int old_lAB = lAB;
    enc_l_counter += enc_l_tt[old_lAB][lAB];
    old_lAB = lAB;
}

void enc_r_interrupt()
{
    int rB = digitalRead(ENC_RIGHT_B_PIN);
    int rCA = digitalRead(ENC_RIGHT_CLK_A_PIN);
    int rA = rCA ^ rB;
    int rAB = rA << 1|rB;
    
    static int old_rAB = rAB;
    enc_r_counter += enc_r_tt[old_rAB][rAB];
    old_rAB = rAB;
}

void enc_l_init()
{


    pinMode(ENC_LEFT_B_PIN,INPUT);
    pinMode(ENC_LEFT_B_PIN,INPUT);

    enc_l_tt[0b00][0b01] = ENC_LEFT_DIR;
    enc_l_tt[0b01][0b11] = ENC_LEFT_DIR;
    enc_l_tt[0b11][0b10] = ENC_LEFT_DIR;
    enc_l_tt[0b10][0b00] = ENC_LEFT_DIR;

    enc_l_tt[0b00][0b10] = -ENC_LEFT_DIR;
    enc_l_tt[0b10][0b11] = -ENC_LEFT_DIR;
    enc_l_tt[0b11][0b01] = -ENC_LEFT_DIR;
    enc_l_tt[0b01][0b00] = -ENC_LEFT_DIR;

    attachInterrupt(
        digitalPinToInterrupt(ENC_LEFT_CLK_A_PIN),
        enc_l_interrupt,
        CHANGE
    );

}
void enc_r_init()
{


    pinMode(ENC_RIGHT_B_PIN,INPUT);
    pinMode(ENC_RIGHT_B_PIN,INPUT);

    enc_r_tt[0b00][0b01] = ENC_RIGHT_DIR;
    enc_r_tt[0b01][0b11] = ENC_RIGHT_DIR;
    enc_r_tt[0b11][0b10] = ENC_RIGHT_DIR;
    enc_r_tt[0b10][0b00] = ENC_RIGHT_DIR;

    enc_r_tt[0b00][0b10] = -ENC_RIGHT_DIR;
    enc_r_tt[0b10][0b11] = -ENC_RIGHT_DIR;
    enc_r_tt[0b11][0b01] = -ENC_RIGHT_DIR;
    enc_r_tt[0b01][0b00] = -ENC_RIGHT_DIR;

    attachInterrupt(
        digitalPinToInterrupt(ENC_RIGHT_CLK_A_PIN),
        enc_r_interrupt,
        CHANGE
    );

}
int enc_l_get_ticks()
{
    noInterrupts();
    int l_ret = enc_l_counter;
    interrupts();
    return l_ret;
    
}
int enc_r_get_ticks()
{
    noInterrupts();
    int r_ret = enc_r_counter;
    interrupts();
    return r_ret;
    
}
void enc_l_tick()
{
    noInterrupts();
    int l_counter = enc_l_counter;
    enc_l_counter = 0;
    interrupts();

    enc_l_phi += ENC_TICK_TO_RAD * l_counter;

}
float enc_l_get_phi()
{
    return enc_l_phi;
}
void enc_r_tick()
{
    noInterrupts();
    int r_counter = enc_r_counter;
    enc_r_counter = 0;
    interrupts();

    enc_r_phi += ENC_TICK_TO_RAD * r_counter;

}
float enc_r_get_phi()
{
    return enc_r_phi;
}