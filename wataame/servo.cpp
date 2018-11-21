#include "servo.hpp"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

Servo::Servo(int id,int max_pulse,int min_pulse, int init)
{
  m_id = id;
  m_max_pulse = max_pulse;
  m_min_pulse = min_pulse;
  m_init = init;
  m_pos = init;
}

void Servo::rot_servo(int pulse){
  Serial.print(m_init);
  if(pulse < m_min_pulse){
    m_pos = m_min_pulse;
    pwm.setPWM(m_id, 0, m_min_pulse);
  }else if(pulse > m_max_pulse){
    m_pos = m_max_pulse;
    pwm.setPWM(m_id, 0, m_max_pulse);
  }else{
    m_pos = pulse;
    pwm.setPWM(m_id, 0, pulse);
  }
}

void Servo::rot_init(){
  if(m_init < m_min_pulse){
    m_pos = m_min_pulse;
    pwm.setPWM(m_id, 0, m_min_pulse);
  }else if(m_init > m_max_pulse){
    m_pos = m_max_pulse;
    pwm.setPWM(m_id, 0, m_max_pulse);
  }else{
    m_pos = m_init;
    pwm.setPWM(m_id, 0, m_init);
  }
}

int Servo::get_max_pulse(){
  return m_max_pulse;
}

int Servo::get_min_pulse(){
  return m_min_pulse;
}

int Servo::get_init(){
  return m_init;
}

int Servo::get_pos(){
  return m_pos;
}



