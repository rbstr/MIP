#include "mbed.h"
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <map>

DigitalOut myled(LED1);
string name = "Filip";


float LONG = 1.0;
float SHORT = 0.5;
float SPACE = 0.4;
float PAUSE = 0.4;

void showLED(float time) {
     myled = 1;
     wait(time);
     myled = 0;
     wait(PAUSE);
 }

string getChar(char c) {
    switch (toupper(c)) {
        case 'A':
            return ".-";
        case 'B':
            return "-...";
        case 'C':
            return "-.-.";
        case 'D':
            return "-..";
        case 'E':
            return ".";
        case 'F':
            return "..-.";
        case 'G':
            return "--.";
        case 'H':
            return "....";
        case 'I':
            return "..";
        case 'J':
            return ".---";
        case 'K':
            return "-.-";
        case 'L':
            return ".-..";
        case 'M':
            return "--";
        case 'N':
            return "-.";
        case 'O':
            return "---";
        case 'P':
            return ".--.";
        case 'Q':
            return "--.-";
        case 'R':
            return ".-.";
        case 'S':
            return "...";
        case 'T':
            return "-";
        case 'U':
            return "..-";
        case 'V':
            return "...-";
        case 'W':
            return ".--";
        case 'X':
            return "-..-";
        case 'Y':
            return "-.--";
        case 'Z':
            return "--..";
        case ' ':
            return "|";
        default: return "";
    }
}

string getMorse(string name) {
    string result = "";

    for (int i = 0; i < name.size(); i++){
        result += getChar(name[i]);
    }

    return result;
    
}

int main() {
    float duration;
    string morse_name = getMorse(name);
    for (int i = 0; i < morse_name.size(); i++){   

        if (morse_name[i] == '|') {
            wait(PAUSE);
            continue;
        }   
                          
        if (morse_name[i] == '.') {
            duration = SHORT;
        }

        if (morse_name[i] == '-') {
            duration = LONG;
        }
        showLED(duration);
    }
}
