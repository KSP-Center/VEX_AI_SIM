#include "include/robotFunctions.cpp"

Bot bot;

class Test{
private:
  
public:
  int systemsTest() {
    int errorCode;
    
    /* error code list
      
      error 1: lifting upper arm failed
      error 2: lowering upper arm failed
      error 3: upper arm device not found
      error 4: intake holder activation failed
      error 5: intake holder deactivation failed
      error 6: intake holder device not found
      error 7: spinning intake failed
      error 8: stopping intake failed
      error 9: intake device not found
      error 10: ring clamp activation failed
      error 11: ring clamp deactivation failed
      error 12: ring clamp device(s) not found
      error 13: wing activation failed
      error 14: wing deactivation failed
      error 15: wing device not found
      
      conveyor stuff
      
      error 16: sending on emitter failed
      error 17: receiving on receiver failed
      error 18: emitter device not found
      error 19: receiver device not found
      error 20: hook activation failed
      error 21: hook deactivation failed
      error 22: hook device not found
      error 23: drive forward command failed
      error 24: drive backward command failed
      error 25: turn left command failed
      error 26: turn right command failed
      error 27: a left-drive device not found
      error 28: a right-drive device not found
    
    */
    
    cout << "MAINBOT: system test script start" << endl;
    errorCode = isTopArmGood();
    outputError(errorCode);
    errorCode = isHolderGood();
    outputError(errorCode);
    errorCode = isIntakeGood();
    outputError(errorCode);
    errorCode = isRingClampGood();
    outputError(errorCode);
    errorCode = isEmitterGood();
    outputError(errorCode);
    errorCode = isReceiverGood();
    outputError(errorCode);
    errorCode = isHookGood();
    outputError(errorCode);
    errorCode = isDrivetrainGood();
    outputError(errorCode);
    cout << "MAINBOT: system test script end, tests successful" << endl;
    sim.delay(1, "sec");
    
    return errorCode;
  }
  
  void outputError(int errorID) {
    if (errorID != NULL) {
      cout << "TESTER: warning: system fault, error code " << errorID << endl;
      sim.delay(9999, "sec");
    } else {
      sim.delay(1, "sec");
    }
  }
  
  int isTopArmGood() {
    int errorCode;
    if (robot->getFromDef("topRingArm") != NULL) {
      bot.topArm(true);
      cout << "TESTER: top arm activation signal sent" << endl;
      if (topRingArm->getAcceleration() > 0) {
        sim.delay(1, "sec");
        bot.topArm(false);
        cout << "TESTER: top arm deactivation signal sent" << endl;
        if (topRingArm->getAcceleration() > 0) {
          errorCode = NULL;
          sim.delay(1, "sec");
          cout << "TESTER: top arm is good" << endl;
        } else {
          errorCode = 2;
        }
      } else {
        errorCode = 1;
      }
    } else {
      errorCode = 3;
    }
    
    return errorCode;
  }
  
  int isHolderGood() {
    int errorCode;
    if (robot->getFromDef("intakeHold") != NULL) {
      bot.holder(true);
      cout << "TESTER: intake holder activation signal sent" << endl;
      if (intakeHold->getTargetPosition() < 0) {
        sim.delay(1, "sec");
        bot.holder(false);
        cout << "TESTER: intake holder deactivation signal sent" << endl;
        if (intakeHold->getTargetPosition() == 0) {
          errorCode = NULL;
          sim.delay(1, "sec");
          cout << "TESTER: intake holder is good" << endl;
        } else {
          errorCode = 5;
        }
      } else {
        errorCode = 4;
      }
    } else {
      errorCode = 6;
    }
    
    return errorCode;
  }
  
  int isIntakeGood() {
    int errorCode;
    if (robot->getFromDef("intakeRoll") != NULL) {
      bot.intake(true);
      cout << "TESTER: intake roller activation signal sent" << endl;
      if (intakeRoll->getAcceleration() > 0) {
        sim.delay(1, "sec");
        bot.intake(false);
        cout << "TESTER: intake roller deactivation signal sent" << endl;
        if (intakeRoll->getAcceleration() > 0) {
          errorCode = NULL;
          sim.delay(1, "sec");
          cout << "TESTER: intake roller is good" << endl;
        } else {
          errorCode = 8;
        }
      } else {
        errorCode = 7;
      }
    } else {
      errorCode = 9;
    }
    
    return errorCode;
  }
  
  int isRingClampGood() {
    int errorCode;
    if (robot->getFromDef("ringClampL") != NULL) {
      bot.clamp(true);
      cout << "TESTER: ring clamp activation signal sent" << endl;
      if (ringClampL->getAcceleration() > 0 && ringClampR->getAcceleration() > 0) {
        sim.delay(1, "sec");
        bot.clamp(false);
        cout << "TESTER: ring clamp deactivation signal sent" << endl;
        if (ringClampL->getAcceleration() > 0 && ringClampR->getAcceleration() > 0) {
          errorCode = NULL;
          sim.delay(1, "sec");
          cout << "TESTER: ring clamp is good" << endl;
        } else {
          errorCode = 11;
        }
      } else {
        errorCode = 10;
      }
    } else {
      errorCode = 12;
    }
    
    return errorCode;
  }
  
  int isWingGood() {
    int errorCode;
    
    return errorCode;
  }
  
  int isConveyorGood() {
    int errorCode;
    if (robot->getFromDef("conveyor") != NULL) {
      bot.Conveyor(true);
      cout << "TESTER: conveyor activation signal sent" << endl;
      if (conveyor->getAcceleration() > 0) {
        sim.delay(1, "sec");
        bot.Conveyor(false);
        cout << "TESTER: conveyor deactivation signal sent" << endl;
        if (conveyor->getAcceleration() > 0) {
          errorCode = NULL;
          sim.delay(1, "sec");
          cout << "TESTER: conveyor is good" << endl;
        } else {
          errorCode = 14;
        }
      } else {
        errorCode = 13;
      }
    } else {
      errorCode = 15;
    }
    
    return errorCode;
  }
  
  int isEmitterGood() {
    int errorCode;
    const char* yes = "systemTest";
    if (robot->getFromDef("emit") != NULL) {
      sim.sendMessage(yes, strlen(yes) + 1);
      cout << "TESTER: testing emitter" << endl;
      if (emit->getChannel() == 0) {
        errorCode = NULL;
        sim.delay(1, "sec");
        cout << "TESTER: emitter is good" << endl;
      } else {
        errorCode = 16;
      }
    } else {
      errorCode = 18;
    }
    
    return errorCode;
  }
  
  int isReceiverGood() {
    int errorCode;
    if (robot->getFromDef("receiv") != NULL) {
      sim.receive();
      cout << "TESTER: testing receiver" << endl;
      if (receiv->getQueueLength() > 0) {
        errorCode = NULL;
        sim.delay(1, "sec");
        cout << "TESTER: receiver is good" << endl;
      } else {
        errorCode = 17;
      }
    } else {
      errorCode = 19;
    }
    
    return errorCode;
  }
  
  int isHookGood() {
    int errorCode;
    if (robot->getFromDef("Hook") != NULL) {
      bot.hook(true);
      cout << "TESTER: clamp activation signal sent" << endl;
      if (Hook->getTargetPosition() > 0) {
        sim.delay(1, "sec");
        bot.hook(false);
        cout << "TESTER: clamp deactivation signal sent" << endl;
        if (Hook->getTargetPosition() == 0) {
          errorCode = NULL;
          sim.delay(1, "sec");
          cout << "TESTER: clamp is good" << endl;
        } else {
          errorCode = 21;
        }
      } else {
        errorCode = 20;
      }
    } else {
      errorCode = 22;
    }
    
    return errorCode;
  }
  
  int isDrivetrainGood() {
    int errorCode;
    if (robot->getFromDef("left1") != NULL && robot->getFromDef("left2") != NULL && robot->getFromDef("left3") != NULL) {
      if (robot->getFromDef("right1") != NULL && robot->getFromDef("right2") != NULL && robot->getFromDef("right3") != NULL) {
        sim.moveBot(1);
        cout << "TESTER: drivetrain forward command sent" << endl;
        if (left1->getAcceleration() > 0 && right1->getAcceleration() > 0) {
          sim.delay(1, "sec");
          sim.moveBot(2);
          cout << "TESTER: drivetrain reverse command sent" << endl;
          sim.delay(50, "msec");
          if (left1->getAcceleration() > 0 && right1->getAcceleration() > 0) {
            sim.delay(1, "sec");
            sim.moveBot(3);
            cout << "TESTER: drivetrain left command sent" << endl;
            sim.delay(50, "msec");
            if (left1->getAcceleration() > 0) {
              sim.delay(1, "sec");
              sim.moveBot(4);
              cout << "TESTER: drivetrain right command sent" << endl;
              sim.delay(50, "msec");
              if (right1->getAcceleration() > 0) {
                errorCode = NULL;
                sim.delay(1, "sec");
                cout << "TESTER: drivetrain is good" << endl;
                sim.moveBot(0);
              } else {
                errorCode = 26;
              }
            } else {
              errorCode = 25;
            }
          } else {
            errorCode = 24;
          }
        } else {
          errorCode = 23;
        }
      } else {
        errorCode = 28;
      }
    } else {
      errorCode = 27;
    }
  
    return errorCode;
  }
};