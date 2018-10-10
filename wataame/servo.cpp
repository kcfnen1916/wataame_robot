#include "servo.hpp"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

Servo::Servo(int id,int max_pulse,int min_pulse, int pos)
{
  m_id = id;
  m_max_pulse = max_pulse;
  m_min_pulse = min_pulse;
  m_pos = pos;
}

void Servo::rot_servo(int pulse){
  Serial.print(m_pos);
  if(pulse < m_pos){
    m_pos--;
    if(m_pos >= m_min_pulse){
      pwm.setPWM(m_id, 0, m_pos);
    }
  }else if(pulse > m_pos){
    m_pos++;
    if(m_pos <= m_max_pulse){
      pwm.setPWM(m_id, 0, m_pos);
    }
  }else{
    m_pos = pulse;
  }
}
