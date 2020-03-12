#include <KNWRobot.h>

#define SERVO_ONE 29
#define MOTOR_ONE 39 
#define MOTOR_TWO 49 
#define PING 59 
KNWRobot* robot;

void setup(){
  robot = new KNWRobot();
  bool servosuccess = robot->setupServo(SERVO_ONE, 6);
  bool motor1success = robot->setupMotor(MOTOR_ONE, 2); 
  bool motor2success = robot->setupMotor(MOTOR_TWO, 3); 
  bool pingSuccess = robot->setupPing(PING, ); //PIN for PING? 
  bool 

}

void loop() { 
  
  
}

void turn180Servo()
{
    int angle = robot->getKeypadInput(); 
    robot->pca180Servo(SERVO_ONE, angle);
}

void turnContServoTime()
{
    int time = robot->getKeypadInput(); 
    robot->pcaContServo(SERVO_ONE, 60, time); 
}

void moveForwardMediumTime() 
{
    int time = robot->getKeypadInput(); 
    robot->pcaDC2MotorsTime(MOTOR_ONE, 500, MOTOR_TWO, 500, time); 
}

void moveForwardFastTime()
{
    int time = robot->getKeypadInput(); 
    robot->pcaDC2MotorsTime(MOTOR_ONE, 800, MOTOR_TWO, 800, time); 
}

void turnLeft() //test these numbers
{
    robot->pcaDC2MotorsTime(MOTOR_ONE, 0, MOTOR_TWO, 500, time); 
}

void turnRight() //test these numbers
{
    robot->pcaDC2MotorsTime(MOTOR_ONE, 500, MOTOR_TWO, 0, time); 
}

void moveEastOfNorth() //test these numbers
{ 
    robot->pcaDC2MotorsTime(MOTOR_ONE, ,MOTOR_TWO, , time); 
}

void moveWestOfNorth() //test these numbers 
{
    robot->pcaDC2MotorsTime(MOTOR_ONE, ,MOTOR_TWO, , time); 
}

long getPing()
{
    return robot->getPing(PING);
}
