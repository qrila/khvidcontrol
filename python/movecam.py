# Query answer is 11 bits plus Ack 3 bits and completion 3 bits

import serial
import time
import sys, getopt

ser = serial.Serial (
    "/dev/ttyUSB0",
    9600,
    timeout = 5
 )

def runCommand(ser, command):
    ser.write(command)
    ack = map(hex,map(ord,ser.read(6)))

    return ack

# Visca inquire replies with completion (3 bits)
def queryPosition(ser, data):
    ser.write(data[0])
    dataReceive = map(hex,map(ord,ser.read(data[1])))

    return(dataReceive)

def setData(data):
    return {
        "powerON": "\x81\x01\x04\x00\x02\xFF",
        "powerOFF": "\x81\x01\x04\x00\x03\xFF",
        "power": ["\x81\x09\x04\x00\xFF", 4], # Power query
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
    }.get(data, "notfound")


def main(argv):
    opts, args = getopt.getopt(argv,"hc:p:")

    for opt, arg in opts:
        if opt == '-c':
            if arg == "power":
                if queryPosition(ser, setData(arg)) == ['0x90', '0x50', '0x2', '0xff']:
                    runCommand(ser, setData("powerOFF"))
                else:
                    runCommand(ser, setData("powerON"))
            else:
                runCommand(ser, setData(arg))
        elif opt == '-p':
            position = arg.split("::")
            pantilt = '\\x81\\x01\\x06\\x02\\x18\\x18\\x' + position[0].replace(',', '\\x') + '\\xFF'
            zoom = '\\x81\\x01\\x04\\x47\\x' + position[1].replace(',', '\\x') + '\\xFF'
            runCommand(ser, pantilt.decode('string-escape'))
            runCommand(ser, zoom.decode('string-escape'))

    ser.close()

if __name__ == "__main__":
   main(sys.argv[1:])
