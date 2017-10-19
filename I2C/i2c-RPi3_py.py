#!/usr/bin/python
import smbus
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM) ##
GPIO.setup(26, GPIO.IN)

bus = smbus.SMBus(1)
address = 0x04
def writeNumber(value):
	bus.write_byte(address, value)
	return -1
def readNumber():
	number = bus.read_byte(address)
	return number

def  my_callback(channel):
	number = readNumber()
	print "Arduino: Hey RPI, I received a digit ", number
GPIO.add_event_detect(26, GPIO.BOTH, callback=my_callback, bouncetime=300)

while True:
	var = input("Enter 1 - 255:")
	if not var:
		continue
	writeNumber(var)
	print "RPI: Hi Arduino, I sent you ", var
	time.sleep(3)
