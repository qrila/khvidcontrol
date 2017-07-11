#!/usr/bin/python
import time
import ATEM
ATEM.begin(192,168,10,240)

Time_Set = time.time() + 0.500
while 1:
    time.sleep(0.05)
    ATEM.runLoop()
    if time.time() > Time_Set:
        ATEM.setProgramInputVideoSource(0, 2);
        ATEM.setPreviewInputVideoSource(0, 3);
        #exit()

#ATEM.demo_a()
