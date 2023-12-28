
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//tested good on pin 6
#define PIN 6 

//tested good for full string
#define NUMPIXELS 50 

//setup the pixle object
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

//propagation delay in the string
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

//------------------------------------------------------------------------------------------------
void allflash(){
  
  pixels.clear();
  pixels.show();
  delay(100);
  
  pixels.fill(pixels.Color(255, 255, 255),0);
  pixels.show();
  delay(100);
  
  pixels.clear();
  pixels.show();
  delay(100);

  pixels.fill(pixels.Color(0, 255, 255),0);
  pixels.show();
  delay(100);

  pixels.clear();
  pixels.show();
  delay(100);

  pixels.fill(pixels.Color(0, 255, 255),0);
  pixels.show();
  delay(100);


}



//------------------------------------------------------------------------------------------------
void mediumflash(){
  
  pixels.clear();
  pixels.show();
  delay(100);
  
  pixels.fill(pixels.Color(128, 255, 255),25, 50);
  pixels.show();
  delay(100);
  
  pixels.clear();
  pixels.show();
  delay(100);

  pixels.fill(pixels.Color(0, 255, 255),0,10);
  pixels.show();
  delay(100);

  pixels.clear();
  pixels.show();
  delay(100);

  pixels.fill(pixels.Color(0, 255, 255),15,35);
  pixels.show();
  delay(100);


}

//------------------------------------------------------------------------------------------------
void chase(){

int d = 15;
pixels.clear();
pixels.show();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 150));
    pixels.show();
    delay(d);  // Delay between LED movements
  }

  for (int i = NUMPIXELS - 1; i >= 0; i--) {
    pixels.setPixelColor(i, pixels.Color(70, 204, 255));
    
    if (i+5>0){
      pixels.setPixelColor(i-5, pixels.Color(255, 255, 0));
      pixels.show();
    }

    pixels.show();
    delay(d);  // Delay between LED movements
  }
}


//------------------------------------------------------------------------------------------------
void grow(){

pixels.clear();
pixels.show();


  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(128, 255, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }

}

void sparkle(){

pixels.clear();
pixels.show();

  for(int i=0; i<NUMPIXELS; i+=10) { // For each pixel in chunk...
    pixels.setPixelColor(i, pixels.Color(128, 255, 255));
  }

  pixels.show();
  delay(120);

  for(int i=0; i<NUMPIXELS; i+=7) { // For each pixel in chunk...
    pixels.setPixelColor(i, pixels.Color(150, 150, 233));
  }

  pixels.show();
  delay(500);

  for(int i=0; i<NUMPIXELS; i+=3) { // For each pixel in chunk...
    pixels.setPixelColor(i, pixels.Color(238, 149, 145));
  }
  
  pixels.show();
  delay(800);

  for(int i=0; i<NUMPIXELS; i+=1) { // For each pixel in chunk...
    pixels.setPixelColor(i, pixels.Color(255, 149, 145));
  }
  
  pixels.show();
  delay(10);

}

//------------------------------------------------------------------------
//simple fade up and down
void fade() {
  
  pixels.clear();
  pixels.show();
  delay(100);
  
  for(int i=0; i<255; i++) { // For each pixel in chunk...
    pixels.fill(pixels.Color(i, i, i),0);
    pixels.show();
    delay(10);
  }

for(int i=255; i>0; i--) { // For each pixel in chunk...
    pixels.fill(pixels.Color(i, i, i),0);
    pixels.show();
    delay(10);
  }


}

//------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(255);
}

//------------------------------------------------------------------------
void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  Serial.println("fade"); fade(); 
  pixels.clear(); delay(2000);

  Serial.println("mediumflash");  mediumflash();
  pixels.clear(); delay(500);
  
  Serial.println("mediumflash");  mediumflash();
  pixels.clear(); delay(100);

  Serial.println("mediumflash");  mediumflash();
  pixels.clear(); delay(500);
  
  Serial.println("mediumflash");  mediumflash();
  pixels.clear(); delay(100);

  Serial.println("grow"); grow(); 
  pixels.clear(); delay(2000);

  Serial.println("allflash"); allflash();
  pixels.clear(); delay(750);
    
  Serial.println("mediumflash");  mediumflash();
  pixels.clear(); delay(2000);
  
  Serial.println("mediumflash");  mediumflash();
  pixels.clear(); delay(1000);

  Serial.println("chase"); chase();
  Serial.println("chase"); chase();
  pixels.clear(); delay(2000);
  
  Serial.println("mediumflash");  mediumflash();
  pixels.clear(); delay(10);
  
  Serial.println("sparkle"); sparkle();
  pixels.clear(); delay(2000);

  Serial.println("allflash"); allflash();
  Serial.println("allflash"); allflash();
  Serial.println("allflash"); allflash();
  pixels.clear(); delay(2000);

  Serial.println("...");
}
