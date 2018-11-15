# Input format:
# python atemgetftb.py <ip>

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
		ATEM.runLoop()
		if time.time() > time_set:
			jep = ATEM.getFadeToBlackStateFullyBlack()
			print jep
			run_cmd = 0


if __name__ == "__main__":
    main(sys.argv[1:])
