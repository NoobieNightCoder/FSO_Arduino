/*
                  CODE FOR TRANSMITTER AND RECEIVER
*/

//Connect libs
#include <string.h>

//Connect Display libs
#include <TFT_eSPI.h>
#include <SPI.h>

// baud Speed
//9600 - maximum stable speed (recommended)
//Must be identical to another microcontroller's baud speed
#define Speed 9600

// Binding the display to the variable
TFT_eSPI tft = TFT_eSPI();

// Display FPS rate  (30 is recommended)
#define FPS 30

//Font size     1 - minimum | 4 - maximum
#define FONT_SIZE 2

void setup() {
  // Serial initialization
  Serial.begin(Speed);

  // Serial1 UART initialization (TX - 18 | RX - 19 on Arduino Mega 2560)
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
  //Checks if User wrote the message and sends it
  if (Serial.available()) {
    String message = Serial.readStringUntil('\r');
    Serial1.println(message);
  }

  //Checks if Serial1 is available
  if (Serial1.available()) {
    String message = Serial1.readStringUntil('\r');

    //Clears extra line ending
    if (message[0] == '\n') {
      message.remove(0, 1);
    }

    //Display the message
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0, FONT_SIZE);
    tft.print(message);
  }
}