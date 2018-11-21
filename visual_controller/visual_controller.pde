import processing.serial.*;
Serial wataamech;

Button start = new Button(10,25,127,50,"start",1,'s');
Button pickup = new Button(147,25,127,50,"pickup",1,'t');
Button finish = new Button(284,25,127,50,"finish",1,'u');
Button emergency = new Button(421,25,127,50,"emergency",2,'o');
Button grip_u = new Button(10,110,60,60,"grip up",1,'e');
Button grip_d = new Button(10,200,60,60,"grip down",1,'f');
Button lift_u = new Button(80,110,60,60,"lift up",1,'g');
Button lift_d = new Button(80,200,60,60,"lift down",1,'h');
Button base_u = new Button(150,110,60,60,"base up",1,'i');
Button base_d = new Button(150,200,60,60,"base down",1,'j');
Button servo_init = new Button(220,110,160,60,"servo init",1,'a');
Button base_init = new Button(220,200,160,60,"base init",1,'b');
Button grip_test = new Button(390,110,160,60,"grip test",1,'c');

Button [] button_list = {start,pickup,finish,emergency,servo_init,base_init,grip_test,grip_u,grip_d,lift_u,lift_d,base_u,base_d};

String [] serial_his = new String[26];;
// String [] values;

int a = 0;

class Button{
  int m_x,m_y,m_xlen,m_ylen;
  boolean m_status;
  color m_c1,m_c2;
  char m_t;
  String m_l;

  Button(int x,int y,int xlen,int ylen,String l,int cf,char t){
    m_x = x;
    m_y = y;
    m_xlen = xlen;
    m_ylen = ylen;
    m_l = l;
    m_t = t;
    if(cf == 1){
      m_c1 = color(37,41,49);
      m_c2 = color(43,46,56);
    }else{
      m_c1 = color(83,32,32);
      m_c2 = color(89,37,39);
    }
  }

  void drawButton() {
    if (overRect()){
      fill(m_c1);
    }else{
      fill(m_c2);
    }
    rect(m_x,m_y,m_xlen,m_ylen);
  }

  void drawText() {
    fill(155,162,178);
    textSize(15);
    textAlign(CENTER,CENTER);
    text(m_l,m_x + m_xlen / 2,m_y + m_ylen / 2);
  }

  void drawTriangle(char c){
    fill(155,162,178);
    if(c == 'u'){
      triangle(m_x+0.1*m_xlen, m_y+0.85*m_xlen, m_x+0.9*m_xlen, m_y+0.85*m_xlen, m_x+0.5*m_xlen, m_y+0.15*m_xlen);
    }else if(c == 'd'){
      triangle(m_x+0.1*m_xlen, m_y+0.15*m_xlen, m_x+0.9*m_xlen, m_y+0.15*m_xlen, m_x+0.5*m_xlen, m_y+0.85*m_xlen);
    }

  }

  boolean overRect() {
    if (mouseX >= m_x && mouseX <= m_x+m_xlen && mouseY >= m_y && mouseY <= m_y+m_ylen) {
      return true;
    }else{
      return false;
    }
  }

  boolean buttonPressed() {
    if (overRect() && mousePressed) {
      if(!m_status){
        m_status = true;
        return true;
        }else{
        return false;
      }
    }else{
      m_status = false;
      return false;
    }
  }

  void serialTrans(){
    if (buttonPressed()){
      wataamech.write(m_t);
      updateSerialHis(m_l + " is Pressed.");
    }
  }
}

void setup() {
  size(1280, 720);
  smooth();
  for (int i = 0; i < 26; i++){
    serial_his[i] = "";
  }
  for (int i = 0; i < Serial.list().length; i++) {
      println(i + ": " + Serial.list()[i]);
    }
  try {
    String portName = Serial.list()[9];
    println(portName);
    wataamech = new Serial(this, portName, 115200);
    wataamech.clear();
    wataamech.bufferUntil(10);
  } catch (NullPointerException e) {
    exit();
  }
}

void draw() {
  // try {
    update();
    serialEvent(wataamech);
    for(int j = 0;j < button_list.length;j++){
      button_list[j].serialTrans();
    }
  // } catch (NullPointerException e) {
  //   // exit();
  // }
}

void update(){
  background(30,33,40);
  fill(19,20,24);
  line(559,0,559,720);
  line(0,100,559,100);
  line(0,270,559,270);
  for(int i = 0;i < button_list.length;i++){
    button_list[i].drawButton();
    if (i >= 7){
      if (i % 2 == 1){
        button_list[i].drawTriangle('u');
      }else{
        button_list[i].drawTriangle('d');
      }
    }else{
      button_list[i].drawText();
    }
  }
  fill(155,162,178);
  textSize(15);
  textAlign(CENTER,CENTER);
  text("grip",40,185);
  text("lift",110,185);
  text("base",180,185);
  fill(155,162,178);
  textSize(15);
  textAlign(LEFT,TOP);
  for(int i = 0;i < 26;i++){
    text(serial_his[i],2,272 + i*17);
  }
}

void updateSerialHis(String s){
  for(int i = 0;i < 25;i++){
    serial_his[i] = serial_his[i+1];
  }
  serial_his[25] = s;
}

void serialEvent(Serial wataamech) { // serialEvent(serial wataamech)
  String st = wataamech.readStringUntil('\n');
  if (st != null){
    updateSerialHis(st);
  }
  a++;
  // str = trim(str);
  // values = split(str, ' ');
}
