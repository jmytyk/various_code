
#try pin d5, d6, which is GPIO 12 and 14 (used in spi)

#pwm2 --> pin2 is onboard LED

#outline

#import
import machine
from machine import PWM, Pin
from time import sleep

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


#max min brightness
maxBright = 100
minBright = 10

#figure out the list of pulse widths, stepping though forward and rev. 
fullRange = maxBright - minBright
p_width_invert = range(maxBright + 1)[::-1]
p_width = fullRange

#fade up, 2 is inverted
for x in range(minBright, maxBright+1):
    print(x)
    pwm1.duty(x)
    pwm2.duty(x)
    sleep(0.01)



#trying to find and easy / blunt way off looping down from max to min. 
#fade down, 2 is inverted. 
for x in reversed(range(fullRange):
    print(x)
    pwm1.duty(x)
    pwm2.duty(x)
    sleep(0.01)




#loop with delay time


