# Query answer is 11 bits plus Ack 3 bits and completion 3 bits

import serial
import time
import sys

ser = serial.Serial (
    "/dev/ttyUSB0",
    9600,
    timeout = 5
 )

def runCommand(ser, command):
    ser.write(command)
    ack = map(hex,map(ord,ser.read(6)))
    return ack

def setData(data):
    return {
        "moveStop": "\x81\x01\x06\x01\x18\x14\x03\x03\xFF",
        "moveUp": "\x81\x01\x06\x01\x01\x07\x03\x01\xFF",
        "moveLeft": "\x81\x01\x06\x01\x09\x01\x01\x03\xFF",
        "moveRight": "\x81\x01\x06\x01\x09\x01\x02\x03\xFF",
        "moveDown": "\x81\x01\x06\x01\x01\x07\x03\x02\xFF",
        "zoomStop": "\x81\x01\x04\x07\x00\xFF",
        "zoomTeleStd": "\x81\x01\x04\x07\x02\xFF",
        "zoomWideStd": "\x81\x01\x04\x07\x03\xFF",
        "menuToggle": "\x81\x01\x06\x06\x10\xFF",
        "menuOK": "\x81\x01\x7E\x01\x02\x00\x01\xFF",
        "menuBack": "\x81\x01\x06\x06\x03\xFF",
        "neutral": "\x81\x01\x06\x02\x18\x18\x00\x00\x00\x00\x00\x00\x00\x00\xFF",
    }.get(data, "\x81\x01\x06\x01\x18\x14\x03\x03\xFF")

runCommand(ser, setData(sys.argv[1]))

ser.close()
