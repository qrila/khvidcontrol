# Input format:
# python atemctrl.py <ip> <program input> <preview input>

import sys
import time
import ATEM

def main(argv):
    run_cmd = 1

    atem_ip = argv[0].split(".")
    ATEM.begin(int(atem_ip[0]), int(atem_ip[1]), int(atem_ip[2]), int(atem_ip[3]))

    time_set = time.time() + 0.500
    while run_cmd == 1:
        time.sleep(0.05)

        if argv[1] == 'program':
            ATEM.runLoop()
            if time.time() > time_set:
                ATEM.setAuxSourceInput(0, 10010)
                run_cmd = 0

        elif argv[1] == 'source':
            ATEM.runLoop()
            if time.time() > time_set:
                ATEM.setAuxSourceInput(0, 1)
                run_cmd = 0

        else:
            ATEM.runLoop()
            if time.time() > time_set:
                ATEM.setProgramInputVideoSource(0, int(argv[1]))
                ATEM.setPreviewInputVideoSource(0, int(argv[1]))
                run_cmd = 0



if __name__ == "__main__":
    main(sys.argv[1:])
