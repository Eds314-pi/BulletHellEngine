from gpiozero import Button
from pynput.keyboard import Controller, Key
from signal import pause
import time

button=Button(26, pull_up=True)
keyboard=Controller()

def pressed():
    print("THE BUTTON HAS WORKED")
    keyboard.press(Key.up)
def released():
	print("THE BUTTON HAS RELEASED")
	keyboard.release(Key.up)
button.when_pressed= pressed
button.when_released=released
pause()

