#include "servo.hpp"
#include "motor.hpp"

int inputchar;
unsigned long s_tim; //わたあめ作成開始時間
unsigned long m_tim; //わたあめ作成時間

Servo base_servo = Servo(0,409,196,196);
Servo grip_servo = Servo(1,409,196,300);
Motor grip_motor = Motor(0,5,6);

void setup() {
  Serial.begin(9600);
  m_tim = 10000; //わたあめ作成時間
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
  Serial.print("Initialized done\n");
}


void control(){
  while(true){
    inputchar = Serial.read();
    if(inputchar == 'e'){
      grip_motor.rot_motor(0);
      Serial.print("Emergency Stop\n");
      break;
    }else if(millis() > s_tim + m_tim){
      Serial.print("Successful completion\n");
      grip_motor.rot_motor(0);
      break;
    }
    Serial.print(" Now Control ");
    Serial.print(millis());
    Serial.print("\n");
    grip_motor.rot_motor(100);
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
