#include "servo.hpp"

Servo::Servo(int id,int max_pulse,int min_pulse, int pos)
{
  m_id = id;
  m_max_pulse = max_pulse;
  m_min_pulse = min_pulse;
  m_pos = pos;
}

