/*
                          DEBUG CODE
*/

// Connect libs
#include <string.h>

// baud Speed      9600 - maximum stable speed (recommended)
#define Speed 9600

// Delay between sending message
#define Delay 1000

// The message text
String message = "Hello world!";

void setup() {
  // For DEBUG
  Serial.begin(Speed);

  // Serial1 UART initialization (TX - 18 on Arduino Mega 2560)
  Serial1.begin(Speed);
}

void loop() {
  // Sends the message
  Serial1.println(message);
  delay(Delay);
}