// Connect libs
#include <string.h>

// Connect Display libs
#include <TFT_eSPI.h>
#include <SPI.h>

// baud Speed (Must be identical to the transmitter baud Speed)
#define Speed 9600

// Display FPS rate  (30 is recommended)
#define FPS 30

//Font size     1 - minimum | 4 - maximum
#define FONT_SIZE 2

// DEBUG mode
#define DEBUG false

// Binding the display to the variable
TFT_eSPI tft = TFT_eSPI();

void setup() {
  // For DEBUG
  if (DEBUG == true)
    Serial.begin(Speed);

  // Serial1 UART initialization (RX - 19 on Arduino Mega 2560)
  Serial1.begin(Speed);

  // Display initialization
  tft.init();

  // Rotate display
  // tft.setRotation(0);

  // Reset display
  tft.fillScreen(TFT_BLACK);

  // FPS set
  analogWrite(7, FPS);
}

void loop() {
  // Checks if Serial1 is available
  if (Serial1.available()) {
    //Receiving message
    String message = Serial1.readStringUntil('\r');

    //Clears extra line ending
    if (message[0] == '\n') {
      message.remove(0, 1);
    }
    //Prints the message (For DEBUG)
    if (DEBUG == true) Serial.println(message);

    //Display update
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, FONT_SIZE);
    tft.print(message);
  }
}