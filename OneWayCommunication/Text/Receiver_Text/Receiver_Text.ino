/*
                          DEBUG CODE
*/

// Connect libs
#include <string.h>

// baud Speed (Must be identical to the transmitter baud Speed)
#define Speed 9600

void setup() {
  // For DEBUG
  Serial.begin(Speed);

  // Serial1 UART initialization (RX - 19 on Arduino Mega 2560)
  Serial1.begin(Speed);
}

void loop() {
  // Checks if Serial1 is available
  if (Serial1.available()) {
    // Receiving message
    String message = Serial1.readStringUntil('\r');

    // Clears extra line ending
    if (message[0] == '\n') {
      message.remove(0, 1);
    }

    // Prints received message
    Serial.println(message);
  }
}