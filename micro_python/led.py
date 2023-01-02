
#try pin d5, d6, which is GPIO 12 and 14 (used in spi)

#pwm2 --> pin2 is onboard LED

#outline

#import
import machine
from machine import PWM, Pin
from time import sleep

def convert(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min

lut = [10, 15, 18, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]

#a way to scale all the values in the LUT
min_brightness = 0
max_brightness = 1024

wait_at_top = 1000
wait_at_bottom = 1000

led1 = Pin(0, Pin.OUT)
led2 = Pin(2, Pin.OUT)

#pin setups
pwm1 = PWM(led1, freq=1000, duty=1023)
pwm2 = PWM(led2, freq=1000, duty=1023)

#turn them off
pwm1.duty(0)
pwm2.duty(1023)

#turn them on
pwm1.duty(1023)
pwm2.duty(0)


#fade up, 2 is inverted
for value in lut:
    print(value)
    
    #map lut into min to max
    dcycle_value = convert(value, 0, 1024, min_brightness, max_brightness)
    print(dcycle_value)

    pwm1.duty(dcycle_value)
    pwm2.duty(dcycle_value)

    sleep(0.01)

#pausing for effect, printing something out to keep connection open
for i in (wait_at_top):
  sleep(0.01)
  print("...")


#trying to find and easy / blunt way off looping down from max to min. 
#fade down, 2 is inverted. 
for value in reversed(lut):
    print(value)

    #map lut into min to max
    dcycle_value = convert(value, 0, 1024, min_brightness, max_brightness)
    print(dcycle_value)
    
    pwm1.duty(dcycle_value)
    pwm2.duty(dcycle_value)

    sleep(0.01)

#pausing for effect, printing something out to keep connection open
for i in (wait_at_bottom):
  sleep(0.01)
  print("...")

