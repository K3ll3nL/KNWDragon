#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <Servo.h>
#include <Keypad.h>
#include "navSlippage.h" 

#define TRIGGER_PIN  12  
#define ECHO_PIN     11  
#define MAX_DISTANCE 200

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {39, 41, 43, 45}; 
byte colPins[COLS] = {47, 49, 51, 53};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
Servo myservo;  
int pos = 90;    
double actualAngle; 

void setup() {
  lcd.begin(16, 2); // Initialize the lcd
  lcd.clear();       // Clear screen and go to the top line
  lcd.blink();      // Enable blinking cursor
  myservo.attach(9);  // Attach the servo on pin 9 to the servo object
  delay(1000);
  Serial.begin(9600); 
  seedSlippage(); 
  myservo.write(pos); 
}

void loop() { 
  int distance;
  bool _stop = false; 
  lcd.print("Find a gap"); 
  delay(3000);
  lcd.clear(); 
  while(!_stop)
  {
     distance = sonar.ping() / 148; 
     if(distance < 5) 
     {
      lcd.print('-'); //represents wall 
      //lcd.print(distance); 
     } 
     else 
     {
      lcd.print('x'); //represents gap 
      _stop = true; 
     }
     delay(5000); 
   }
   _stop = false; 
  while(!_stop)
  {
      distance = sonar.ping() / 148; 
      if(distance < 5) 
      {
        lcd.print('-'); //represents wall 
        _stop = true; 
      }
      else 
      lcd.print('x'); //represents gap 
      delay(5000); 
  }
  _stop = false; 
  lcd.clear(); 
  delay(10000);    
  //Dead end 
  lcd.print("Dead End"); 
  delay(3000); 
  lcd.clear(); 
  distance = sonar.ping() / 148; 
  while(distance > 3)
  {
    lcd.print("Move forward"); 
    distance = sonar.ping() / 148; 
    delay(5000); 
    lcd.clear(); 
  }
  while(distance < 5)
  {
    lcd.print("Turn left 90");
    distance = sonar.ping() / 148; 
    delay(5000);
    lcd.clear();  
  } 
  lcd.print("Going back...");    
  delay(10000);   
  lcd.clear();
  //Follow a wall and provide 3 ping readings. Complete 4 turns with the slippage function called once per turn 
  lcd.print("Follow a Wall"); 
  delay(10000); 
  lcd.clear();  
  int i = 0; 
  int right = 10; 
  int left = 10; 
  while(i < 5)
  { 
    delay(1000); 
    right = 10; 
    left = 10; 
    distance = sonar.ping() / 148;  
    if(distance < 5) 
    {
      i++; 
      lcd.clear(); 
      lcd.print(distance); 
      delay(1000); 
      lcd.clear(); 
      lcd.print("Look right"); 
      delay(5000); 
      lcd.clear(); 
      right = sonar.ping() / 148; 
      delay(5000); 
      lcd.print("Look left"); 
      delay(5000); 
      left = sonar.ping() / 148; 
    }
    if(right < 5) 
    {
      lcd.clear(); 
      lcd.print("Turn left"); 
      i++; 
      lcd.clear();
    } 
    else 
    {
        lcd.clear(); 
        lcd.print("Turn right"); 
        i++; 
        lcd.clear(); 
    }
    actualAngle = navSlippage(90.0); 
    lcd.clear(); 
    delay(5000); 
    while(90 - actualAngle > 5)
    {
      lcd.clear(); 
      lcd.print("Turn out 10"); 
      delay(5000); 
      lcd.clear(); 
      actualAngle += 10; 
      pos+=10;
      myservo.write(pos); 
     }
    while(actualAngle - 90 > 5)
    {
      lcd.clear(); 
      lcd.print("Turn in 10"); 
      delay(5000); 
      lcd.clear(); 
      actualAngle -= 10; 
      pos-=10; 
      myservo.write(pos); 
    }
    delay(5000); 
    lcd.clear(); 
  }  
  delay(10000);     
  //Approach a barrier and stop when 3" away 
  lcd.print("Approach a barrier"); 
  delay(3000); 
  lcd.clear(); 
  while(!_stop) 
  {
    delay(1000);
    distance = sonar.ping() / 148;  
    if(distance <= 3) 
    {
      lcd.print("Stop"); 
      _stop = true; 
    }
  }
  _stop = false; 
  delay(3000); 
  lcd.clear(); 
  delay(10000); 
  //Navigate a moveable barrier 
  lcd.print("Moveable barrier"); 
  delay(3000); 
  lcd.clear(); 
  while(!_stop) 
  {
    distance = sonar.ping() / 148; 
    if(distance > 5)
    {
       lcd.print("Moving forward"); 
       _stop = true; 
    }
    delay(3000); 
  }
  _stop = false; 
  lcd.clear(); 
  delay(10000); 
  lcd.print("3 distances"); 
  delay(3000); 
  lcd.clear(); 
  //Measure 3 distances 
  for(int i = 0; i < 3; i++)
  {
    lcd.print("Distance "); 
    lcd.print(i+1);
    lcd.print(":"); 
    delay(3000); 
    distance = sonar.ping() / 148; 
    lcd.print(distance); 
    delay(5000); 
    lcd.clear();  
  }
}
