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

  delay(2000);

  Forwards(500, 50);

  Stop(1000);

  Backwards(500, 50);

  Stop(1000);

  Turn(90, 50);

  Stop(1000);
  
  Turn(-90, 50);

  Stop(1000);

  AbsForwards(750, 50);

  Stop(1000);
}

void loop() {
  
}


// Move forwards
void Backwards(int ms, int intensity)
{
  int targetTime = millis() + (int)(ms * (1 / (intensity / 100)));
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
  int targetTime = millis() + ms + (int)(ms * (1 / (intensity / 100)));
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
  int targetTime = millis() + ms + (int)(ms * (1 / (intensity / 100)));
  while(millis() <= targetTime)
  {
    analogWrite(motor1WireA, (int)(map(intensity, 1, 100, 10, 1023) / 1.2));
    digitalWrite(motor1WireB, LOW);
  
    analogWrite(motor2WireA, map(intensity, 1, 100, 10, 1023));
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
  
  int targetTime = millis() + ((abs(Degrees) * 5) * (1 / (intensity / 100)));
  while(millis() <= targetTime)
  {
    // Turn right
    if (Degrees > 0) {
      digitalWrite(motor1WireA, LOW);
      analogWrite(motor1WireB, map(intensity, 1, 100, 10, 1023));
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
