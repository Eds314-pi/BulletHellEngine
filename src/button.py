from gpiozero import Button
from pynput.keyboard import Controller, Key
from signal import pause

button = Button(26, pull_up=True)
keyboard = Controller()

def pressed():
<<<<<<< HEAD
keyboard.press(Key.up)
keyboard.release(Key.up)
=======
    print("THE BUTTON HAS WORKED")
    keyboard.press(Key.up)
    keyboard.release(Key.up)
>>>>>>> 1d028f7398ebb7649b070a02c5ee8a57cfa11ab6

button.when_pressed = pressed

pause()
