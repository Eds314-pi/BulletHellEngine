from gpiozero import Button
from pynput.keyboard import Controller, Key
from signal import pause

button=Button(26, pull_up=True)
keyboard=Controller()

def pressed():
    keyboard.press(Key.up)
    keyboard.release(Key.up)

button.when_pressed= pressed
pause()
print("THE BUTTON HAS WORKED")
