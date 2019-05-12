import time
from typing import List

import serial
from pynput.mouse import Button, Controller
mouse = Controller()
arduino = serial.Serial('COM7', 9600)
time.sleep(2)
prev = ''
prev_s = ''
while 1:
    data = arduino.readline()
    d: List[str] = data.strip().decode().split(',')
    if d[6] == "M":
        while d[4] == "1":
            data = arduino.readline()
            d: List[str] = data.strip().decode().split(',')
            mouse.position = (int(d[0]), int(d[1]))

            if d[2] == 'L':
                mouse.press(Button.left)
                while d[2] == 'L':
                    data = arduino.readline()
                    d: List[str] = data.strip().decode().split(',')
                    mouse.position = (int(d[0]), int(d[1]))
                mouse.release(Button.left)

            if d[2] == 'S':
                mouse.press(Button.left)
                time.sleep(0.2)
                mouse.release(Button.left)

            if d[2] == 'D':
                mouse.press(Button.left)
                time.sleep(0.2)
                mouse.release(Button.left)
                time.sleep(0.2)
                mouse.press(Button.left)
                time.sleep(0.2)
                mouse.release(Button.left)

            if d[3] == 'L':
                while d[3] == 'L':
                    data = arduino.readline()
                    d: List[str] = data.strip().decode().split(',')
                    mouse.position = (int(d[0]), int(d[1]))
                mouse.release(Button.right)

            if d[3] == 'S':
                mouse.press(Button.right)
                time.sleep(0.2)
                mouse.release(Button.right)

            if d[3] == 'D':
                mouse.press(Button.right)
                time.sleep(0.2)
                mouse.release(Button.right)
                time.sleep(0.2)
                mouse.press(Button.right)
                time.sleep(0.2)
                mouse.release(Button.right)

    else:
        while d[4] == "1":
            data = arduino.readline()
            d: List[str] = data.strip().decode().split(',')
            import serial
            import time
            from pynput.keyboard import Key
            from pynput.keyboard import Controller as kc

            keyboard = kc()
            if d[5] == 'L' and prev != "L":
                keyboard.press(Key.left)
                keyboard.release(Key.left)
            if d[5] == 'R' and prev != "R":
                keyboard.press(Key.right)
                keyboard.release(Key.right)
            if d[5] == 'B' and prev != "B":
                keyboard.press(Key.alt)
                keyboard.release(Key.alt)
                keyboard.press('s')
                keyboard.release('s')
                keyboard.press('b')
                keyboard.release('b')
            if d[5] == 'C' and prev != "C":
                keyboard.press(Key.alt)
                keyboard.release(Key.alt)
                keyboard.press('s')
                keyboard.release('s')
                keyboard.press('c')
                keyboard.release('c')
            if d[5] == 'E' and prev != "E":
                keyboard.press(Key.esc)
                keyboard.release(Key.esc)
            if d[2] == 'S' and prev_s != "S":
                keyboard.press(Key.space)
                keyboard.release(Key.space)
            prev_s = d[2]
            prev = d[5]
    print(d)