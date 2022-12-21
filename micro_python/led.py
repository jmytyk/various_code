
#try pin d5, d6, which is GPIO 12 and 14 (used in spi)


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

pwm1.duty(25)
pwm2.duty(25)

pwm1.duty(1023)
pwm2.duty(1023)

for x in range(1023):
	pwm1.duty(x)
	pwm2.duty(x)


'''
while True:
  tchannel.pulse_width(cur_width)

  sleep(0.01)

  cur_width += wstep

  if cur_width > max_width:
    cur_width = max_width
    wstep *= -1
  elif cur_width < min_width:
    cur_width = min_width
    wstep *= -1

'''




#loop with delay time


