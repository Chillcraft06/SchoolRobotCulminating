#include <Wire.h>
#include <VL53L0X.h>

//There are two pins for each motor whose
//state will determing the state of movement
//for that motor (still, running, power, direction)
int motor1WireA = 11;
int motor1WireB = 6;

// Probably for ground
int motor2WireA = 10;
int motor2WireB = 11;


VL53L0X sensor;

void setup() {
  //I will setup and demonstrate one motor here.
  //The arduio will be setting the state of these
  //wires, so these should be setup as OUTPUTs
  pinMode(motor1WireA, OUTPUT);
  pinMode(motor1WireB, OUTPUT);
  pinMode(motor2WireA, OUTPUT);
  pinMode(motor2WireB, OUTPUT);

  delay(500);

  Serial.begin(115200);

  Wire.begin();

  sensor.setTimeout(500);
  
   if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
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
  if ((sensor.readRangeSingleMillimeters() / 10) <= 8)
  {
    Turn(260, 100);
  }
  else
  {
    AbsBackwards(100, 100);
  }
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  delay(100);
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
