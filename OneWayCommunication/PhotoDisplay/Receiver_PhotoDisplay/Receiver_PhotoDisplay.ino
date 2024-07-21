// Connect libs
#include <string.h>

// Display libs
#include <TFT_eSPI.h>
#include <SPI.h>

// baud Speed (Must be identical to the transmitter baud Speed)
#define Speed 9600

// Binding the display to the variable
TFT_eSPI tft = TFT_eSPI();

// The size of transmitted image
#define imageWidth 120
#define imageHeight 120

// Display FPS rate  (30 is recommended)
#define FPS 30

// DEBUG mode
#define DEBUG false

void setup() {
  // For debugging
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

    // start receiving package
    String packet = Serial1.readStringUntil('\r');

    // Initializing package variables
    int x = -1, y = -1, hex;
    uint16_t color;

    String xcoord = "";
    String ycoord = "";
    String hexStr = "";

    // Package receiving
    for (int i = 0; i < packet.length(); i++) {
      // X coordinate
      if (x == -1) {
        if (packet[i] != ' ') {
          xcoord += packet[i];
        } else {
          x = xcoord.toInt();
        }
      }

      // Y coordinate
      else if (y == -1) {
        if (packet[i] != ' ') {
          ycoord += packet[i];
        } else {
          y = ycoord.toInt();
        }
      }

      // HEX Color code
      else {
        hexStr += packet[i];
      }
    }
    color = hexStr.toInt();

    // View package contents (For DEBUG)
    if (DEBUG == true)
      Serial.println("X: " + String(x) + "  Y: " + String(y) + "  HEX Color: " + String(color, HEX));

    // Drawing the pixel
    tft.drawPixel(x, y, color);
  }
}