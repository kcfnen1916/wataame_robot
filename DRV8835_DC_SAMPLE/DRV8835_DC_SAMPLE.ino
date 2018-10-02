//DC MOTOR CW/CCW and SPEED CONTROL (PWM =490Hz)

int IN1 = 5;
int IN2 = 6;
//int VR_PIN = A0;
//int VR_VALUE;
int PWM_VALUE = 30;
int STATUS = 2;
void setup() {
}
//void READ_VR(void){
//  VR_VALUE = analogRead(VR_PIN);
//  if ((VR_VALUE >=500) && (VR_VALUE <=523))STATUS = 0; //BREAK
//  if(VR_VALUE <=499){                                  //CCW
//    STATUS = 1;
//    PWM_VALUE = (500 - VR_VALUE)/2;//1to500
//  }
//  if(VR_VALUE >=524){
//    STATUS = 2;                                        //CW
//    PWM_VALUE = (VR_VALUE - 523)/2;
//  }
//}
void PWM_SYORI(){
    if (STATUS == 0){       //BREAK
      analogWrite(IN1,255);
      analogWrite(IN2,255);
    }
    if (STATUS == 1){       //CCW
      analogWrite(IN1,PWM_VALUE);
      analogWrite(IN2,0);
    }
    if (STATUS == 2){       //CW
      analogWrite(IN1,0);
      analogWrite(IN2,PWM_VALUE);
    }
}
void loop(){
//  READ_VR();
  PWM_SYORI();
  delay(50);
}
