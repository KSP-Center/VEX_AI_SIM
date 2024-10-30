#include "include/devices.h"
#include "include/test.cpp"

int main() {
  cout << "program has started" << endl;
  string test = "testing";
  // SETUP
  Test t;
  NeuralNetwork actor;
  NeuralNetwork critic;
  
  while (true) {
    // NN COMPUTE - rewards and reset included in the function
    sim.programSetup();
    
    bot.trainingNetwork(actor, critic, 5000, 0.99, 0.015, 1.05, 1e-4);
  }
  
  return 0;
}