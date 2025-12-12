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


//Robot parametres
#define ROBOT_WIDTH 0.075 //METRES
#define ROBOT_WHEEL_RADIOUS 0.0165 //metres

//Movement parametres
#define MAX_VEL 0.1 //m/s
#define MAX_ANG_VEL 5//rad/s
//maze parametres
#define CELL_WIDTH 0.18  //metres

// ASMR parameters
#define ASMR_PROG_BUFFER_SIZE 64