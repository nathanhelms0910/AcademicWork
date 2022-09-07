#!/usr/bin/python3
#Author: Nathan Helms
#With Inspiration from baichen
#https://github.com/baichen/StepperMotor-28BYJ-48/blob/master/StepperMotor.py

import time
from gpiozero import LED

class MoveDamnYou:

    def __init__(self, A1, A2, B1, B2):
        self.PIN_A1 = LED(A1)
        self.PIN_A2 = LED(A2)
        self.PIN_B1 = LED(B1)
        self.PIN_B2 = LED(B2)

    def setStep(self,p1, p2, p3, p4):
        self.PIN_A1.value = p1
        self.PIN_A2.value = p2
        self.PIN_B1.value = p3
        self.PIN_B2.value = p4

    def clockwise(self, delay, steps):
        for i in range(0, steps):
            self.setStep(1, 0, 1, 0)
            time.sleep(delay)
            self.setStep(0, 1, 1, 0)
            time.sleep(delay)
            self.setStep(0, 1, 0, 1)
            time.sleep(delay)
            self.setStep(1, 0, 0, 1)
            time.sleep(delay)

    def counter_clockwise(self, delay, steps):
        for i in range(0, steps):
            self.setStep(1, 0, 0, 1)
            time.sleep(delay)
            self.setStep(0, 1, 0, 1)
            time.sleep(delay)
            self.setStep(0, 1, 1, 0)
            time.sleep(delay)
            self.setStep(1, 0, 1, 0)
            time.sleep(delay)


if __name__=='__main__':

    #MoveDamnYou motor1(22, 27, 17, 18)
    motor1 = MoveDamnYou(22, 27, 17, 18)

    while True:
        motor1.clockwise(5.0/1000, 512)
        time.sleep(1)





