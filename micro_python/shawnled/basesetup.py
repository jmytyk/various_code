import machine
from machine import PWM, Pin, I2C
from time import sleep
import math
import pca9685
import json

i2c = I2C(scl=Pin(5), sda=Pin(4), freq=400000, timeout=1000)
i2c.scan()

pca= pca9685.PCA9685(i2c,0x40)

#changin pwm freq seems to do something. 62-2441 (this is visible on scope)
pca.freq(500) 
pca.freq() #what did it get set to? the freq is based on scalers?

for v in range(4095):

    pca.duty(0,v) #index, duty cycle
    sleep(0.001)
    print(v)
    
for v in range(4095,0,-1):

    pca.duty(0,v) #index, duty cycle
    sleep(0.001)
    print(v)
