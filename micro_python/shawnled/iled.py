#connecting i2c controlled 16ch pwm board. 
#look at... 

#https://github.com/adafruit/micropython-adafruit-pca9685   --> actual adafruit lib
#https://www.engineersgarage.com/micropython-i2c-protocol-in-esp8266-and-esp3/ --> getting i2c stood up

#imports
import machine
from machine import PWM, Pin, I2C
from time import sleep
import math
import pca9685
import json


#------------------------------------------------------------------------------------

#do the math to fill a LUT table
def fillCIETable():
    steps = 4095     #number of steps in the lut
    maxValue = 4095
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

#------------------------------------------------------------------------------------

#populate a LUT with values found in a json file. use the juypter notebook to generate the curve and values.

def fillSplTable():
    jin = []
    try:
        with open('spline_pwm_file.json', 'r') as j:
            json_data = json.load(j)
    
    except OSError:
        print("spline_pwm_file.json isn't found")

    jin = json_data.split(',')
    print("length of loaded file ",  len(jin))

    return jin

#------------------------------------------------------------------------------------

#micropython doesn't have the full math lib, need to do it by hand. this functions maps a number from one to another in a range. 

def convert(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

#------------------------------------------------------------------------------------

#micropython doesn't have the full math lib, need to do it by hand

def round_nearest_int(x):
    if x >= 0:
        return int(x + 0.5)
    else:
        return int(x - 0.5)

#------------------------------------------------------------------------------------

#setup the i2c on GPIO 5,4, at 400k, 
# physical board pin is D1,  SCL, conected to GPIO5
# physical board pin is D2,  SDA, conected to GPIO4

def i2cSetup():
        
    #timeout of commumication, no connect on the board will cause watchdog to reboot the board.
    i2c = I2C(scl=Pin(5), sda=Pin(4), freq=400000, timeout=1000)
    
    #return stuff on the wire, verified the request is being sent via scope
    #rpca pwm driver board returns 64, 112 sometime --> 64 is 0x40
    i2c.scan()

def pcaSetup():
    #setup the PCA using i2c
    #addrerss 0x40 --> clearly documented.
    pca= pca9685.PCA9685(i2c,0x40)
    
    #changin pwm freq seems to do something. 62-2441 (this is visible on scope)
    pca.freq(1500) 
    pca.freq() #what did it get set to? the freq is based on scalers?
    
    #set 5 channels to full.
    #pca.duty(0,2048) #index, duty cycle

def valueUpdate(id, value):
    
    #update the duty on the output, id is passed in. 
    pca.duty(id,value) #index, duty cycle
    
    
#------------------------------------------------------------------------------------

def main():
    
    i2cSetup()
    pcaSetup()
    
    #which fade curve to use?
    lut = fillCIETable()
    #lut = fillSplTable()
    
    
    while True:
        #a way to scale all the values in the LUT
        min_brightness = 0
        max_brightness = 4095

        wait_at_top = 250
        wait_at_bottom = 250

        #fade up, 2 is inverted
        for value in lut:

            #map lut into min to max
            dcycle_value = round_nearest_int(convert(value, 0, 4095, min_brightness, max_brightness))

            print(dcycle_value)
            
            valueUpdate(0, dcycle_value)
            valueUpdate(1, dcycle_value)
            valueUpdate(2, dcycle_value)
            valueUpdate(3, dcycle_value)
            valueUpdate(4, dcycle_value)
            valueUpdate(5, dcycle_value)
            valueUpdate(6, dcycle_value)
            valueUpdate(7, dcycle_value)
            valueUpdate(8, dcycle_value)
            valueUpdate(9, dcycle_value)
            
            sleep(0.01)

        for i in range(wait_at_top):
            sleep(0.01)
            print("top...")
            
        for value in reversed(lut):

            dcycle_value = round_nearest_int(convert(value, 0, 4095, min_brightness, max_brightness))

            print(dcycle_value)
            
            valueUpdate(0, dcycle_value)
            valueUpdate(1, dcycle_value)
            valueUpdate(2, dcycle_value)
            valueUpdate(3, dcycle_value)
            valueUpdate(4, dcycle_value)
            valueUpdate(5, dcycle_value)
            valueUpdate(6, dcycle_value)
            valueUpdate(7, dcycle_value)
            valueUpdate(8, dcycle_value)
            valueUpdate(9, dcycle_value)
            
            sleep(0.01)

        #pausing for effect, printing something out to keep connection open
        for i in range(wait_at_bottom):
            sleep(0.01)
            print("bottom...")   

        print("end")
    

if __name__ == "___main___":
    main()

