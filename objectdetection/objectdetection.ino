#include <NewPing.h>

//There are two pins for each motor whose
//state will determing the state of movement
//for that motor (still, running, power, direction)
int motor1WireA = 5;
int motor1WireB = 6;

// Probably for ground
int motor2WireA = 10;
int motor2WireB = 11;

#define TRIGGER_PIN  8 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2  12 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  //I will setup and demonstrate one motor here.
  //The arduio will be setting the state of these
  //wires, so these should be setup as OUTPUTs
  pinMode(motor1WireA, OUTPUT);
  pinMode(motor1WireB, OUTPUT);
  pinMode(motor2WireA, OUTPUT);
  pinMode(motor2WireB, OUTPUT);

  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
}
void AbsForwards(int ms, int intensity)
{
  unsigned long targetTime = millis() + ms;
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
  unsigned long targetTime = millis() + ms;
  while(millis() <= targetTime)
  {
    digitalWrite(motor1WireA, LOW);
    analogWrite(motor1WireB, (int)(map(intensity, 1, 100, 100, 255) - 2 )); 


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
  unsigned long targetTime = millis() + ms;
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
  unsigned long targetTime = millis() + (unsigned long)(((abs(Degrees) / 4UL) / ((float)intensity / 1000UL)));

  Serial.println(targetTime);

  Serial.println(abs(Degrees) / 4);

  Serial.println((float)intensity / 1000);
  Serial.println((abs(Degrees) / 4) / ((float)intensity / 1000));
  while(millis() <= targetTime)
  {

    // Turn right
    if (Degrees > 0) {
      digitalWrite(motor1WireA, LOW);
      analogWrite(motor1WireB, map(intensity, 1, 100, 100, 255));
      
      analogWrite(motor2WireA, map(intensity, 1, 100, 100, 255));
      digitalWrite(motor2WireB, LOW);
    }
    // Turn left
    else {
      analogWrite(motor1WireA, map(intensity, 1, 100, 100, 255));
      digitalWrite(motor1WireB, LOW);
      
      digitalWrite(motor2WireA, LOW);
      analogWrite(motor2WireB, map(intensity, 1, 100, 100, 255));

    }
  }
  
  digitalWrite(motor1WireA, LOW);
  digitalWrite(motor1WireB, LOW);

  digitalWrite(motor2WireA, LOW);
  digitalWrite(motor2WireB, LOW);
}
void loop() {
  if (sonar.ping_cm() <= 30)
  {
    Turn(10, 70);
  }
  else
  {
    if (sonar2.ping_cm() >= 10)
    {
      Turn(-5, 70);
    }
    else if (sonar2.ping_cm() <= 5)
    {
      Turn(10, 70);
    }
    else
    {
      AbsBackwards(50, 70);
    }
  }
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
