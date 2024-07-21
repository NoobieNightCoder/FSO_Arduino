// Connect libs
#include <string.h>

// Examples of images
#include "example1.h"  // 120x120 Image
// #include "example2.h"      // 120x120 Image

// The size of the Image
#define imageHeight 120
#define imageWidth 120

// baud Speed      9600 - maximum stable speed (recommended)
#define Speed 9600

// Delay between sending Images
#define Delay 1000

// Debug mode
#define DEBUG false

void setup() {
  // For DEBUG
  if (DEBUG == true)
    Serial.begin(Speed);

  // Serial1 UART initialization (TX - 18 on Arduino Mega 2560)
  Serial1.begin(Speed);
}

//Initialization of variables for calculation time spent on sending an image (For DEBUG)
long int StartTime, EndTime, Time;

void loop() {
  // Start of timing (For DEBUG)
  if (DEBUG == true)
    StartTime = millis();

  // Image transmitting
  for (int y = 0; y < imageHeight; y++) {
    for (int x = 0; x < imageWidth; x++) {

      // Creating a package with next protocol: [X, Y, COLOR]
      // X - x coordinate of the pixel
      // Y - y coordinate of the pixel
      // COLOR - HEX color code of the pixel

      String package = "";
      package += String(x) + " " + String(y) + " ";
      long color = pgm_read_word(&(SendImage[y * imageHeight + x]));

      // Sending the package
      Serial1.print(package);
      Serial1.println(color);

      // View package contents (For DEBUG)
      if (DEBUG == true)
        Serial.println(package + String(color, HEX));
    }
  }

  // End of timing and Calculation of time spent on sending an image (For DEBUG)
  if (DEBUG == true) {
    EndTime = millis();
    Time = EndTime - StartTime;
    Serial.println("Time spent to send the image: " + String(Time));
  }

  delay(Delay);
}