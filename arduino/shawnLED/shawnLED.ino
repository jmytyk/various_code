//setup where things are wired up. 

//mosfet connections to the MEGA
const int debug =  LED_BUILTIN;// the number of the LED pin
const int supplycontrol1 = 10;// the number of the mosfet pin
const int supplycontrol2 = 11;// the number of the mosfet pin

//everything is in miliseconds, multiplying inline is easier to read 
int fadeupsteptime = 1000 * 0.01;
int pausetimetop = 1000 * 1;
int fadedownsteptime = 1000 * 0.01;
int pausetimebottom = 1000 * 1;



//-------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(debug, OUTPUT);
  pinMode(supplycontrol1, OUTPUT);
  pinMode(supplycontrol2, OUTPUT);

//flash the onbard pin to ensure we're up and running
  analogWrite(debug, 0);
  delay(250);
  analogWrite(debug, 255);
  delay(250);
  analogWrite(debug, 0);
}


//-------------------------------------------------------------------
void loop() {
//this is the fade up loop, 0-255 steps 
for (int i = 0; i <= 255; i++) {
  Serial.println(i);
  analogWrite(debug, i);
  analogWrite(supplycontrol1, i);
  analogWrite(supplycontrol2, i);
  delay(fadeupsteptime);
}




 //this is the pause when at of the cycle
 delay(pausetimetop);




 //this is the fade down loop, 255-0 steps 
for (int j = 255; j >= 0; j--) {
  Serial.println(j);
  analogWrite(debug, j);
  analogWrite(supplycontrol1, j);
  analogWrite(supplycontrol2, j);
  delay(fadeupsteptime);
}




//this is the pause when at the bottom of the cycle
  delay(pausetimebottom);

}
