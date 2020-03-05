#include <KNWRobot.h>
#include <Servo.h>
#define motorpin1 2 //定义IN1管脚
#define motor1pin2 11
#define motor2pin1 13
#define motor2pin2 12
#define pwnleft 6
#define pwnright 3
#define angport 10


//Servo myservo;
int pos;
KNWRobot *robot;
void setup(){
//put your setup code here，to run once
  robot = new KNWRobot();
  delay(1000); 
  robot->clearLCD();
  robot->printLCD("test"); 
  delay(1000); 
  int servoID = 1; 
  bool servosuccess = robot->setupServo(servoID, 12);
  int IRID = 2; 
  bool IRsuccess = robot->setupIR(IRID, 4); 
  int MotorIDLeft = 3; 
  int MotorIDRight = 4; 
  robot->setupMotor(MotorIDLeft,0); 
  robot->setupMotor(MotorIDRight,1); 
  //robot->setupKeypad(); 
  loop(); 
  //Serial.begin(9600);
} 

void loop() {
  robot->clearLCD(); 
  robot->printLCD("Hello World");
  delay(1000); 
  char* input; 
  int angle; 
  input = robot->getKeypadInput();
  if(input == "1")
  {
    robot->clearLCD(); 
    robot->printLCD("Enter Angle");
    delay(1000);  
  }
  angle = robot->getKeypadInput(); 
  robot->pca180Servo(1,angle);
  robot->pca180Servo(1,-angle); 
  delay(1000);  
while(input != '*')
{
  robot->clearLCD(); 
  robot->printLCD("Hello World1"); 
  input = robot->getKeypadInput();
  if(input == '1') //move servo by angle 
  {
    angle = robot->getKeypadInput(); 
    robot->pca180Servo(1,angle);
    robot->pca180Servo(1,-angle);      
  }
  if(input == '2') //move up 3 meters towards a beacon 
  {
     int numIR = robot->scanIR(2); 
     char* IRCharacters = ""; 
     while(IRCharacters[0] != 'K')
     {
        robot->pcaDC2MotorsTime(3,0,4,500,1000);
        IRCharacters = robot->getIR(); 
     }
     robot->pcaDC2MotorsTime(3,500,4,500,5000); 
  }
}
}

/*void loop() {
  while(Serial.available()){
  Serial.println(" Input the choose:\n1:forward\n2:back\n3:turnL\n4:turnR\n5:backL\n6:backR\n7:round180\n8:addspeed\n9:quit\n+:addforward\n-:substractforward\n");
  delay(50);
  input = Serial.read();
  
  if(input == '1') robot->pcaDC2MotorsTime(1,500,2,500, 5000); //{forward(220);}
  if(input == '2') robot->pcaDC2MotorsTime(1,-500,2,-500, 5000);//back
  if(input == '3') robot->pcaDC2MotorsTime(1,0,2,500,2000); //turnL
  if(input == '4') robot->pcaDC2MotorsTime(1,500,2,0,2000); //{turnR(240);}
  if(input == 's') {
    Serial.println(" Angle: ");
    angle = Serial.read(); 
    robot->pca180Servo(1,angle); 
    robot->pca180Servo(1,-angle);     
  }
  /*if(input == '5') {backL(220);}
  if(input == '6') {backR(220);}
  if(input == '7') {leftround180(240);}
  if(input == '8') {rightround180(240);}
  if(input == '9') {break;}
  if(input == '+'){
    sp = sp + 30;
    sp = sp % 255;
    forward(sp);
  }
  if(input == '-'){
    sp = sp - 30;
    sp = sp % 255;
    back(sp);
  }
  if(input == 's') { angle(angport, 120);} //夹取
  if(input == 'r') {angle(angport, 0);} //释放
  if(input == 'a') angle(angport, 30);
  //else forward(150);
  Serial.println("open"); 
  }
}
//pin是电平的IO，pwmpin是pwm波形IO，state控制电机正传或反，val是速度值
/*void motor(int pin1,int pin2, int pwmpin,int state,int val){
  if(state==1)//1是正转{ 
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT); 
    digitalWrite(pin1,1);
    digitalWrite(pin2,0);
    analogWrite(pwmpin,val);
  }else if(state==2){ 
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT); 
    digitalWrite(pin2,1);
    digitalWrite(pin1,0);
    analogWrite(pwmpin,val);
wards  }else if(state==0){
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    digitalWrite(pin1,1);
    digitalWrite(pin2,0); 
    analogWrite(pwmpin,0);
  }
}*/
/*void forward(int i){
  motor(motor1pin1,motor1pin2,pwmleft,1,i);
  motor(motor2pin1,motor2pin2,pwmright,1,i);
}
void back(int j){
  motor(motor1pin1,motor1pin2,pwmleft,2,j);
  motor(motor2pin1,motor2pin2,pwmright,2,j);
}
void turnR(int s){
  motor(motor1pin1,motor1pin2,pwmleft,1,s);
  motor(motor2pin1,motor2pin2,pwmright,1,0);
}
void turnL(int t){
  motor(motor1pin1,motor1pin2,pwmleft,1,0);
  motor(motor2pin1,motor2pin2,pwmright,1,t);
}
void backL(int k){
  motor(motor1pin1,motor1pin2,pwmleft,2,k);
  motor(motor2pin1,motor2pin2,pwmright,2,k/2);
}
void backR(int l){
  motor(motor1pin1,motor1pin2,pwmleft,2,l/2);
  motor(motor2pin1,motor2pin2,pwmright,2,l);
}
void leftround180(int x){
  motor(motor1pin1,motor1pin2,pwmleft,1,x);
  motor(motor2pin1,motor2pin2,pwmright,2,x);
}
void rightround180(int x){
  motor(motor1pin1,motor1pin2,pwmleft,2,x);
  motor(motor2pin1,motor2pin2,pwmright,1,x);
}
void quit(){
  motor(motor1pin1,motor1pin2,pwmleft,0,0);
  motor(motor2pin1,motor2pin2,pwmright,0,0);
}
int up(int num){
  while(num < 150){
    num = num + 2;
    forward(num);
  }
}
int down(int num){
while(num > 50){
    num = num - 2;
    forward(num);
  }
}
void angle(int pin, int val){
  myservo.attach(pin);
  delay(20);
  myservo.write(val);
}*/
