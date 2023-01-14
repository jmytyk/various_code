#connecting i2c controlled 16ch pwm.
#look at... 

#https://github.com/adafruit/micropython-adafruit-pca9685   --> actual adafruit lib
#https://github.com/GuyCarver/MicroPython/tree/master/esp8266 --> robot usage, rewritten
#https://github.com/OutOfTheBots/ESP32_PCA9685 --> another robot lib
#https://www.engineersgarage.com/micropython-i2c-protocol-in-esp8266-and-esp3/ --> getting i2c stood up



#imports
import machine
from machine import PWM, Pin, I2C
from time import sleep
import math
import pca9685


#setup the i2c on GPIO 5,4, at 400k, 
# physical board pin is D1,  SCL, conected to GPIO5
# physical board pin is D2,  SDA, conected to GPIO4
#freq of the bus.. good enough?
#timeout of commumication, no connect on the board will cause watchdog to reboot the board.
i2c = I2C(scl=Pin(5), sda=Pin(4), freq=400000, timeout=1000)

#return stuff on the wire, verified the request is being sent via scope
i2c.scan()

#return 64 most of the time, 64,112 sometime --> 64 is 0x40

#put stuff on the wire. 
#i2c.writeto(42, b'123')

#setup the PCA using i2c
#addrerss 0x40 --> clearly documented.
pca= pca9685.PCA9685(i2c,0x40)

#hook up some hardware to see what's happening... 

#changin pwm freq seems to do something. 62-2441 (this is visible on scope)
pca.freq(1500) 
pca.freq() #what did it get set to? the freq is based on scalers?


#set 5 channels to full.
pca.duty(0,2048) #index, duty cycle
pca.duty(1,2048) #index, duty cycle
pca.duty(2,2048) #index, duty cycle
pca.duty(3,2048) #index, duty cycle
pca.duty(4,2048) #index, duty cycle
pca.duty(5,2048) #index, duty cycle
pca.duty(6,2048) #index, duty cycle
pca.duty(7,2048) #index, duty cycle
pca.duty(8,2048) #index, duty cycle
pca.duty(9,2048) #index, duty cycle
pca.duty(10,2048) #index, duty cycle
pca.duty(11,2048) #index, duty cycle
pca.duty(12,2048) #index, duty cycle
pca.duty(13,2048) #index, duty cycle
pca.duty(14,2048) #index, duty cycle
pca.duty(15,2048) #index, duty cycle
pca.duty(16,2048) #index, duty cycle




pca.duty(2,4095) #index, duty cycle
pca.duty(3,4095) #index, duty cycle
pca.duty(4,4095) #index, duty cycle
pca.duty(5,4095) #index, duty cycle
