//Setup the output PWM pin
const int outputPin = 9;

// The number of Steps between the output being on and off
const int pwmIntervals = 100;

// The R value in the graph equation
float R;

void setup() {
  // set the pin connected to the LED as an output
  pinMode(outputPin, OUTPUT);

  // Calculate the R variable (only needs to be done once at setup)
  R = (pwmIntervals * log10(2))/(log10(255));

}

void loop() {
  int brightness = 0;

  for (int interval = 0; interval <= pwmIntervals; interval++) {
      // Calculate the required PWM value for this interval step
      brightness = pow (2, (interval / R)) - 1;
      // Set the LED output to the calculated brightness
      analogWrite(outputPin, brightness);
      delay(40);
  }
}