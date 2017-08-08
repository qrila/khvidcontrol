# Query answer is 11 bits plus Ack 3 bits and completion 3 bits

import sys
import getopt
import json
import serial

SER = serial.Serial(
    "/dev/ttyUSB0",
    9600,
    timeout=1
)

def run_command(ser, command):
    ser.write(command)
    ack = map(hex, map(ord, ser.read(6)))

    return ack

# Visca inquire replies with completion (3 bits)
def query_status(ser, query, bits):
    ser.write(query)
    data_receive = map(hex, map(ord, ser.read(bits)))

    return data_receive

def set_data(data, camera):
    return {
        "powerON": "\\x8" + camera + "\\x01\\x04\\x00\\x02\\xFF",
        "powerOFF": "\\x8" + camera + "\\x01\\x04\\x00\\x03\\xFF",
        "moveStop": "\\x8" + camera + "\\x01\\x06\\x01\\x18\\x14\\x03\\x03\\xFF",
        "moveUp": "\\x8" + camera + "\\x01\\x06\\x01\\x01\\x07\\x03\\x01\\xFF",
        "moveLeft": "\\x8" + camera + "\\x01\\x06\\x01\\x09\\x01\\x01\\x03\\xFF",
        "moveRight": "\\x8" + camera + "\\x01\\x06\\x01\\x09\\x01\\x02\\x03\\xFF",
        "moveDown": "\\x8" + camera + "\\x01\\x06\\x01\\x01\\x07\\x03\\x02\\xFF",
        "zoomStop": "\\x8" + camera + "\\x01\\x04\\x07\\x00\\xFF",
        "zoomTeleStd": "\\x8" + camera + "\\x01\\x04\\x07\\x02\\xFF",
        "zoomWideStd": "\\x8" + camera + "\\x01\\x04\\x07\\x03\\xFF",
        "menuToggle": "\\x8" + camera + "\\x01\\x06\\x06\\x10\\xFF",
        "menuOK": "\\x8" + camera + "\\x01\\x7E\\x01\\x02\\x00\\x01\\xFF",
        "menuBack": "\\x8" + camera + "\\x01\\x06\\x06\\x03\\xFF",
        "neutral": "\\x8" + camera +\
                   "\\x01\\x06\\x02\\x18\\x18\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\xFF",
        "power": ["\\x8" + camera + "\\x09\\x04\\x00\\xFF", 4], # Power query
        "pantilt": ["\\x8" + camera + "\\x09\\x06\\x12\\xFF", 11], # Receive 11bit
        "zoom": ["\\x8" + camera + "\\x09\\x04\\x47\\xFF", 7] # Receive 7bit
    }.get(data, "notfound")


def main(argv):
    opts, args = getopt.getopt(argv, "hc:p:q:")

    for opt, arg in opts:
        if opt == '-c':
            arg = arg.split("::")
            run_command(SER, set_data(arg[0], arg[1]).decode('string-escape'))
        elif opt == '-p':
            arg = arg.split("::")
            pantilt = '\\x8' + arg[2] +\
                      '\\x01\\x06\\x02\\x18\\x14\\x' + arg[0].replace(',', '\\x') + '\\xFF'
            zoom = '\\x8' + arg[2] + '\\x01\\x04\\x47\\x' + arg[1].replace(',', '\\x') + '\\xFF'
            run_command(SER, pantilt.decode('string-escape'))
            run_command(SER, zoom.decode('string-escape'))
        elif opt == '-q':
            arg = arg.split("::")
            if arg[0] == "power":
                camera_id = str(89 + int(arg[1]))
                query_bits = set_data(arg[0], arg[1])
                if query_status(SER, query_bits[0].decode('string-escape'),\
                                query_bits[1]) == ['0x' + camera_id, '0x50', '0x2', '0xff']:
                    run_command(SER, set_data("powerOFF", arg[1]).decode('string-escape'))
                else:
                    run_command(SER, set_data("powerON", arg[1]).decode('string-escape'))
            elif arg[0] == "saveposition":
                ptquery_bits = set_data("pantilt", arg[1])
                zquery_bits = set_data("zoom", arg[1])
                pantilt = query_status(SER, ptquery_bits[0].decode('string-escape'),
                                       ptquery_bits[1])
                zoom = query_status(SER, zquery_bits[0].decode('string-escape'), zquery_bits[1])
                output = {"pantilt": pantilt, "zoom": zoom}
                print json.dumps(output)

    SER.close()

if __name__ == "__main__":
    main(sys.argv[1:])
