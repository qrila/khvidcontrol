# Query answer is 11 bits plus Ack 3 bits and completion 3 bits

import serial
import time
import sys
import json

ser = serial.Serial (
    "/dev/ttyUSB0",
    9600,
    timeout = 5
 )

# Visca inquire replies with completion (3 bits)
def queryPosition(ser, data):
    ser.write(data[0])
    dataReceive = map(hex,map(ord,ser.read(data[1])))

    return(dataReceive)

def setData(data):
    return {
        "pantilt": ["\x81\x09\x06\x12\xFF", 11], # Receive 11bit
        "zoom": ["\x81\x09\x04\x47\xFF", 7] # Receive 7bit
    }.get(data, "error")

pantilt = queryPosition(ser, setData("pantilt"))
zoom = queryPosition(ser, setData("zoom"))

output = {"pantilt": pantilt, "zoom": zoom}
print json.dumps(output)

ser.close()
