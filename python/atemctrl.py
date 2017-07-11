# Input format:
# python atemctrl.py <ip> <program input> <preview input>

import ATEM, time, sys

def main(argv):
    run_cmd = 1

    ip = argv[0].split(".")
    ATEM.begin(int(ip[0]),int(ip[1]),int(ip[2]),int(ip[3]))

    Time_Set = time.time() + 0.500
    while run_cmd == 1:
        time.sleep(0.05)
        ATEM.runLoop()
        if time.time() > Time_Set:
            ATEM.setProgramInputVideoSource(0, int(argv[1]));
            ATEM.setPreviewInputVideoSource(0, int(argv[2]));
            run_cmd = 0

if __name__ == "__main__":
    main(sys.argv[1:])
