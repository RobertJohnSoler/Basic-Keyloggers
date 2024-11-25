# Basic-Keyloggers

## Overview
This repo showcases basic keyloggers written in different languages. Though keyloggers can be used for nasty purposes, this repo should only serve for educational purposes.

The keyloggers in this project come in three different versions: C, C++, and Python. C and C++ because they are the languages most commonly used for malware, and Python because it's the easiest one to understand and learn from.

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


[comment]: <> (talk about prerequisites next, such as making sure both machines can ping each other, testing the socket scratch files and verifying that socket communications work, attacking your own machine first, and then attacking another machine.)