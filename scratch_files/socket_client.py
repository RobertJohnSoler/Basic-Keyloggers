
# Import socket module 
import socket             
 
# Create a socket object 
s = socket.socket()         
 
# Define the port on which you want to connect 
port = 8080           
 
# connect to the server on local computer 
s.connect(('127.0.0.1', port)) 
 
# receive data from the server and decoding to get the string.
print("Sending hello message from Python client to server...")
s.send("Hello from my python client!".encode())
print ("Hello sent to server.")
# close the connection 
s.close()     