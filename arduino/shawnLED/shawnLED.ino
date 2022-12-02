
// hardware connections to the MEGA
const int debug =  LED_BUILTIN;   // the number of the LED pin
const int supplycontrol1 = 10;    // the number of the mosfet pin
const int supplycontrol2 = 11;    // the number of the mosfet pin

// everything is in miliseconds, multiplying inline is easier to read 
int fade_down_step_time = 1000 * 0.01;
int fade_up_step_time = 1000 * 0.01;
int pause_time_top = 1000 * 5;
int pause_time_bottom = 1000 * 5;

int currentLevel = 1;                 // current light level
int change = 1;                       // step size through the LUT table 

const int resolution = 8;             // how many entries in the LUT  (board dependent) 
const int steps = pow(2, resolution); // how many slots in the LUT

//int cie1931[steps];                   // pre-calculated PWM levels, ie LUT values
int cie1931[255] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,10,10,10,11,11,11,12,12,12,13,13,13,14,14,14,15,15,16,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,28,28,29,29,30,31,31,32,33,33,34,35,35,36,37,37,38,39,40,40,41,42,43,44,44,45,46,47,48,49,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,75,76,77,78,79,80,82,83,84,85,87,88,89,90,92,93,94,96,97,99,100,101,103,104,106,107,108,110,111,113,114,116,118,119,121,122,124,125,127,129,130,132,134,135,137,139,141,142,144,146,148,149,151,153,155,157,159,161,162,164,166,168,170,172,174,176,178,180,182,185,187,189,191,193,195,197,200,202,204,206,208,211,213,215,218,220,222,225,227,230,232,234,237,239,242,244,247,249,252,255,255};





//-------------------------------------------------------------------
void setup() {
  pinMode(debug, OUTPUT);
  pinMode(supplycontrol1, OUTPUT);
  pinMode(supplycontrol2, OUTPUT);
  
  Serial.begin(57600); 
  //while (!Serial) delay(3000);
  
  //not availble on Mega /Uno board, changing pwm duty cycle should happen here.
  //analogWriteResolution(resolution);
  
  //fill the LUT
  //fillCIETable();

}

//-------------------------------------------------------------------
void loop() {

  // decrease or increase by 1 point each time
  // if at the bottom or top, change the direction:
  //if (currentLevel <= 0 || currentLevel >= steps) {
  //  change = -change;
  //}
  //currentLevel += change;


//fade up chunk. 
for (int i = 0; i <= 255; i++) {
  // PWM output the result. Get levels from
  // the pre-calculated CIE1931 table:
  //analogWrite(5, cie1931[currentLevel]);
  analogWrite(debug, cie1931[i]);
  analogWrite(supplycontrol1, cie1931[i]);
  analogWrite(supplycontrol2, cie1931[i]);
   
  //delay(10);
  //Serial.println(i);
  Serial.println(cie1931[i]);

  //fade up step time tweak
  delay(fade_up_step_time);

}

 //this is the pause when at of the cycle
 delay(pause_time_top);

//fade down chunk. 
for (int j = 255; j >= 0; j--) {
  // PWM output the result. Get levels from
  // the pre-calculated CIE1931 table:
  //analogWrite(5, cie1931[currentLevel]);
  analogWrite(debug, cie1931[j]);
  analogWrite(supplycontrol1, cie1931[j]);
  analogWrite(supplycontrol2, cie1931[j]);
   
  //delay(10);
  //Serial.println(j);
  Serial.println(cie1931[j]);

  //fade up step time tweak
  delay(fade_down_step_time);

}

delay(pause_time_bottom);

}

//-------------------------------------------------------------------
//fill up the look-up table that has all the fade values in it. 
void fillCIETable() {
  /*
    For CIE, the following formulas have  Y as luminance, and
    Yn is the luminance of a white reference (basically, max luminance).
    This assumes a perceived lightness value L* between 0 and 100,
    and  a luminance value Y of 0-1.0.
    if L* > 8:  Y = ((L* + 16) / 116)^3 * Yn
    if L* <= 8: Y = L* *903.3 * Yn
  */

  // set the range of values:
  float maxValue = steps;

  // scaling factor to convert from 0-100 to 0-maxValue:
  float scalingFactor = 100 / maxValue;

  // luminance value:
  float Y = 0.0;

  // iterate over the array and calculate the right value for it:
  for (int l = 0; l <= maxValue; l++) {
    // you need to scale L from a 0-255 range to a 0-100 range:
    float lScaled = float(l) * scalingFactor;
    if ( lScaled <= 8 ) {
      Y = (lScaled / 903.3);
    } else {
      float foo = (lScaled + 16) / 116.0;
      Y = pow(foo, 3);
    }

    // multiply to get 0-maxValue, and fill in the table:
    cie1931[l] = Y * maxValue;
  }





}

