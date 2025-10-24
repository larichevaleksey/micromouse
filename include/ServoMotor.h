#pragma once

#include "Arduino.h"
#include "Config.h"
#include "Encoder.h"
#include "Motor.h"
#include"VelEstimator.h"

float servo_left_pi(float err_l)
{
    static float I_l = 0;
    float up_l = err_l * SERVO_KP;
    float ui_l = err_l * SERVO_KI;
    float u_l = up_l + ui_l;
    I_l +=err_l* SERVO_KI* Ts_s;

    return u_l;
}

float servo_right_pi(float err_r)
{
    static float I_r = 0;
    float up_r = err_r * SERVO_KP;
    float ui_r = err_r * SERVO_KI;
    float u_r = up_r + ui_r;
    I_r +=err_r* SERVO_KI* Ts_s;

    return u_r;
}

void servo_tick(float w0_left, float w0_right)
{
    enc_l_tick();
    ve_l_tick(enc_l_get_phi());

    float w_left = ve_l_get_w_est();
    float err_left = w0_left-w_left;
    float u_left = servo_left_pi(err_left);
   

    enc_r_tick();
    ve_r_tick(enc_r_get_phi());

    float w_right = ve_r_get_w_est();
    float err_right = w0_right-w_right;
    float u_right = servo_right_pi(err_right);
    m_drive(u_left,u_right);
    

}
