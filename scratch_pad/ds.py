#working on how to load unload data

import json
import array
import numpy


#array('l',[1,2,3,4])
#array.fromfile()

numList = [1, 2, 3, 4, 5]
Array = numpy.array(numList)

# Displaying the array
print('Array:\n', Array)
file = open("file1.txt", "w+")
 
# Saving the array in a text file
content = str(Array)
file.write(content)
file.close()
 
# Displaying the contents of the text file
file = open("file1.txt", "r")
content = file.read()
 
print("\nContent in file1.txt:\n", content)
file.close()


