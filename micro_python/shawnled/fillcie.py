import math


def fillCIETable() :
  '''
    For CIE, the following formulas have  Y as luminance, and
    Yn is the luminance of a white reference (basically, max luminance).
    This assumes a perceived lightness value L* between 0 and 100,
    and  a luminance value Y of 0-1.0.
    if L* > 8:  Y = ((L* + 16) / 116)^3 * Yn
    if L* <= 8: Y = L* *903.3 * Yn


 '''

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
     
  # multiply to get 0-maxValue, and fill in the table:
  cie1931.append(Y * maxValue)

for value in cie1931:
  print(value)
  