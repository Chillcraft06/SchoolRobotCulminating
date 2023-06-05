int sensor = 13;
int motor1WireA = 5;
int motor1WireB = 6;

// Probably for ground
int motor2WireA = 10;
int motor2WireB = 11;

int Speed = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT);

  pinMode(motor1WireA, OUTPUT);
  pinMode(motor2WireA, OUTPUT);
  pinMode(motor1WireB, OUTPUT);
  pinMode(motor2WireB, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(sensor) == HIGH)
  {
      digitalWrite(motor1WireA, LOW);
      analogWrite(motor1WireB, 255 / Speed);
      
      analogWrite(motor2WireA, 255 / Speed);
      digitalWrite(motor2WireB, LOW);
      delay(35);
  }
  else
  {
    analogWrite(motor1WireA, 255 / Speed);
    digitalWrite(motor1WireB, LOW);
      
    digitalWrite(motor2WireA, LOW);
    analogWrite(motor2WireB, 255 / Speed);
    delay(35);
  }
   
   
   analogWrite(motor1WireA, 255 / Speed);
   digitalWrite(motor1WireB, LOW);

   analogWrite(motor2WireA, 255 / Speed);
   digitalWrite(motor2WireB, LOW);

   delay(25);
}
