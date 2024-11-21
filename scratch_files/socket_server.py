import socket

s = socket.socket()
print("Socket created.")

port = 8080

s.bind(('', port))
print("Socket binded to ", port)

s.listen(5)
print("Socket is listening...")


c, addr = s.accept()
print("Got connection from ", addr)
while True:
    print(c.recv(1024).decode(), end="", flush=True)
    