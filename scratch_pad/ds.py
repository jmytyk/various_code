#working on how to load unload data
import io


datastr = "1, 2, 3, 5, 4, 78, 8"

f = open('data.txt', 'w')
f.write(datastr)

f.close()


f = open('data.txt')
fstring = f.read()
f.close()

data = fstring.split(',')

print(data)

print(data[1])



