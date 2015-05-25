/*
  GayBox - Atelier Objets Connectés Lyon - mai 2015

 */
#include <Servo.h>
#include <LiquidCrystal.h>
#include "pitches.h"
#define NO_SOUND 0

// Servo motor ------------------------------
Servo prettyServo;
int pos = 0;

// RGB LEDS -------------------------------
int redPin = 2; // LED connected on Pin 7
int greenPin = 3; // LED connected on Pin 7
int bluePin = 4; // LED connected on Pin 7
// Comment if you have RGB common cathode leds :
#define COMMON_ANODE
// colors of the leds for each YMCA tune
int colors[4][3] = {
  {255, 0, 0},    // W color
  {80, 0, 80},    // M color
  {0, 0, 255},    // C color
  {255, 255, 0}   // A color
};


// SPEAKER -------------------------------------------
int speaker = 13; //Speaker connected on Pin 13

//array of notes
int melody[] = {
  NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NO_SOUND
};

// note duration: 1 = whole note, 2 = half note, 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  2,4,8,8
};

// Vitesse de la musique ---------------------------
int pace = 1450;

// Serial Reading ---------------------------
int incomingByte = 0; // data received from serial

// Switch ---------------------------------
int inProgress = 0;

// LCD ------------------------------------------
LiquidCrystal lcd(7,6,9,10,11,12);


// SETUP ======================================================================
void setup() {
  // initialize the digital pin as an output.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // servo init
  prettyServo.attach(8);
  prettyServo.write(pos);

  // lcd init
  lcd.begin(16,2);
  reinitLcd();

  // Serial init
  Serial.begin(19200);           // set up Serial library at 19200 bps
  Serial.println("Arduino is ready!");
}


// LOOP =======================================================================
void loop() {
  // Decomment to launch automatically the program without twitter connection (debug)
  // launchGayFiesta();
  // stopGayFiesta();

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("I received: ");
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
  // lock the switch to prevent another incoming tweet to interrupt the sequence
  inProgress = 1;
  startLcd();
  freddyServoUp();
  launchRainbowAndMusic();
}

void stopGayFiesta() {
  stopRainbow();
  freddyServoDown();
  reinitLcd();
  delay(2000);
  // unlock the switch
  inProgress = 0;
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
  prettyServo.write(pos);
  delay(10);
}

// Leds and tunes ----------------------------------------------------------------------
void launchRainbowAndMusic() {
  for (int note = 0; note < 4; note++) {
    int duration = pace/noteDurations[note]; //Adjust duration with the pace of music
    tone(speaker, melody[note],duration); //Play note
    setColor(colors[note][0],colors[note][1], colors[note][2]); // display Leds color
    delay(duration * 1.2);
  }
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

