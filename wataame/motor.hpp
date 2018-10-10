#ifndef INCLUDE_GUARD_MOTOR_HPP
#define INCLUDE_GUARD_MOTOR_HPP

#include "Arduino.h"

class Motor{
  public:
    Motor(int id,int in1,int in2);
    void rot_motor(int duty);
  private:
    int m_id; // Motor ID
    int m_in1; // Motor Input pin1
    int m_in2; // Motor Input pin2
};

#endif // INCLUDE_GUARD_MOTOR_HPP

