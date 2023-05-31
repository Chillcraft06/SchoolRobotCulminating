//There are two pins for each motor whose
//state will determing the state of movement
//for that motor (still, running, power, direction)
int motor1WireA = 5;
int motor1WireB = 6;

// Probably for ground
int motor2WireA = 10;
int motor2WireB = 11;

void setup() {
  //I will setup and demonstrate one motor here.
  //The arduio will be setting the state of these
  //wires, so these should be setup as OUTPUTs
  pinMode(motor1WireA, OUTPUT);
  pinMode(motor1WireB, OUTPUT);
  Serial.begin(9600);

  delay(2000);

  Turn(90, 50);

  Stop(1000);

  Turn(90, 50);

  Stop(1000);

  Turn(90, 50);

  Stop(1000);

  Turn(90, 50);

  Stop(1000);
}

void loop() {
  
}


// Move forwards
void Backwards(int ms, int intensity)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, LOW);
    analogWrite(motor1WireB, map(intensity, 1, 100, 10, 1023));
  
    digitalWrite(motor2WireA, LOW);
    analogWrite(motor2WireB, map(intensity, 1, 100, 10, 1023));
  }
  
  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}

// Essentially just the move forward code, but reversed the current outputss
void Forwards(int ms, int intensity)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    analogWrite(motor1WireA, map(intensity, 1, 100, 10, 1023));
    digitalWrite(motor1WireB, LOW);
  
    analogWrite(motor2WireA, map(intensity, 1, 100, 10, 1023));
    digitalWrite(motor2WireB, LOW);
  }

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}

void AbsForwards(int ms, int intensity)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    analogWrite(motor1WireA, (int)(map(intensity, 1, 100, 10, 1023) / 1.0055));
    digitalWrite(motor1WireB, LOW);
  
    analogWrite(motor2WireA, (int)(map(intensity, 1, 100, 10, 1023)));
    digitalWrite(motor2WireB, LOW);
  }

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}


// Stop moving
void Stop(int ms)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, LOW);
  
    digitalWrite(motor2WireA, LOW);
    digitalWrite(motor2WireB, LOW);
  }
}

// Turn by "Degrees"
void Turn(int Degrees, int intensity)
{
  // Start initially off

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);

  // Technically should be left as is, turning should be absolute. (90 degrees at 25% speed should be the same as 90 degrees at 100% speed)
  int targetTime = millis() + (int)(((abs(Degrees) / 1.2) / ((float)intensity / 100)));
  Serial.println(millis());
  Serial.println(targetTime);
  while(millis() <= targetTime)
  {
    Serial.println(millis());
    // Turn right
    if (Degrees > 0) {
      digitalWrite(motor1WireA, LOW);
      analogWrite(motor1WireB, map(intensity, 1, 100, 10, 1023) / 2);
      
      analogWrite(motor2WireA, map(intensity, 1, 100, 10, 1023) / 2);
      digitalWrite(motor2WireB, LOW);
    }
    // Turn left
    else {
      digitalWrite(motor2WireA, LOW);
      analogWrite(motor2WireB, map(intensity, 1, 100, 10, 1023));
    }
  }
  
  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}
