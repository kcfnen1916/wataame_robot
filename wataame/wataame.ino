#include "servo.hpp"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int DC_IN1 = 5;
int DC_IN2 = 6;
int inputchar;
unsigned long s_tim; //わたあめ作成開始時間
unsigned long m_tim; //わたあめ作成時間

Servo base_servo = Servo(0,409,196,196);
Servo grip_servo = Servo(1,409,196,300);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  m_tim = 10000; //わたあめ作成時間
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
  Serial.print("Initialized done\n");
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

void dc_motor(int value = 0){
    if (value == 0){       //BREAK
      analogWrite(DC_IN1,255);
      analogWrite(DC_IN2,255);
    }else if (value > 0){       //CCW
      analogWrite(DC_IN1,value);
      analogWrite(DC_IN2,0);
    }else if (value < 0){       //CW
      analogWrite(DC_IN1,0);
      analogWrite(DC_IN2,value);
    }
}

void control(){
  while(true){
    inputchar = Serial.read();
    if(inputchar == 'e'){
      dc_motor(0);
      Serial.print("Emergency Stop\n");
      break;
    }else if(millis() > s_tim + m_tim){
      Serial.print("Successful completion\n");
      dc_motor(0);
      break;
    }
    Serial.print(" Now Control ");
    Serial.print(millis());
    Serial.print("\n");
    dc_motor(100);
    base_servo.rot_servo(408);
    for (int i = 9;i>0;i--){
      if (millis() - s_tim > i * 1000){
        if (i % 2 == 0){
          Serial.print("310\n");
          grip_servo.rot_servo(310);
          break;
        }else{
          Serial.print("290\n");
          grip_servo.rot_servo(290);
          break;
        }
      }
    }
  }
}

void loop() {
  inputchar = Serial.read();
  if(inputchar != -1 ){
    switch(inputchar){
      case 's':
        Serial.print("Start\n");
        s_tim = millis();
        control();
        break;
      case 't':
        Serial.print("Stop\n");
        break;
      case 'v':
        Serial.print("Servo test\n");
        break;
    }
  } else {
  }
}
