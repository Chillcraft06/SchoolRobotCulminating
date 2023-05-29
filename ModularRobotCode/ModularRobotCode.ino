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

  Forwards(1);

  Stop(1);

  Backwards(1);

  Stop(1);

  Turn(90);

  Stop(0.5);
  
  Turn(-90);

  Stop(1);
}

void loop() {
  
}


// Move forwards
void Backwards(float seconds)
{
  float targetTime = millis() + (seconds * 1000);
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, HIGH);
  
    digitalWrite(motor2WireA, LOW);
    digitalWrite(motor2WireB, HIGH);
  }
  
  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}

// Essentially just the move forward code, but reversed the current outputss
void Forwards(float seconds)
{
  float targetTime = millis() + (seconds * 1000);
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, HIGH);
    digitalWrite(motor1WireB, LOW);
  
    digitalWrite(motor2WireA, HIGH);
    digitalWrite(motor2WireB, LOW);
  }

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}


// Stop moving
void Stop(float seconds)
{
  float targetTime = millis() + (seconds * 1000);
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, LOW);
  
    digitalWrite(motor2WireA, LOW);
    digitalWrite(motor2WireB, LOW);
  }

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);

}

// Turn by "Degrees"
void Turn(int Degrees)
{
  // Start initially off

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
  
  float targetTime = millis() + (Degrees * 5);
  while(millis() <= targetTime)
  {
    // Turn right
    if (Degrees > 0) {
      digitalWrite(motor1WireA, LOW);
      digitalWrite(motor1WireB, HIGH);
    }
    // Turn left
    else {
      digitalWrite(motor2WireA, LOW);
      digitalWrite(motor2WireB, HIGH);
    }
  }
  
  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}
