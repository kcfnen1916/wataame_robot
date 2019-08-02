#include "servo.hpp"
#include "motor.hpp"

int input;
unsigned long s_tim; //わたあめ作成開始時間
unsigned long m_tim; //わたあめ作成時間

int gtf = 1;

int trig = 9; // 出力ピン
int echo = 8; // 入力ピン

int pick_flag = 0;

Servo lift_servo = Servo(0,440,320,330);
Servo grip_servo = Servo(2,250,196,205);
Motor grip_motor = Motor(0,5,6);
Motor base_motor = Motor(1,10,11);

void setup() {
  Serial.begin(115200);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  m_tim = 100000; //わたあめ作成時間
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
  lift_servo.rot_init();
  grip_servo.rot_init();
  Serial.print("Initialized done\n");
}

float get_dist(){
  delay(100);
  digitalWrite(trig,LOW);
  delayMicroseconds(1);
  // 超音波を出力
  digitalWrite(trig,HIGH);
  delayMicroseconds(11);
  // 超音波を出力終了
  digitalWrite(trig,LOW);
  // 出力した超音波が返って来る時間を計測
  int t = pulseIn(echo,HIGH);
  // 計測した時間と音速から反射物までの距離を計算
  float distance = t*0.17;
  // 計算結果をシリアル通信で出力
  return distance;
}

void base_move(float dest){
  float dist = get_dist();
//  Serial.print(dist);
//  Serial.print("\n");
  int ds_tim = millis();
  if (dist > dest){
    while (true) {
      dist = get_dist();
      if (millis() - ds_tim  > 300){
        base_motor.rot_motor(0);
        break;
      }
      base_motor.rot_motor(-20);
    }
  }else{
    while (true) {
      dist = get_dist();
      if (millis() - ds_tim  > 500){
        base_motor.rot_motor(0);
        break;
      }
      base_motor.rot_motor(60);
    }
  }
}

void base_init(){
  base_move(40.0);
}

void control(){
  int ls_pul = 330;
  int gs_pul = 205;
  pick_flag = 0;
  while(true){
    input = Serial.read();
    if (input != -1){
      if(input == 'o'){
        grip_motor.rot_motor(0);
        base_motor.rot_motor(0);
        Serial.print("Emergency Stop\n");
        break;
      }else if(input == 'u'){
        grip_motor.rot_motor(0);
        base_motor.rot_motor(0);
        lift_servo.rot_servo(360);
        grip_servo.rot_servo(210);
        Serial.print("Successful completion\n");
        break;
      }else if (input == 't'){
        Serial.print("pick up\n");
        if (pick_flag == 0){
          pick_flag = 1;
        }else{
          pick_flag = 0;
        }
      }else if (input == 'e'){
        Serial.print("Grip up\n");
        gs_pul = grip_servo.get_pos() + 2;
      }else if (input == 'f'){
        Serial.print("Grip down\n");
        gs_pul = grip_servo.get_pos() - 2;
      }else if (input == 'g'){
        Serial.print("Lift up\n");
        ls_pul = lift_servo.get_pos() + 2;
      }else if (input == 'h'){
        Serial.print("Lift down\n");
        ls_pul = lift_servo.get_pos() - 2;
      }else if (input == 'i'){
        Serial.print("Base up\n");
        base_move(get_dist() + 25);
      }else if (input == 'j'){
        Serial.print("Base down\n");
        base_move(get_dist() - 25);
      }
    }else{
      if (pick_flag == 0){
        ls_pul = lift_servo.get_init(); // lift_servo
        gs_pul = grip_servo.get_init(); // grip_servo
      }else{
        ls_pul = lift_servo.get_pos() + (lift_servo.get_max_pulse() - lift_servo.get_max_pulse()) * (millis() - s_tim) / m_tim; // lift_servo
//        if (((millis() - s_tim) / 1000 ) % 2 == 0){ // grip_servo
//          gs_pul = grip_servo.get_init() + 2;
//        }else{
//          gs_pul = grip_servo.get_init();
//        }
      }
    }

    grip_motor.rot_motor(100);
    lift_servo.rot_servo(ls_pul);
    grip_servo.rot_servo(gs_pul);
    Serial.print("Now Control ");
    Serial.print(millis());
    Serial.print(" ");
    Serial.print(ls_pul);
    Serial.print(" ");
    Serial.print(gs_pul);
    Serial.print('\n');
  }
}

void loop() {
  input = Serial.read();
  Serial.print(get_dist());
  Serial.write('z');
//  Serial.print(get_dist());

  if (get_dist() < 40){
        base_motor.rot_motor(0);
   }
  if(input != -1 ){
    Serial.print(input);

    Serial.write('x');
    if (input == 's'){
      Serial.print("Start\n");
      s_tim = millis();
      control();
    }else if (input == 'a'){
      Serial.print("Servo init\n");
      lift_servo.rot_init();
      grip_servo.rot_init();
    }else if (input == 'b'){
      Serial.print("Base init\n");
      base_init();
    }else if (input == 'c'){
      Serial.print("Grip test\n");
      if (gtf == 1){
        grip_motor.rot_motor(100);
        gtf = 0;
      }else{
        grip_motor.rot_motor(0);
        gtf = 1;
      }
    }else if (input == 'e'){
      Serial.print("Grip up\n");
      grip_servo.rot_servo(grip_servo.get_pos() + 2);
    }else if (input == 'f'){
      Serial.print("Grip down\n");
      grip_servo.rot_servo(grip_servo.get_pos() - 2);
    }else if (input == 'g'){
      Serial.print("Lift up\n");
      lift_servo.rot_servo(lift_servo.get_pos() + 2);
    }else if (input == 'h'){
      Serial.print("Lift down\n");
      lift_servo.rot_servo(lift_servo.get_pos() - 2);
    }else if (input == 'i'){
      Serial.print("Base up\n");
      base_move(get_dist() + 25);
    }else if (input == 'j'){
      Serial.print("Base down\n");
      base_move(get_dist() - 25);
    }
  } else {

  }
  Serial.write('\n');
}
