
// hardware connections to the MEGA
const int debug =  LED_BUILTIN;   // the number of the on board LED pin
const int supplycontrol1 = 10;    // the number of the mosfet pin
const int supplycontrol2 = 11;    // the number of the mosfet pin

// everything is in miliseconds  (1 second = 1000 milliseconds)
float fade_down_step_time = 50;
float fade_up_step_time = 50;
float pause_time_top = 500;
float pause_time_bottom = 500;

//pre-calculated PWM levels, roughly based in cie1931, thanks Tom I
volatile int cie1931[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,10,10,10,11,11,11,12,12,12,13,13,13,14,14,14,15,15,16,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,28,28,29,29,30,31,31,32,33,33,34,35,35,36,37,37,38,39,40,40,41,42,43,44,44,45,46,47,48,49,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,75,76,77,78,79,80,82,83,84,85,87,88,89,90,92,93,94,96,97,99,100,101,103,104,106,107,108,110,111,113,114,116,118,119,121,122,124,125,127,129,130,132,134,135,137,139,141,142,144,146,148,149,151,153,155,157,159,161,162,164,166,168,170,172,174,176,178,180,182,185,187,189,191,193,195,197,200,202,204,206,208,211,213,215,218,220,222,225,227,230,232,234,237,239,242,244,247,249,252,255};
const int lutsize = sizeof(cie1931)/sizeof(int);

//-------------------------------------------------------------------
void setup() {
  pinMode(debug, OUTPUT);
  pinMode(supplycontrol1, OUTPUT);
  pinMode(supplycontrol2, OUTPUT);
  
  Serial.begin(57600);

  delay(500);
  
  Serial.println("size of table"); 
  Serial.println(lutsize); 

//not availble on Mega /Uno board, changing pwm duty cycle should happen here.
//analogWriteResolution(resolution);

  delay(500);
}

//-------------------------------------------------------------------
void loop() {
  Serial.println(".................. Start Point");

  //fade up chunk. 
  for (int i = 0; i < lutsize; i++) {
    // PWM output the result. Get levels from
    // the pre-calculated CIE1931 table:

    analogWrite(debug, cie1931[i]);
    analogWrite(supplycontrol1, cie1931[i]);
    analogWrite(supplycontrol2, cie1931[i]);
  
    //int temp = cie1931[i];
    Serial.println(cie1931[i]);

    //fade up step time tweak
    delay(fade_up_step_time);

}

Serial.println("------------------ Midpoint");

//this is the pause when at of the cycle
delay(pause_time_top);

//fade down chunk. counts backward, 0 based index
  for (int j = lutsize-1; j >= 0; --j) {
  
    analogWrite(debug, cie1931[j]);
    analogWrite(supplycontrol1, cie1931[j]);
    analogWrite(supplycontrol2, cie1931[j]);

    Serial.println(cie1931[j]);
  
    //fade up step time tweak
    delay(fade_down_step_time);

}

Serial.println("^^^^^^^^^^^^^^^^^^ End Point");

delay(pause_time_bottom);

}
