
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
//this fucntion ie. chunk of code will set the whole string to off wait a little bit, set the string to all white, wait, then back off. 

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

}


//------------------------------------------------------------------------------------------------
//this function ie. chunk of code will have the pixles light up from one end to the other. it starts with all pixels off, ends with all on. 
void grow(){

pixels.clear();
pixels.show();


  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(128, 255, 255));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }

}


//------------------------------------------------------------------------------------------------
//simple fade up and down, starts with all off, ends with all off
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
//Arduino required setup block of code.

void setup() {
  Serial.begin(115200);         //be sure your serial monitor is set to 115200
  pixels.begin();               //INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(255);
}

//------------------------------------------------------------------------
//Arduino required loop block of code.

void loop() {
  pixels.clear();               // Set all pixel colors to 'off'

  Serial.println("allflash");   //use the serial monitor to keep track of where we are in the loop
  allflash();                   //triger the 'all flash' chunk of code. 
  
  Serial.println("allflash");   //use the serial monitor to keep track of where we are in the loop
  allflash();                   //triger the 'all flash' chunk of code. 
  
  Serial.println("allflash");   //use the serial monitor to keep track of where we are in the loop
  allflash();                   //triger the 'all flash' chunk of code. 
  
  Serial.println("allflash");   //use the serial monitor to keep track of where we are in the loop
  allflash();                   //triger the 'all flash' chunk of code. 

  pixels.clear();               //clear all the data awaiting to be sent to the string
  pixels.show();                //send the data to the string
  delay(100);                   //wait just a bit to let all the data proogate down the line. 
  
  delay(2000);                  //pause the whole sequence for 2 seconds

  Serial.println("fade");       //use the serial monitor to keep track of where we are in the loop
  fade();                       //triger the 'fade' chunk of code. 
  
  pixels.clear();               //clear all the data awaiting to be sent to the string
  pixels.show();                //send the data to the string
  delay(100);                   //wait just a bit to let all the data proogate down the line. 
    
  delay(2000);                  //pause the whole sequence for 2 seconds

  Serial.println("grow");       //use the serial monitor to keep track of where we are in the loop
  grow();                       //triger the 'grow' chunk of code. 
  
  pixels.clear(); 
  pixels.show();                //send the data to the string
  delay(100);                   //wait just a bit to let all the data proogate down the line. 

  delay(2000);                  //pause the whole sequence for 2 seconds

  Serial.println("...");        //use the serial monitor to keep track of where we are in the loop




  //talk to pixel 1, set it to a color.

  pixels.clear();  //be sure we have a empty data buffer. 
  pixels.show();   //send the data to the string
  delay(100);      //wait just a bit to let all the data proogate down the line. 



  //note the '1' is which pixel
  //the color is set "in-line" just after... pixels.Color(255,0,0)  -> Red is 255, Green is 0, Blue is 0  (R,G,B)
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));

  pixels.show();   //Send the updated pixel colors to the hardware.
  delay(100);      //wait just a bit to let all the data proogate down the line. 

  Serial.println("...");        //use the serial monitor to keep track of where we are in the loop




}
