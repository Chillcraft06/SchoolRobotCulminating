#include <SoftwareSerial.h>

//There are two pins for each motor whose
//state will determing the state of movement
//for that motor (still, running, power, direction)
int motor1WireA = 5;
int motor1WireB = 6;

// Probably for ground
int motor2WireA = 10;
int motor2WireB = 11;

int lineDetector = 13;


SoftwareSerial hc06(2,3);
String cmd="";

void setup() {
  //I will setup and demonstrate one motor here.
  //The arduio will be setting the state of these
  //wires, so these should be setup as OUTPUTs
  pinMode(motor1WireA, OUTPUT);
  pinMode(motor1WireB, OUTPUT);
  pinMode(motor2WireA, OUTPUT);
  pinMode(motor2WireB, OUTPUT);
  pinMode(lineDetector, INPUT);

  Serial.begin(9600);

  hc06.begin(9600);
  
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
  while(hc06.available()>0){
        cmd+=(char)hc06.read();
    }
   if(cmd!=""){
    Serial.print("Command recieved : ");
    Serial.println(cmd);
    Serial.println(cmd.indexOf("T"));
    // We expect ON or OFF from bluetooth
    if(cmd.indexOf("T") >= 0){
            Turn(cmd.substring(1).toInt(), 100);
            Serial.println(cmd.substring(1).toInt());
    } else if(cmd.indexOf("F") >= 0){
            AbsForwards(cmd.substring(1).toInt(), 100);
    }else if(cmd.indexOf("B") >= 0){
            AbsBackwards(cmd.substring(1).toInt(), 100);
    }
    else if(cmd.indexOf("S") >= 0){
            Stop(200);
    } // redundant, kept for future possible interruption features
    cmd=""; //reset cmd
  }
}

void TestingMode()
{
  delay(2000);

  Turn(-90, 50);
  Stop(1000);
  Turn(180, 50);
  Stop(1000);
  Turn(90, 50);
  Stop(1000);
  Turn(-360, 50);
  Stop(1000);
  AbsForwards(1000, 100);
  AbsBackwards(2000, 50);
  Stop(1000);
}

void LineFollow()
{
  while(true)
  {
    delay(1000);

    if (digitalRead(lineDetector) == HIGH)
    {
      Turn(10, 75);
      Stop(100);
    }
    else
    {
      Turn(-10, 75);
      Stop(100);
    }
    
    AbsForwards(100, 50);
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
