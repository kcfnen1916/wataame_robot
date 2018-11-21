#ifndef INCLUDE_GUARD_SERVO_HPP
#define INCLUDE_GUARD_SERVO_HPP
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

extern Adafruit_PWMServoDriver pwm;

class Servo{
  public:
    Servo(int id,int max_pulse,int min_pulse,int init);
    void rot_servo(int pulse);
    void rot_init();
    int get_max_pulse();
    int get_min_pulse();
    int get_init();
    int get_pos();
  private:
    int m_id; // Servo ID
    int m_max_pulse; // Max pulse
    int m_min_pulse; // Min pulse
    int m_init; // init position
    int m_pos; // now position
};

#endif // INCLUDE_GUARD_SERVO_HPP

