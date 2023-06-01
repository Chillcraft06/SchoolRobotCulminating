//There are two pins for each motor whose
//state will determing the state of movement
//for that motor (still, running, power, direction)
int motor1WireA = 5;
int motor1WireB = 6;

// Probably for ground
int motor2WireA = 10;
int motor2WireB = 11;

int mode = 1;
int modeButton = 2;
bool modeBtnPressed = false;
int modeLED = 3; // Will need changes in functionality if PWM port needed (such as ultrasonic distance sensor), works just fine for now.

int selectButton = 8;

int lineDetector = 13;

void setup() {
  //I will setup and demonstrate one motor here.
  //The arduio will be setting the state of these
  //wires, so these should be setup as OUTPUTs
  pinMode(motor1WireA, OUTPUT);
  pinMode(motor1WireB, OUTPUT);
  pinMode(modeLED, OUTPUT);

  pinMode(modeButton, INPUT);
  pinMode(selectButton, INPUT);
  pinMode(lineDetector, INPUT);

  
  
}

void loop() {
  if (digitalRead(modeButton) == HIGH && !modeBtnPressed)
  {
    modeBtnPressed = true;
    mode += 1;
    if (mode > 2) // change max number as modes are added
    {
      mode = 1;
    }
  }

  analogWrite(modeLED, map(mode, 1, 2, 100, 200)); // show mode number through brightness.

  if (digitalRead(selectButton) == HIGH)
  {
    digitalWrite(modeLED, LOW);
    switch(mode)
    {
      case 1: // Normal mode / Testing mode
        TestingMode();
      break;

      case 2: // Line follow mode
        LineFollow();
      break;
    }
    
    //After mode finishes, go back to selection "menu".

  }

  if (digitalRead(modeButton) == LOW && modeBtnPressed)
  {
    modeBtnPressed = false;
  }
}

void TestingMode()
{
  delay(2000);

  Turn(-90, 50);
  Stop(1000);
  Turn(90, 50);
  Stop(500);
  Turn(90, 50);
  Stop(1000);
  Turn(-90, 50);
  Stop(500);
  AbsForwards(500, 100);
  AbsBackwards(1000, 50);
  Stop(1000);
}

void LineFollow()
{
  while(digitalRead(modeButton) == LOW)
  {
    delay(2000);

    if (digitalRead(lineDetector) == HIGH)
    {
      Turn(10, 75);
    }
    else
    {
      Turn(-10, 75);
    }
    AbsForwards(100, 75);
  }
  modeBtnPressed = true;
}

void AbsForwards(int ms, int intensity)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    analogWrite(motor1WireA, (int)(map(intensity, 1, 100, 100, 255) - 2)); 
    digitalWrite(motor1WireB, LOW);
  
    analogWrite(motor2WireA, (int)(map(intensity, 1, 100, 100, 255)));
    digitalWrite(motor2WireB, LOW);
  }

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}


void AbsBackwards(int ms, int intensity)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, LOW);
    analogWrite(motor1WireB, (int)(map(intensity, 1, 100, 100, 255) + 2 )); 


    digitalWrite(motor2WireA, LOW);
    analogWrite(motor2WireB, (int)(map(intensity, 1, 100, 100, 255)));
    
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

  while(millis() <= targetTime)
  {

    // Turn right
    if (Degrees > 0) {
      digitalWrite(motor1WireA, LOW);
      analogWrite(motor1WireB, map(intensity, 1, 100, 100, 255) / 2);
      
      analogWrite(motor2WireA, map(intensity, 1, 100, 100, 255) / 2);
      digitalWrite(motor2WireB, LOW);
    }
    // Turn left
    else {
      analogWrite(motor1WireA, map(intensity, 1, 100, 100, 255) / 2);
      digitalWrite(motor1WireB, LOW);
      
      digitalWrite(motor2WireA, LOW);
      analogWrite(motor2WireB, map(intensity, 1, 100, 100, 255) / 2);

    }
  }
  
  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}


/* OLD CODE, may still need just in case

void Forwards(int ms, int intensity)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    analogWrite(motor1WireA, map(intensity, 1, 100, 100, 255));
    digitalWrite(motor1WireB, LOW);
  
    analogWrite(motor2WireA, map(intensity, 1, 100, 100, 255));
    digitalWrite(motor2WireB, LOW);
  }

  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}

void Backwards(int ms, int intensity)
{
  int targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, LOW);
    analogWrite(motor1WireB, map(intensity, 1, 100, 100, 255));
  
    digitalWrite(motor2WireA, LOW);
    analogWrite(motor2WireB, map(intensity, 1, 100, 100, 255));
  }
  
  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}

*/
