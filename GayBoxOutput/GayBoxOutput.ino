/*
  GayBox - Atelier Objets Connectés Lyon - mai 2015

 */
#include <Servo.h>

// Servo motor ------------------------------
Servo prettyServo;
int pos = 0;

// RGB LEDS -------------------------------
int redPin = 5; // LED connected on Pin 7
int greenPin = 6; // LED connected on Pin 7
int bluePin = 7; // LED connected on Pin 7
#define COMMON_ANODE

// Serial Reading ---------------------------
int incomingByte = 0; // data received from serial

// Interrupteur ---------------------------
int inProgress = 0;


void setup() {
  // initialize the digital pin as an output.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  prettyServo.attach(8);

  Serial.begin(19200);           // set up Serial library at 19200 bps

  Serial.println("Arduino is ready!");
}


// the loop routine runs over and over again forever:
void loop() {
  // launchRainbow();
  // stopRainbow();
  //launchGayFiesta();
  //stopGayFiesta();
  


  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);

    if (incomingByte == 49 && inProgress == 0){
      launchGayFiesta();
      stopGayFiesta();
    } else {
      stopGayFiesta();
    }
  }
}

void launchGayFiesta() {
  freddyServoUp();
  launchRainbow();
}

void stopGayFiesta() {
  stopRainbow();
  freddyServoDown();
  delay(2000);
}

// Methods ----------------------------------------------------------
void freddyServoUp() {
  prettyServo.write(90);
  delay(10);

  // for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
  // {                                  // in steps of 1 degree
  //   prettyServo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
  // for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
  // {
  //   prettyServo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
}

void freddyServoDown() {
  prettyServo.write(0);
  delay(10);
  inProgress = 0;
}

void launchRainbow(){
  Serial.println("Launch Rainbow");
  inProgress = 1;
                                // supposed   // COMMON_ANODE   // COMMON_CATHODE
  setColor(255, 0, 0);       // red        // pink           // yellow
  delay(1300);
  setColor(0, 255, 255);     // aqua       // yellow-green   // pink
  delay(700);
  setColor(0, 0, 255);       // blue       // blue           // red
  delay(400);
  setColor(255, 255, 0);     // yellow     // red            // blue
  delay(400);
  // setColor(0, 255, 0);       // green      // red            // blue
  // delay(500);
  // setColor(80, 0, 80);       // purple     // red - pink       // yellow-green
  // delay(500);
}

void stopRainbow(){
  Serial.println("Stop Rainbow");
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}


void setColor(int red, int green, int blue) {
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


