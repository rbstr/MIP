#include "mbed.h"
#include "rtos.h"
#include "stm32469i_discovery.h"
#include "TS_DISCO_F469NI.h"
#include "LCD_DISCO_F469NI.h"
#include "F469_GUI.hpp"
#include <cstdint>
#include <cstdio>
#include <string>
#include <ctime>

Semaphore semaphore(1);
Thread thread;
DigitalOut led1(LED1);

enum class State { SET, START, RUN, STOP, ERROR };

volatile State state = State::SET;

Button sendButton(250, 250, 200, 200, "POSLAT");

void Touch() {
  if (sendButton.Touched()) {
    if (state == State::SET) {
      state = State::START;
    }
    sendButton.Draw();
  }
}


void Post()
{
  while(state != State::ERROR){
    semaphore.acquire();
    if (state == State::RUN) {
        time_t t = time(0);
        printf("%s %s %s %s %s %d\n", "api_key=", "\"7BGKHY6ER3G9WR3M\"", "&field1=", "\"PILAR_RUBES\"", "&field2=", t);
        ThisThread::sleep_for(1s);
        state = State::STOP;
    }
    semaphore.release();
  }
} 

int main() {
  
  thread.start(callback(Post));

  while (state != State::ERROR) {
    semaphore.acquire();
    if (state == State::SET) {
      Touch();
    }
    else if (state == State::START) {
      state = State::RUN;
      printf("\nSystem is running\n");
      printf("Thread state: %d\n", thread.get_state());
    }
    else if (state == State::STOP) {
      printf("Thread state: %d\n", thread.get_state());
      state = State::SET;
      printf("SET\n");
    }
    else if (state == State::ERROR) {
      thread.terminate();
      printf("Thread state: %d\n", thread.get_state());
      printf("Problem\n");
    }
    semaphore.release();
  }

  thread.join();
  printf("Thread joined\n");
  printf("End\n");
  exit(1);
}