import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)

relay = 10
relay1 = 8

GPIO.setup(relay, GPIO.OUT)
GPIO.setup(relay1, GPIO.OUT)

GPIO.output(relay1, GPIO.HIGH)
time.sleep(1)
GPIO.output(relay1, GPIO.LOW)
time.sleep(1)

GPIO.output(relay, GPIO.HIGH)
time.sleep(1)
GPIO.output(relay, GPIO.LOW)
time.sleep(1)


