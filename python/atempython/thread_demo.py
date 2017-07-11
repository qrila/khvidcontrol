#!/bin/python
import time
import ATEM
import threading
import code

def ATEMLoop(runev):
    while runev.is_set():
        time.sleep(0.005)
        ATEM.runLoop()

ATEM.begin(192,168,10,240)

thread1_runev = threading.Event()
thread1_runev.set()
thread1 = threading.Thread(target=ATEMLoop, args=(thread1_runev,))
thread1.start()

code.interact()
thread1_runev.clear()
thread1.join()
