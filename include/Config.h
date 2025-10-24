#pragma once

#include <Arduino.h>

//Time
#define Ts_us 5000
#define Ts_s (Ts_us/1000000.0)

//Vel stimator
#define VE_LPF_T 0.005

// servo
#define SERVO_KP 3.0
#define SERVO_KI 20.0