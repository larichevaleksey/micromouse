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
#include "ASMR.h"
  

void fwd ()
{
  odom_reset();
  while(true)
  {
   //timer
  static uint32_t timer = micros();
  while (micros()-timer <Ts_us);
  timer = micros();

  //sense
  odom_tick();

  //plan
  v_0 =MAX_VEL;
  theta_i0 = 0;
  if(odom_get_S() > CELL_WIDTH)
  {
    return;
  }
  //act
  // m_drive(left_u, right_u);
  // servo_tick(left_w0, right_w0);
  mixer_tick(v_0, theta_i0);
  }
}

void left()
{
  odom_reset();
  while(true)
  {
    //timer
  static uint32_t timer = micros();
  while (micros()-timer <Ts_us);
  timer = micros();

  //sense
  odom_tick();

  //plan
  v_0 =0;
  theta_i0 = MAX_ANG_VEL  ;
  if(odom_get_theta()>M_PI/2)
  {
    return;
  }
  //act
  // m_drive(left_u, right_u);
  // servo_tick(left_w0, right_w0);
  mixer_tick(v_0, theta_i0);
  }
}

void stop()
{
  odom_reset();
  while (true)
  {
    //timer
  static uint32_t timer = micros();
  while (micros()-timer <Ts_us);
  timer = micros();

  //sense
  odom_tick();

  //plan
  v_0 =0;
  theta_i0 = 0;

  //act
  // m_drive(left_u, right_u);
  // servo_tick(left_w0, right_w0);
  mixer_tick(v_0, theta_i0);
}
  }
void setup()
{
  Serial.begin(115200);
  m_init();
  vs_init();
  enc_l_init();
  enc_r_init();
  asmr_init();

  interrupts();

  argviz_init(Serial);
  argviz_registerScreen(0, volts);
  argviz_registerScreen(1, encoders);
  argviz_registerScreen(2, servos);
  argviz_registerScreen(3, mixer);
  argviz_registerScreen(4, asmr);
  argviz_start();//
  // fwd();
  // left();
  // fwd();
  // left();
  // fwd();
  // left();
  // fwd();
  // left();
  // stop();
}


void loop()
{
  //timer
  static uint32_t timer = micros();
  while (micros()-timer <Ts_us);
  timer = micros();

  //sense
  //odom_tick();


  //plan

  //act
  // m_drive(left_u, right_u);
  // servo_tick(left_w0, right_w0);
  // mixer_tick(v_0, theta_i0);
  asmr_tick();
}