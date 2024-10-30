// libraries
#include "include/devices.h"
#include "include/robotFunctions.cpp"

// main program
int main() {
  cout << "program started" << endl;
  Bot bot;
  sim.programSetup();
  bool sending;
  
  while (true) {
    if (score_checker->getTime() >= 0) {
      sending = true;
      while (sending == true) {
        bot.score();
        bot.currentScore = 0;
        sim.delay(32, "msec");
      }
    }
  }
}