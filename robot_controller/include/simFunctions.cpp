#define ACCELERATION 1000.0
#define CHANNEL_NUMBER 0.0
#define STARTING_VELOCITY 0.0
#define STARTING_VELOCITY_2 10.0
#define MAX_TORQUE 100
#define RANGE 999.9
#define TARGET_POSITION INFINITY

#include "include/neural-network.cpp"

Reset reset;

class Sim{
private:
  const void* message1;
  string translatedMessage;
  
public:
  // setup the program
  void programSetup() {
    // TARGET_POSITION
    // drivetrain
    left1->setPosition(TARGET_POSITION);
    left2->setPosition(TARGET_POSITION);
    left3->setPosition(TARGET_POSITION);
    right1->setPosition(TARGET_POSITION);
    right2->setPosition(TARGET_POSITION);
    right3->setPosition(TARGET_POSITION);
    intakeRoll->setPosition(TARGET_POSITION);
    conveyor->setPosition(TARGET_POSITION);
    cout << "MAINBOT: positions set" << endl;
  
    // STARTING_VELOCITY
    // drivetrain
    left1->setVelocity(STARTING_VELOCITY);
    left2->setVelocity(STARTING_VELOCITY);
    left3->setVelocity(STARTING_VELOCITY);
    right1->setVelocity(STARTING_VELOCITY);
    right2->setVelocity(STARTING_VELOCITY);
    right3->setVelocity(STARTING_VELOCITY);
    
    // other motors/pneumatics
    Hook->setVelocity(STARTING_VELOCITY_2);
    topRingArm->setVelocity(STARTING_VELOCITY_2);
    intakeHold->setVelocity(STARTING_VELOCITY_2);
    intakeRoll->setVelocity(STARTING_VELOCITY);
    conveyor->setVelocity(STARTING_VELOCITY);
    ringClampL->setVelocity(STARTING_VELOCITY_2);
    ringClampR->setVelocity(STARTING_VELOCITY_2);
    cout << "MAINBOT: default velocities set" << endl;
  
    // TORQUE
    // drivetrain
    left1->setAvailableTorque(MAX_TORQUE);
    left2->setAvailableTorque(MAX_TORQUE);
    left3->setAvailableTorque(MAX_TORQUE);
    right1->setAvailableTorque(MAX_TORQUE);
    right2->setAvailableTorque(MAX_TORQUE);
    right3->setAvailableTorque(MAX_TORQUE);
 
    // other motors/pneumatics
    Hook->setAvailableTorque(MAX_TORQUE * 10);
    topRingArm->setAvailableTorque(MAX_TORQUE * 10);
    intakeHold->setAvailableTorque(MAX_TORQUE * 10);
    intakeRoll->setAvailableTorque(MAX_TORQUE);
    conveyor->setAvailableTorque(MAX_TORQUE);
    ringClampL->setAvailableTorque(MAX_TORQUE * 10);
    ringClampR->setAvailableTorque(MAX_TORQUE * 10);
    cout << "MAINBOT: torque set" << endl;
   
    // ACCELERATION
    // drivetrain
    left1->setAcceleration(ACCELERATION);
    left2->setAcceleration(ACCELERATION);
    left3->setAcceleration(ACCELERATION);
    right1->setAcceleration(ACCELERATION);
    right2->setAcceleration(ACCELERATION);
    right3->setAcceleration(ACCELERATION);
  
    // other motors/pneumatics
    Hook->setAcceleration(ACCELERATION * 10);
    topRingArm->setAcceleration(ACCELERATION * 10);
    intakeHold->setAcceleration(ACCELERATION * 10);
    intakeRoll->setAcceleration(ACCELERATION / 2);
    conveyor->setAcceleration(ACCELERATION);
    ringClampL->setAcceleration(ACCELERATION);
    ringClampR->setAcceleration(ACCELERATION);
    cout << "MAINBOT: acceleration set" << endl;
    
    // FORCE FEEDBACK
    // drivetrain
    left1->enableForceFeedback(TIME_STEP);
    left2->enableForceFeedback(TIME_STEP);
    left3->enableForceFeedback(TIME_STEP);
    right1->enableForceFeedback(TIME_STEP);
    right2->enableForceFeedback(TIME_STEP);
    right3->enableForceFeedback(TIME_STEP);
    
    // other motors/pneumatics
    Hook->enableForceFeedback(TIME_STEP);
    topRingArm->enableForceFeedback(TIME_STEP);
    intakeHold->enableForceFeedback(TIME_STEP);
    intakeRoll->enableForceFeedback(TIME_STEP);
    ringClampL->enableForceFeedback(TIME_STEP);
    ringClampR->enableForceFeedback(TIME_STEP);
    
    // OTHERS
    receiv->enable(TIME_STEP);
    receiv->setChannel(CHANNEL_NUMBER);
    emit->setChannel(CHANNEL_NUMBER);
    emit->setRange(RANGE);
    invisVision->enable(TIME_STEP);
    invisVision->recognitionEnable(TIME_STEP);
    yes->enable(TIME_STEP);
    isGoalHere->enable(TIME_STEP);
    isGoalHere->recognitionEnable(TIME_STEP);
    isRingHere->enable(TIME_STEP);
    isRingHere->recognitionEnable(TIME_STEP);
  }
  
  // delay the program
  void delay (double time, const char* unit) {
    if (unit == "msec") {
      time = time * 0.001;
    }
    float current_time_1 = float(robot->getTime());
    float current_time_2= float(robot->getTime());
    do {
      current_time_2 = float(robot->getTime());
      robot->step(1);
    } while(current_time_2 < (current_time_1 + time));
  }
  
  // send a message through the radio
  void sendMessage(const void* message, int size) {
    emit->send(message, size);
    cout << "MAINBOT: sending message" << endl;
  }
  
  // check for a message in the radio
  void receive() {
    if (receiv->getQueueLength() <= 1) {
      message1 = static_cast<const char *>(receiv->getData());
      //cout << "MAINBOT: received: " << message1 << endl;
    } else {
      //cout << "MAINBOT: no messages received" << endl;
    }
  }
  
  // move the robot in a specified direction
  void moveBot(int direction) {
    if (direction == 0) {
      left1->setVelocity(0);
      left2->setVelocity(0);
      left3->setVelocity(0);
      right1->setVelocity(0);
      right2->setVelocity(0);
      right3->setVelocity(0);
    } else if (direction == 1) {
      left1->setVelocity(10);
      left2->setVelocity(10);
      left3->setVelocity(10);
      right1->setVelocity(-10);
      right2->setVelocity(-10);
      right3->setVelocity(-10);
    } else if (direction == 2) {
      left1->setVelocity(-10);
      left2->setVelocity(-10);
      left3->setVelocity(-10);
      right1->setVelocity(10);
      right2->setVelocity(10);
      right3->setVelocity(10);
    } else if (direction == 3) {
      left1->setVelocity(10);
      left2->setVelocity(10);
      left3->setVelocity(10);
      right1->setVelocity(10);
      right2->setVelocity(10);
      right3->setVelocity(10);
    } else if (direction == 4) {
      left1->setVelocity(-10);
      left2->setVelocity(-10);
      left3->setVelocity(-10);
      right1->setVelocity(-10);
      right2->setVelocity(-10);
      right3->setVelocity(-10);
    }
  }
  
  // reset the simulator manually
  void resetSimManual() {
    reset.resetBot(0.1, 1.34, 0.035, 0, 1, 0, 0);
    reset.resetRed();
    reset.resetYellow();
    reset.resetBlue();
  }
};
