/*
  GayBox - Atelier Objets Connectés Lyon - mai 2015

 */
 
int led = 7; // LED connected on Pin 7  
int incomingByte = 0; // data received from serial

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(19200);           // set up Serial library at 19200 bps
  
  Serial.println("Arduino is ready!");    
}

// the loop routine runs over and over again forever:
void loop() {
  
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);

    if (incomingByte == 49){
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(3000);               // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    } else {
      digitalWrite(led, LOW);
    }  
  }

}
