import socket

while True:

    s = socket.socket()
    print("Socket created.")

    port = 8080

    s.bind(('0.0.0.0', port))
    print("Socket binded to ", port)

    s.listen(5)
    print("Socket is listening...")


    c, addr = s.accept()
    print("Got connection from ", addr)
    
    while True:
        try:
            print(c.recv(1024).decode(), end="", flush=True)
        except:
            print("Client must have disconnected.")
            s.close()
            break
        