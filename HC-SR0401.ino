int trigPin = 11;
int echoPin = 12;
long duration, cm, inches;

void setup() {
  //serial port begin
  Serial.begin (9600);
  //define inputs and outputs
  pinMode(trigPin, OUTPUT);
  
  pinMode(echoPin, INPUT);
}

void loop() {
  // the sensor is triggered by a high pulse of 10 more microsecond.
  // give a short low pulse beforehand to ensure a clean high pulse
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);

  //convert the time into a distance
  cm = (duration/2) / 29.1;
  inches = (duration/2) / 74;

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(1000);
}  
