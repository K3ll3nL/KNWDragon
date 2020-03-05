#include <KNWRobot.h>


//define stuff
int IRSensor = 13;
int LeftMotor = 0;
int LeftMotorID = 20
int RightMotor = 1;
int RightMotorID = 21;
int FrontPing = 2;
int SalServo = 3;
int SalServoID = 22;
int ScoopServo = 4;
int ScoopServoID = 23;


KNWRobot *robot;

void setup() {
  //instantiate robot
  robot = new KNWRobot();
  robot->moveCursor(0, 0);
  robot->printLCD("A");
  delay(5000);
  robot->clearLCD();
  robot->setupMotor(LeftMotorID, LeftMotor);
  robot->setupMotor(RightMotorID, RightMotor);
  robot->setupServo(SalServoID, SalServo);
  robot->setupServo(ScoopServoID, ScoopServo);
  
  loop();
  //set up stuff
}

void loop() {
  while(true){
    //assign keypad input as int
    robot->moveCursor(0, 0);
    robot->printLCD("B");
    int quadrant = robot->getKeypadInput();
    if (quadrant == 1) {
      robot -> printLCD("C");
    }
  }
}
