#include "include/libraries.h"

class Rewards {
private:
  bool approximatelyEqual(double a, double b, double epsilon) {
    return abs(a - b) <= epsilon;
  }
  
public:
  double computeBasic() {
    double extraReward = 0.0;
    double leftDriveVelocity = (left1->getVelocity() + left2->getVelocity() + left3->getVelocity()) / 3;
    double rightDriveVelocity = (right1->getVelocity() + right2->getVelocity() + right3->getVelocity()) / 3;
    
    // forward reward (soon to be changed to be multi-directional)
    if (leftDriveVelocity > 0.01 && rightDriveVelocity < -0.01) {
      if (approximatelyEqual(leftDriveVelocity, rightDriveVelocity * -1, 0.01)) {
        extraReward = extraReward + 20 * (leftDriveVelocity + (rightDriveVelocity * -1)) / 2;
      } else {
        extraReward = extraReward + 10 * (leftDriveVelocity + (rightDriveVelocity * -1)) / 2;
      }
    }
    
    // pneumatic and intake rewards
    if (topRingArm->getTargetPosition() > 0) {
      extraReward = extraReward + 50;
    }
    if (Hook->getTargetPosition() > 0) {
      extraReward = extraReward + 50;
    }
    if (intakeHold->getTargetPosition() > 0) {
      extraReward = extraReward + 50;
    }
    if (intakeRoll->getVelocity() > 0) {
      extraReward = extraReward + 20 * intakeRoll->getVelocity();
    }
    
    cout << "REWARD: " << extraReward << endl;
    return extraReward;
  }
  
  double computeComplex() {
    double extraReward = 0.0;
    
    return extraReward;
  }
};