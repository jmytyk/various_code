#include <Adafruit_NeoPixel.h>
#define LED_PIN 1
#define LED_COUNT  16
#define BRIGHTNESS  10

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
  
}

void loop() {
  colorWipe(strip.Color(128,  0,    0),          100); //r
  colorWipe(strip.Color(0,    128,  0),          100); //g
  colorWipe(strip.Color(0,    0,    128),        100); //b
  colorWipe(strip.Color(0,    0,    0,    128),  100); //w
  //colorWipe(strip.Color(255,  255,  255,  255),  10); //rgb+w
  //does it clear here?

  pulseWhite(5);

}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void pulseWhite(uint8_t wait) {
  for(int j=0; j<256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(0, 0, 0, strip.gamma8(j)));
    strip.show();
    delay(wait);
  }

  //comp between gamma and not gamma
    strip.fill(strip.Color(10, 0, 0, 0));
    strip.show();

  for(int j=0; j<256; j++) { // Ramp up from 0 to 255

    strip.fill(strip.Color(0, 0, 0, j));
    strip.show();
    delay(wait);
  }

  for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
    strip.fill(strip.Color(0, 0, 0, j));
    strip.show();
    delay(wait);
  }

}

