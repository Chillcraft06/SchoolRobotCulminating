//A "starter" program to help you get your motors
//running and controllable...

//There are two pins for each motor whose
//state will determing the state of movement
//for that motor (still, running, power, direction)
int motor1WireA = 5;
int motor1WireB = 6;
int motor2WireA = 10;
int motor2WireB = 11;

void setup() {
  //I will setup and demonstrate one motor here.
  //The arduio will be setting the state of these
  //wires, so these should be setup as OUTPUTs
  pinMode(motor1WireA, OUTPUT);
  pinMode(motor1WireB, OUTPUT);
}

void loop() {
  //I will set the motors to hold a certain state
  //for a certain time, to avoid continuous running
  //and fast battery drain.  This variable will
  //help to do that. To see the whole "routine" again,
  //press the reset button fixed to the arduino.
  int timePassed = millis();

  //For the first two seconds of testing
  if (timePassed < 2000) {
    //keep motor off
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, LOW);
  }
  //for the next three seconds...
  if (timePassed >= 2000 && timePassed < 5000) {
    //spin the motors
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, HIGH);
  }
  //for the next three seconds...
  if (timePassed >= 5000 && timePassed < 8000) {
    //spin in the other direction
    digitalWrite(motor1WireA, HIGH);
    digitalWrite(motor1WireB, LOW);
  }
  //finally, once we have seen the test pattern...
  if (timePassed >= 8000 && timePassed < 10000) {
    //spin in the other direction
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, LOW);
  }

  if (timePassed >= 10000 && timePassed < 12000) {
    //spin in the other direction
    digitalWrite(motor1WireA, HIGH);
    digitalWrite(motor1WireB, LOW);


    digitalWrite(motor2WireA, HIGH);
    digitalWrite(motor2WireB, LOW);
  }

  if (timePassed >= 12000 && timePassed < 14000) {
    //spin in the other direction
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, HIGH);


    digitalWrite(motor2WireA, LOW);
    digitalWrite(motor2WireB, HIGH);
  }

  if (timePassed >= 14000) {
    //spin in the other direction
    digitalWrite(motor1WireA, LOW);
    digitalWrite(motor1WireB, LOW);

    digitalWrite(motor2WireA, LOW);
    digitalWrite(motor2WireB, LOW);
  }

}
