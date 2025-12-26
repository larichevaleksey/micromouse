#pragma once

#include <Arduino.h>

//Time
#define Ts_us 2000
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
#define MAX_VEL 0.2 //m/s
#define MAX_ANG_VEL 7//rad/s
#define TURN_RADIUS_SHORTEST 0.09 //metres
#define TURN_RADIUS_EXPLORE 0.05  // [m]

//maze parametres
#define CELL_WIDTH 0.18  //metres

// ASMR parameters
#define ASMR_PROG_BUFFER_SIZE 64



/*
1.0.x.x.x.x.x.x
    ^^^ ^ ^^^ |- Направление поворота
     |  |  |  |- 0: LEFT
     |  |  |  `- 1: RIGHT
     |  |  |
     |  |  |- Угол поворота
     |  |  |- 00: 45deg
     |  |  |- 01: 90deg
     |  |  |- 10: 135deg
     |  |  `- 11: 180deg
     |  |
     |  |- Откуда приходим в поворот (из прямой или диагонали)
     |  |- 0: STRAIGHT
     |  `- 1: DIAG
     |
     |- Вид поворота 90
     |- 00: Shortest
     |- 01: Explore
     `- 10: In-place
*/
