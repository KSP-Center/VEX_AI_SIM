// library for sim functions
#include "include/simFunctions.cpp"

// create the sim class
Sim sim;

class Bot{
private:
  double pixelCount = 0.0;
  int objectCount = 0;

public:
  int currentScore = 0;
  string cS = " ";
  
  // functions
  // grab recognized objects and calulate score
  int score() {
    // score the posts
    objectCount = moveGoal1->getRecognitionNumberOfObjects();
    calcScore(objectCount);
    objectCount = moveGoal2->getRecognitionNumberOfObjects();
    calcScore(objectCount);
    objectCount = moveGoal3->getRecognitionNumberOfObjects();
    calcScore(objectCount);
    objectCount = moveGoal4->getRecognitionNumberOfObjects();
    calcScore(objectCount);
    objectCount = moveGoal5->getRecognitionNumberOfObjects();
    calcScore(objectCount);
    
    cS = currentScore;
    sim.sendMessage(cS.c_str(), (int)strlen(cS.c_str()) + 1);
    
    return 0;
  }
  
  // add the score
  int calcScore(int postScore) {
    switch (postScore) {
      case 0:
        currentScore = currentScore + 0;
        break;
      case 1:
        currentScore = currentScore + 3;
        break;
      case 2:
        currentScore = currentScore + 4;
        break;
      case 3:
        currentScore = currentScore + 5;
        break;
      case 4:
        currentScore = currentScore + 6;
        break;
      case 5:
        currentScore = currentScore + 7;
        break;
      case 6:
        currentScore = currentScore + 8;
        break;
    }
    
    return 0;
  }
};