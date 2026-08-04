from gpiozero import Button
from pynput.keyboard import Controller, Key
from signal import pause
import time

button0=Button(26, pull_up=True)
button1=Button(13, pull_up=True)
button2=Button(6, pull_up=True)
button3=Button(5, pull_up=True)
keyboard=Controller()

def pressed0():
    print("THE BUTTON HAS WORKED")
    keyboard.press(Key.up)
def released0():
	print("THE BUTTON HAS RELEASED")
	keyboard.release(Key.up)
def pressed1():
    print("THE BUTTON HAS WORKED")
    keyboard.press(Key.right)
def released1():
	print("THE BUTTON HAS RELEASED")
	keyboard.release(Key.right)
def pressed2():
    print("THE BUTTON HAS WORKED")
    keyboard.press(Key.left)
def released2():
	print("THE BUTTON HAS RELEASED")
	keyboard.release(Key.left)
def pressed3():
    print("THE BUTTON HAS WORKED")
    keyboard.press(Key.down)
def released3():
	print("THE BUTTON HAS RELEASED")
	keyboard.release(Key.down)

button0.when_pressed= pressed0
button0.when_released=released0
button1.when_pressed= pressed1
button1.when_released=released1
button2.when_pressed= pressed2
button2.when_released=released2
button3.when_pressed= pressed3
button3.when_released=released3
pause()

