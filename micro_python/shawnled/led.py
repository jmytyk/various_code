#try pin d5, d6, which is GPIO 12 and 14 (used in spi)
#pwm2 --> pin2 is onboard LED

#import
#import machine   #imported by boot.py
from machine import PWM, Pin
from time import sleep
import math

#lut = [10, 15, 18, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]

def round_nearest_int(x):
    if x >= 0:
        return int(x + 0.5)
    else:
        return int(x - 0.5)


def fillCIETable():
    steps = 1024     #number of steps in the lut
    maxValue = 1024
    cie1931 = []    # pre-calculated PWM levels
  
    #scaling factor to convert from 0-100 to 0-maxValue:
    scalingFactor = 100 / maxValue
  
    #luminance value:
    Y = 0.0
  
    #iterate over the array and calculate the right value for it:
    for l in range(steps+1):
        # you need to scale L from a 0-255 range to a 0-100 range:
        lScaled = l * scalingFactor
        
        if lScaled <= 8:
            Y = (lScaled / 903.3)
        else:
            foo = (lScaled + 16) / 116.0
            Y = pow(foo, 3)
      
        #multiply to get 0-maxValue, and fill in the table:
        #cie1931.append(Y * maxValue)
        cie1931.append(round_nearest_int(Y * maxValue))      
      
    for value in cie1931:
        print(value)
  
    return cie1931


def convert(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min



def main():
    

    lut = fillCIETable()
    while True:
        #a way to scale all the values in the LUT
        min_brightness = 0
        max_brightness = 1024

        wait_at_top = 500
        wait_at_bottom = 500

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

            #map lut into min to max
            dcycle_value = round_nearest_int(convert(value, 0, 1024, min_brightness, max_brightness))

            print(dcycle_value)
            pwm1.duty(dcycle_value)
            pwm2.duty(dcycle_value)
            sleep(0.01)

            #pausing for effect, printing something out to keep connection open
        for i in range(wait_at_top):
            sleep(0.01)
            print("top...")

        #trying to find and easy / blunt way off looping down from max to min. 

        #fade down, 2 is inverted. 
        for value in reversed(lut):

            #map lut into min to max
            dcycle_value = round_nearest_int(convert(value, 0, 1024, min_brightness, max_brightness))

            print(dcycle_value)
            pwm1.duty(dcycle_value)
            pwm2.duty(dcycle_value)

            sleep(0.01)

        #pausing for effect, printing something out to keep connection open
        for i in range(wait_at_bottom):
            sleep(0.01)
            print("bottom...")   

        print("end")
    

if __name__ == "___main___":
    main()
