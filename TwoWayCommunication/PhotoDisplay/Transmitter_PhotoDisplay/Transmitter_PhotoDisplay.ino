// Connect libs
#include <string.h>

// Examples of images
//#include "example1.h"  // 120x120 Image
// #include "example2.h"         // 120x120 Image

#include "amogus.h"

// The size of the Image
#define imageHeight 120
#define imageWidth 120

// baud Speed      38400 - maximum stable speed (recommended)
#define Speed 38400

// Delay between sending Images
#define Delay 5000

// Debug mode
#define DEBUG false

void setup() {
  // For DEBUG
  if (DEBUG == true)
    Serial.begin(Speed);

  // Serial1 UART initialization (TX - 18 on Arduino Mega 2560)
  Serial1.begin(Speed);  //tx
  Serial2.begin(Speed);  //rx
}

//Initialization of variables for calculation time spent on sending an image (For DEBUG)
long int StartTime, EndTime, Time;

void loop() {
  // Start of timing (For DEBUG)
  //if (DEBUG == true)
    StartTime = millis();

  // Image transmitting
  for (int y = 0; y < imageHeight; y++) {
    for (int x = 0; x < imageWidth; x++) {
      // Creating a package with next protocol: [X, Y, COLOR]
      // X - x coordinate of the pixel
      // Y - y coordinate of the pixel
      // COLOR - HEX color code of the pixel

      String package = "";
      long color = pgm_read_word(&(SendImage[y * imageHeight + x]));

      package += String(x) + " " + String(y) + " " + String(color) + " " + String(x + y);

      if (color != 0x0000) {
packageSend:
        // View package contents (For DEBUG)
        if (DEBUG == true)
          Serial.println(package);

        // Sending the package
        while (true) {
          Serial1.println(package);

          // Waiting for a response from receiver
          if (Serial2.available()) {

            // Getting the message
            String mess = Serial2.readStringUntil('\r');

            if (mess[0] == '\n') {
              mess.remove(0, 1);
            }
            
            // View message content (For DEBUG)
            if (DEBUG == true) Serial.println(mess);
            
            // Checking the message, if "OK" then send next package
            if (mess != "OK") {
              goto packageSend;
            } else {
              break;
            }
          }
        }
      }
    }
  }

  // End of timing and Calculation of time spent on sending an image (For DEBUG)
  //if (DEBUG == true) {
    EndTime = millis();
    Time = EndTime - StartTime;
    Serial.println("Time spent to send the image: " + String(Time));
  //}

  delay(Delay);
}