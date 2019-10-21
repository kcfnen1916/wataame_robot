#include "motor.hpp"

Motor::Motor(int id,int in1,int in2)
{
  m_id = id;
  m_in1 = in1;
  m_in2 = in2;
}

void Motor::rot_motor(int duty){
  if (duty == 0){       //BREAK
      analogWrite(m_in1,255);
      analogWrite(m_in2,255);
    }else if (duty > 0){       //CCW
      analogWrite(m_in1,duty);
      analogWrite(m_in2,0);
    }else if (duty < 0){       //CW
      analogWrite(m_in1,0);
      analogWrite(m_in2,duty);
    }
}
