#include <Arduino.h>
#include <argviz.h>

#include "VoltageSensor.h"
#include <Motor.h>
#include <Encoder.h>
#include <Config.h>
#include <VelEstimator.h>
#include <ServoMotor.h>
#include <Mixer.h>
#include <Screens.h>
#include <Odometer.h>
/**
Set

```
monitor_raw = true
monitor_speed = 115200
```

in platformio.ini to get proper output
 */

void setup()
{
  Serial.begin(115200);
  m_init();
  vs_init();
  enc_l_init();
  enc_r_init();

  interrupts();

  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_registerScreen(1, encoders);
  argviz_registerScreen(2, servos);
  argviz_registerScreen(3, mixer);
  argviz_start();
}

void loop()
{
  //timer
  static uint32_t timer = micros();
  while (micros()-timer <Ts_us);
  timer = micros();

  //sense
  odom_tick();
  //plan

  //act
  // m_drive(left_u, right_u);
  // servo_tick(left_w0, right_w0);
  mixer_tick(v_0, theta_i0);
}