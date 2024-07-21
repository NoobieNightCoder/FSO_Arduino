// Connect libs
#include <string.h>

// baud Speed      9600 - maximum stable speed (recommended)
#define Speed 9600

// Delay between sending message
#define Delay 1000

// DEBUG mode
#define DEBUG false

// Message text
String message = "Hello world!";

// Message count
int mesNum = 1;

void setup() {
  // For DEBUG
  if (DEBUG == true)
    Serial.begin(Speed);

  // Serial1 UART initialization (TX - 18 on Arduino Mega 2560)
  Serial1.begin(Speed);
}

void loop() {
  // Sending message
  String SendMessage = message + " #" + String(mesNum);
  Serial1.println(SendMessage);
  delay(Delay);
  mesNum++;
}