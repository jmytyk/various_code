#connecting i2c controlled 16ch pwm.

#imports
import machine
from machine import PWM, Pin, I2C
from time import sleep
import math
import pca9685

#setup the i2c on pin 22,23, at 400k
i2c = I2C(scl=Pin(22), sda=Pin(23), freq=400000)

#return stuff on the wire. 
i2c.scan()

#put stuff on the wire. 
i2c.writeto(42, b'123')


#setup the PCA using i2c

pca = pca9685(i2c, 0x40) 
pca.freq(4000) #set pwm overall freq


#set 5 channels to full. 
pca.duty(0,4095) #index, duty cycle
pca.duty(1,4095) #index, duty cycle
pca.duty(2,4095) #index, duty cycle
pca.duty(3,4095) #index, duty cycle
pca.duty(4,4095) #index, duty cycle
pca.duty(5,4095) #index, duty cycle

