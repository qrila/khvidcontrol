# Input format:
# python atemftb.py <ip> <1 or 0>

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

        if argv[1] == 0:
            ATEM.runLoop()
            if time.time() > time_set:
                ATEM.performFadeToBlackME(0, 0)
                run_cmd = 0

        elif argv[1] == 1:
            ATEM.runLoop()
            if time.time() > time_set:
                ATEM.performFadeToBlackME(1, 0)
                run_cmd = 0





if __name__ == "__main__":
    main(sys.argv[1:])
