#pragma once
#include <Arduino.h>
#include <ASMR.h>
#include <DistSensors.h>
#include <Config.h>

float wf_kp_left = 0.1;
float wf_kp_right=-0.1;
float wf_kp_angle= 2.09; 
float wf_straight_tick(SensorData data)
{
    float left = data.dist_left;
    float err_l =WF_LEFT_REFERENCE-left;
    float theta_i0_l= err_l* wf_kp_left;
    
    float right = data.dist_right;
    float err_r =WF_RIGHT_REFERENCE-right;
    float theta_i0_r= err_r* wf_kp_right;
    
    float err_angle= 0-data.odom_theta;
    float theta_i0_angle = err_angle*wf_kp_angle;

    float theta_i0 = 0;
    size_t counter = 0;
    if (data.is_wall_left)
    {
        theta_i0+= theta_i0_l;
        counter++;
    }

    if (data.is_wall_right)
    {
        theta_i0+= theta_i0_r;
        counter++;
    }
    theta_i0 += theta_i0_angle;
    counter++;
    if (counter!=0)
    {
        theta_i0/=counter;
    }
    theta_i0 += theta_i0_angle;
    counter++;
    return theta_i0;
}