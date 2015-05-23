/*
  GayBox - Atelier Objets Connectés Lyon - mai 2015

 */

int redPin = 5; // LED connected on Pin 7
int greenPin = 6; // LED connected on Pin 7
int bluePin = 7; // LED connected on Pin 7

#define COMMON_ANODE

int incomingByte = 0; // data received from serial

int inProgress = 0;


void setup() {
  // initialize the digital pin as an output.
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(19200);           // set up Serial library at 19200 bps

  Serial.println("Arduino is ready!");
}


// the loop routine runs over and over again forever:
void loop() {
  launchRainbow();
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);

    if (incomingByte == 49 && inProgress == 0){
      launchRainbow();
      stopRainbow();
    } else {
      stopRainbow();
    }
  }
}


void launchRainbow(){
  Serial.println("Launch Rainbow");
  inProgress = 1;
  setColor(255, 0, 0);  // red
  delay(1500);
  // setColor(255, 255, 0);  // yellow
  // delay(500);
  // setColor(0, 255, 0);  // green
  // delay(500);
  // setColor(0, 255, 255);  // aqua
  // delay(500);
  // setColor(0, 0, 255);  // blue
  // delay(500);
  // setColor(80, 0, 80);  // purple
  // delay(500);
}

void stopRainbow(){
  Serial.println("Stop Rainbow");
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  inProgress = 0;
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





