# Basic-Keyloggers
This repo showcases basic keyloggers written in different languages. Though keyloggers can be used for nasty purposes, this repo should only serve for educational purposes.

Important commands:

To just compile a program:                                           g++ -o akl.exe actual_keylogger.cpp

To compile a program that uses socket:                               g++ -o akl.exe actual_keylogger.cpp -lws2_32 

To compile a program that runs in the background while using socket: g++ -o akl.exe actual_keylogger.cpp -lws2_32 -mwindows
