import socket

s = socket.socket()
print("Socket created.")

port = 8080

s.bind(('', port))
print("Socket binded to ", port)

s.listen(5)
print("Socket is listening...")

while True:
    c, addr = s.accept()
    print("Got connection from ", addr)
    print(c.recv(1024, 0))
    