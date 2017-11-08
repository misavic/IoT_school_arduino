import sys
import serial
import wiringpi


wiringpi.wiringPiSetupGpio()

port = "/dev/ttyS0"
baud = 115200

ser = serial.Serial()
ser.port = port
ser.baudrate = baud

wiringpi.pinMode(8, 1)
try:
   ser.open()
except:
   sys.stderr.write("Error opening serial port %s\n" % (ser.portstr) )
   sys.exit(1)

ser.setRtsCts(0)

while 1:
    # Read from serial port, blocking
    data = ser.read(1)

    # If there is more than 1 byte, read the rest
    n = ser.inWaiting()
    if n:
       data = data + ser.read(n)


    print(str(data))

    letter = str(data)[5]

    print(letter)

