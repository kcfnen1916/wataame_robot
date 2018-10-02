#ifndef INCLUDE_GUARD_SERVO_HPP
#define INCLUDE_GUARD_SERVO_HPP





class Servo{
  public:
    Servo(int id,int max_pulse,int min_pulse,int pos);
    void rot_servo(int pulse);
  private:
    int m_id;
    int m_max_pulse;
    int m_min_pulse;
    int m_pos;
};

#endif // INCLUDE_GUARD_SERVO_HPP

