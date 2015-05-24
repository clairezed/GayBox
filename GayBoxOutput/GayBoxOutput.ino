/*
  GayBox - Atelier Objets Connectés Lyon - mai 2015

 */
#include <Servo.h>
#include <LiquidCrystal.h>

// Servo motor ------------------------------
Servo prettyServo;
int pos = 0;

// RGB LEDS -------------------------------
int redPin = 2; // LED connected on Pin 7
int greenPin = 3; // LED connected on Pin 7
int bluePin = 4; // LED connected on Pin 7
#define COMMON_ANODE

// Serial Reading ---------------------------
int incomingByte = 0; // data received from serial

// Interrupteur ---------------------------
int inProgress = 0;

// LCD ----------------------
LiquidCrystal lcd(7,6,9,10,11,12);

// SETUP ======================================================================
void setup() {
  // initialize the digital pin as an output.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // servo init
  prettyServo.attach(8);

  // lcd init
  lcd.begin(16,2);
  reinitLcd();

  // Serial init
  Serial.begin(19200);           // set up Serial library at 19200 bps
  Serial.println("Arduino is ready!");
}


// LOOP =======================================================================
void loop() {
  launchGayFiesta();
  stopGayFiesta();

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    // Serial.println(incomingByte, DEC);
    Serial.println(incomingByte);

    if (incomingByte == 49 && inProgress == 0){
      launchGayFiesta();
      stopGayFiesta();
    } else {
      stopGayFiesta();
    }
  }
}

void launchGayFiesta() {
  startLcd();
  freddyServoUp();
  launchRainbow();
}

void stopGayFiesta() {
  stopRainbow();
  freddyServoDown();
  reinitLcd();
  delay(2000);
}

// Methods =======================================================================

// Lcd ------------------------------------------------------------------------
void startLcd() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAY GAY GAY");
}

void reinitLcd() {
  lcd.clear();
  lcd.print("GayBox ");
  lcd.setCursor(0,1);
  lcd.print("waiting for #gay");
}

// Servo ----------------------------------------------------------------------
void freddyServoUp() {
  prettyServo.write(90);
  delay(10);
}

void freddyServoDown() {
  prettyServo.write(0);
  delay(10);
  inProgress = 0;
}

// RGB leds -------------------------------------------------------------------
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





