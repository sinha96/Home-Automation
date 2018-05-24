import serial
from datetime import datetime
data = serial.Serial('/dev/ttyACM0',9600)
while True:
    while (data.inWaiting()==0):
        pass
    arduinoString = data.readline()
    print(arduinoString)
    f = open('log.txt','a')
    f.write('{} - {}\n'.format(datetime.now().strftime("%c"),arduinoString))
    f.close()
