#pragma once
#include <Arduino.h>
#include <Config.h>
float ve_l_w_est = 0;
float ve_l_w_est_f =0;

float ve_r_w_est = 0;
float ve_r_w_est_f = 0;

float dlphi = 0;
float drphi = 0;

void ve_init()
{
}

void ve_l_tick(float lphi)
{
    static  float lphi_old = lphi;
    float dlphi = lphi -lphi_old;
    ve_l_w_est = dlphi/Ts_s;
    lphi_old = lphi;


    static float lI =0;
    float le = ve_l_w_est - ve_l_w_est_f;
    float ls = le / VE_LPF_T ;
    lI += ls*Ts_s;
    ve_l_w_est_f =lI;
}
float ve_l_get_w_est()
{
    return ve_l_w_est;
}
float ve_l_get_w_est_f()
{
    return ve_l_w_est_f;
}


void ve_r_tick(float rphi)
{
    static  float rphi_old = rphi;
    float drphi = rphi -rphi_old;
    ve_r_w_est = drphi/Ts_s;
    rphi_old = rphi;


    static float rI =0;
    float re = ve_r_w_est - ve_r_w_est_f;
    float rs = re / VE_LPF_T ;
    rI += rs*Ts_s;
    ve_r_w_est_f =rI;
}
float ve_r_get_w_est()
{
    return ve_r_w_est;
}
float ve_r_get_w_est_f()
{
    return ve_r_w_est_f;
}