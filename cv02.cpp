#include "mbed.h"
#include "stm32469i_discovery.h"
#include "TS_DISCO_F469NI.h"
#include "LCD_DISCO_F469NI.h"
#include "F469_GUI.hpp"
#include <string>

#define START_TIME 120

enum class State { SET, START, RUN, RESET };

volatile static int COUNTDOWN = START_TIME;
volatile static bool countdown_running = false;

void countdown()
{
    while(true) {
        if(countdown_running) {
            COUNTDOWN--;
            ThisThread::sleep_for(1s);
        }
    }
}

int main()
{
    LCD_DISCO_F469NI lcd;
    Label time(400, 200, "00:00", Label::CENTER, Font24);

    Button addSeconds(220, 300, 200, 160, "+ 10 sekund");
    Button minusSeconds(430, 300, 200, 160, "- 10 sekund");

    Button resetButton(10, 300, 200, 160, "Reset");
    Button runButton(640, 300, 200, 160, "Run");

    Thread thread;

    State state = State::SET;

    while (true) {
        if (addSeconds.Touched()) {
            addSeconds.Activate();
            if(state == State::SET) {
                COUNTDOWN += 10;
            }
        }

        if (minusSeconds.Touched()) {
            minusSeconds.Activate();
            if(state == State::SET) {
                COUNTDOWN -= 10;
            }
        }

        if (resetButton.Touched()) {
            resetButton.Activate();
            state = State::RESET;
        }

        if (runButton.Touched()) {
            runButton.Activate();
            state = State::START;
        }

        switch(state) {
            case State::SET: {
                break;
            }
            case State::START: {
                countdown_running = true;
                thread.start(countdown);
                state = State::RUN;
                break;
            }
            case State::RUN: {
                break;
            }
            case State::RESET: {
                countdown_running = false;
                COUNTDOWN = START_TIME;
                state = State::SET;
                break;
            }
        }

        string outputline;
        if (COUNTDOWN > 0) {
            short minute = COUNTDOWN / 60;
            short seconds = COUNTDOWN % 60;

            outputline = ((minute <= 10)? "0":"") + to_string(minute) + ":" + ((seconds < 10)? "0":"") + to_string(seconds);
        } else {
            outputline = "vybuch";
        }

        time.Draw(outputline);

        ThisThread::sleep_for(200ms);
    }
}