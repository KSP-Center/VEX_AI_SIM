#include "include/rewardFunctions.cpp"

#define BLUEZ1 0.0705
#define BLUEZ2 0.094
#define REDZ 0.042
#define YELLOWZ 0.194

class Reset{
private:
  // reset the red rings
  void specificRed(int ID, float x, float y, float z) {
    const double translateRedRing[3] = {x, y, z};
    if (ID == 1) {
      translateRedRing1->setSFVec3f(translateRedRing);
    } else if (ID == 2) {
      translateRedRing2->setSFVec3f(translateRedRing);
    } else if (ID == 3) {
      translateRedRing3->setSFVec3f(translateRedRing);
    } else if (ID == 4) {
      translateRedRing4->setSFVec3f(translateRedRing);
    } else if (ID == 5) {
      translateRedRing5->setSFVec3f(translateRedRing);
    } else if (ID == 6) {
      translateRedRing6->setSFVec3f(translateRedRing);
    } else if (ID == 7) {
      translateRedRing7->setSFVec3f(translateRedRing);
    } else if (ID == 8) {
      translateRedRing8->setSFVec3f(translateRedRing);
    } else if (ID == 9) {
      translateRedRing9->setSFVec3f(translateRedRing);
    } else if (ID == 10) {
      translateRedRing10->setSFVec3f(translateRedRing);
    } else if (ID == 11) {
      translateRedRing11->setSFVec3f(translateRedRing);
    } else if (ID == 12) {
      translateRedRing12->setSFVec3f(translateRedRing);
    } else if (ID == 13) {
      translateRedRing13->setSFVec3f(translateRedRing);
    } else if (ID == 14) {
      translateRedRing14->setSFVec3f(translateRedRing);
    } else if (ID == 15) {
      translateRedRing15->setSFVec3f(translateRedRing);
    } else if (ID == 16) {
      translateRedRing16->setSFVec3f(translateRedRing);
    } else if (ID == 17) {
      translateRedRing17->setSFVec3f(translateRedRing);
    } else if (ID == 18) {
      translateRedRing18->setSFVec3f(translateRedRing);
    } else if (ID == 19) {
      translateRedRing19->setSFVec3f(translateRedRing);
    } else if (ID == 20) {
      translateRedRing20->setSFVec3f(translateRedRing);
    } else if (ID == 21) {
      translateRedRing21->setSFVec3f(translateRedRing);
    } else if (ID == 22) {
      translateRedRing22->setSFVec3f(translateRedRing);
    } else if (ID == 23) {
      translateRedRing23->setSFVec3f(translateRedRing);
    }
  }
  
  // reset the blue rings
  void specificBlue(int ID, float x, float y, float z) {
    const double translateBlueRing[3] = {x, y, z};
    if (ID == 1) {
      translateBlueRing1->setSFVec3f(translateBlueRing);
    } else if (ID == 2) {
      translateBlueRing2->setSFVec3f(translateBlueRing);
    } else if (ID == 3) {
      translateBlueRing3->setSFVec3f(translateBlueRing);
    } else if (ID == 4) {
      translateBlueRing4->setSFVec3f(translateBlueRing);
    } else if (ID == 5) {
      translateBlueRing5->setSFVec3f(translateBlueRing);
    } else if (ID == 6) {
      translateBlueRing6->setSFVec3f(translateBlueRing);
    } else if (ID == 7) {
      translateBlueRing7->setSFVec3f(translateBlueRing);
    } else if (ID == 8) {
      translateBlueRing8->setSFVec3f(translateBlueRing);
    } else if (ID == 9) {
      translateBlueRing9->setSFVec3f(translateBlueRing);
    } else if (ID == 10) {
      translateBlueRing10->setSFVec3f(translateBlueRing);
    }
  }
  
  // reset the yellow goals
  void specificYellow(int ID, float x, float y, float z) {
    const double translateGoal[3] = {x, y, z};
    if (ID == 1) {
      translateGoal1->setSFVec3f(translateGoal);
    } else if (ID == 2) {
      translateGoal2->setSFVec3f(translateGoal);
    } else if (ID == 3) {
      translateGoal3->setSFVec3f(translateGoal);
    } else if (ID == 4) {
      translateGoal4->setSFVec3f(translateGoal);
    } else if (ID == 5) {
      translateGoal5->setSFVec3f(translateGoal);
    }
  }

public:
  void resetBot(float x, float y, float z, float x1, float y1, float z1, float rad) {
    const double translateBot[3] = {x, y, z};
    const double rotateBot[4] = {x1, y1, z1, rad};
    translateFieldBot->setSFVec3f(translateBot);
    rotateFieldBot->setSFRotation(rotateBot);
  }
  
  void resetRed() {
    specificRed(1, 0, 0, REDZ);
    specificRed(2, -1.2, 0, REDZ);
    specificRed(3, -1.2, -0.6, REDZ);
    specificRed(4, -0.6, -0.6, REDZ);
    specificRed(5, 0.6, -0.6, REDZ);
    specificRed(6, 1.2, -0.6, REDZ);
    specificRed(7, 1.2, 0, REDZ);
    specificRed(8, 1.2, 0.6, REDZ);
    specificRed(9, 0.6, 0.6, REDZ);
    specificRed(10, -0.6, 0.6, REDZ);
    specificRed(11, -1.2, 0.6, REDZ);
    specificRed(12, -1.5, 1.2, REDZ);
    specificRed(13, -1.2, 1.2, REDZ);
    specificRed(14, -1.2, 1.5, REDZ);
    specificRed(15, 1.2, 1.5, REDZ);
    specificRed(16, 1.2, 1.2, REDZ);
    specificRed(17, 1.5, 1.2, REDZ);
    specificRed(18, 1.5, -1.2, REDZ);
    specificRed(19, 1.2, -1.2, REDZ);
    specificRed(20, 1.2, -1.5, REDZ);
    specificRed(21, -1.2, -1.5, REDZ);
    specificRed(22, -1.2, -1.2, REDZ);
    specificRed(23, -1.5, -1.2, REDZ);
  }
  
  void resetBlue() {
    specificBlue(1, 0.6, -1.5, BLUEZ1);
    specificBlue(2, -0.6, -1.5, BLUEZ1);
    specificBlue(3, -1.2, -1.5, BLUEZ2);
    specificBlue(4, -1.2, -1.2, BLUEZ2);
    specificBlue(5, -1.5, -1.2, BLUEZ2);
    specificBlue(6, -1.69, -1.69, REDZ);
    specificBlue(7, 1.69, -1.69, REDZ);
    specificBlue(8, 1.5, -1.2, BLUEZ2);
    specificBlue(9, 1.2, -1.2, BLUEZ2);
    specificBlue(10, 1.2, -1.5, BLUEZ2);
  }
  
  void resetYellow() {
    specificYellow(1, 0, -1.2, YELLOWZ);
    specificYellow(2, 0.6, -1.5, YELLOWZ);
    specificYellow(3, 0.6, 1.2, YELLOWZ);
    specificYellow(4, -0.6, 1.2, YELLOWZ);
    specificYellow(5, -0.6, -1.5, YELLOWZ);
  }
};
