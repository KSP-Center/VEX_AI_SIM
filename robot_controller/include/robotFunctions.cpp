// library for sim functions
#include "include/simFunctions.cpp"

// create classes
Sim sim;
Rewards rewar;

class Bot{
private:
  double currentScore;
  bool training = true;
  int currentTerm = 25;
  int previousTerm = 0;
  bool isTime;
  bool E_NEW_NET = false;
  
  // hook starting positions
  int hookPositions[4] = {1, 18, 35, 52};
    
  // hook starting rotation
  int hookRotations[4] = {1, 1, 4, 4};
    
  // preset selector
  int positionPresetSelector = 0;
  int rotatePresetSelector = 0;
public:
  const void* message = " ";
  double functionOutput;

  // activate or deactivate the hook
  void hook(bool activated) {
    if (activated == true) {
      Hook->setPosition(0.46);
    } else {
      Hook->setPosition(0);
    }
  }
  
  void topArm(bool activated) {
    if (activated == true) {
      topRingArm->setPosition(-1.2);
    } else {
      topRingArm->setPosition(0);
    }
  }
  
  void holder(bool activated) {
    if (activated == true) {
      intakeHold->setPosition(-0.5);
    } else {
      intakeHold->setPosition(0);
    }
  }
  
  void clamp(bool activated) {
    if (activated == true) {
      ringClampL->setPosition(0.3);
      ringClampR->setPosition(0.3);
    } else {
      ringClampL->setPosition(-0.3);
      ringClampR->setPosition(-0.3);
    }
  }
  
  void intake(bool spinning) {
    if (spinning == true) {
      intakeRoll->setVelocity(-100.0);
    } else {
      intakeRoll->setVelocity(0);
    }
  }
  
  void Conveyor(bool spinning) {
    if (spinning == true) {
      conveyor->setVelocity(-10.0);
      if (isTime == 1) {
        updateConveyorPosition(true);
        isTime = 0;
        sim.delay(5, "msec");
      } else if (isTime == 0) {
        isTime = 1;
      }
    } else {
      conveyor->setVelocity(0);
      updateConveyorPosition(false);
    }
  }
  
  // training functions for network
  void trainingNetwork(NeuralNetwork& actor, NeuralNetwork& critic, int numEpisodes, double gamma, double learningRate, double GRADIENT_CLASH_THRESHOLD, double weight_decay) {
    // initialize variables
    vector<double> state;
    int extraReward = 0;
    int runCount = 0;
    
    AdamWOptimizer actorOptimizer(learningRate, 0.9, 0.999, 0.01, weight_decay);
    AdamWOptimizer criticOptimizer(learningRate, 0.9, 0.999, 0.01, weight_decay);
    
    actor.add_layer(Layer(21, 64, "relu", actorOptimizer));
    actor.add_layer(Layer(64, 64, "relu", actorOptimizer));
    actor.add_layer(Layer(64, 7, "linear", actorOptimizer));
    
    critic.add_layer(Layer(21, 64, "relu", criticOptimizer));
    critic.add_layer(Layer(64, 64, "relu", criticOptimizer));
    critic.add_layer(Layer(64, 7, "linear", criticOptimizer));
    
    double driveIN[4] = {0.0, 0.0, 0.0, 0.0};
    double pneuIN[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double otherIN[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    unsigned int time_elpased_millis = 0;
    std::string training_objective;
    double episode_reward;
    
    if (E_NEW_NET == 1) {
        // Save neural network to file
        actor.save("actor_network_params.txt");
        critic.save("critic_network_params.txt");
    }
    
    for (int episode = 0; episode <= numEpisodes; ++episode) {
      // Load neural network from file
      if (E_NEW_NET) {
        NeuralNetwork actorLoadedNN;
        NeuralNetwork criticLoadedNN;
        actorLoadedNN.load("actor_network_params.txt");
        criticLoadedNN.load("critic_network_params.txt");
      
        actor = actorLoadedNN;
        critic = criticLoadedNN;
      }
      
      //fstream AIshots("ai_rec.html");
    
      vector<vector<double>> states;
      vector<double> actions, rewards, logProbs, values;
      
      sim.moveBot(0);
      hook(false);
      topArm(false);
      holder(false);
      clamp(false);
      intake(false);
      Conveyor(false);
      
      sim.resetSimManual();
      //robot->animationStartRecording("ai_rec.html");
      training = true;
      cout << "run number " << runCount << endl;
      while (training == true) {
        runCount = runCount + 1;
      
        // assign input values
        driveIN[0] = (left1->getVelocity() + left2->getVelocity() + left3->getVelocity()) / 3;
        driveIN[1] = (right1->getVelocity() + right2->getVelocity() + right3->getVelocity()) / 3;
        driveIN[2] = (left1->getForceFeedback() + left2->getForceFeedback() + left3->getForceFeedback()) / 3;
        driveIN[3] = (right1->getForceFeedback() + right2->getForceFeedback() + right3->getForceFeedback()) / 3;
        pneuIN[0] = topRingArm->getTargetPosition();
        pneuIN[1] = topRingArm->getAcceleration();
        pneuIN[2] = topRingArm->getForceFeedback();
        pneuIN[3] = Hook->getTargetPosition();
        pneuIN[4] = Hook->getAcceleration();
        pneuIN[5] = Hook->getForceFeedback();
        pneuIN[6] = intakeHold->getTargetPosition();
        pneuIN[7] = intakeHold->getAcceleration();
        pneuIN[8] = intakeHold->getForceFeedback();
        pneuIN[9] = (ringClampL->getTargetPosition() + ringClampR->getTargetPosition()) / 2;
        pneuIN[10] = (ringClampL->getAcceleration() + ringClampR->getAcceleration()) / 2;
        pneuIN[11] = (ringClampL->getForceFeedback() + ringClampR->getForceFeedback()) / 2;
        otherIN[0] = intakeRoll->getVelocity();
        otherIN[1] = intakeRoll->getAcceleration();
        otherIN[2] = intakeRoll->getForceFeedback();
        otherIN[3] = static_cast<double>(isRingHere->getRecognitionNumberOfObjects());
        otherIN[4] = static_cast<double>(isGoalHere->getRecognitionNumberOfObjects());
        
        // erase the vector, and insert the array
        state.assign({driveIN[0], driveIN[1], driveIN[2], driveIN[3], pneuIN[0], pneuIN[1], pneuIN[2], pneuIN[3], pneuIN[4], pneuIN[5], pneuIN[6], pneuIN[7], pneuIN[8], pneuIN[9], pneuIN[10], pneuIN[11], otherIN[0], otherIN[1], otherIN[2], otherIN[3], otherIN[4]});
        states.push_back(state);
        
        vector<vector<double>> actionProbs = actor.forward({state});
        
        vector<vector<double>> valueEstimates = critic.forward({state});

        values.push_back(valueEstimates[0][0]);        
                
        sim.delay(64, "msec");
      
        double output[7] = {actionProbs[0][0] * -1, actionProbs[0][1], actionProbs[0][2] * -1, actionProbs[0][3] * -1, actionProbs[0][4] * -1, actionProbs[0][5] * -1, actionProbs[0][6] * -1};
        logProbs.push_back(log(max(actionProbs[0][output[0]], 1e-8)));
        
        for (int i = -1; i > 7; i++) {
          outputFunctionConvert(i, output[i]);
        }
        cout << "MAINBOT: outputs = ";
        cout << output[0] << " ";
        cout << output[1] << " ";
        cout << output[2] << " ";
        cout << output[3] << " ";
        cout << output[4] << " ";
        cout << output[5] << " ";
        cout << output[6] << endl;
        
        // basic rewards
        extraReward = extraReward + rewar.computeBasic();
        
        // complex rewards (for actual strategies)
        // extraReward = extraReward + rewar.computeComplex();
      
        rewards.push_back(driveIN[0] + driveIN[1] + driveIN[2] + driveIN[3] + pneuIN[0] + pneuIN[1] + pneuIN[2] + pneuIN[3] + pneuIN[4] + pneuIN[5] + pneuIN[6] + pneuIN[7] + pneuIN[8] + pneuIN[9] + pneuIN[10] + pneuIN[11] + otherIN[0] + otherIN[1] + otherIN[2] + otherIN[3] + otherIN[4] + extraReward);
        
        // check for if run is over
        if (robot->getTime() >= currentTerm) {
          training = false;
          previousTerm = currentTerm;
          currentTerm = currentTerm + 25;
          extraReward = 0;
          runCount = runCount + 1;
          
          if (E_NEW_NET == true) {
            actor.save("actor_network_params.txt");
            critic.save("critic_network_params.txt");
          }
        }
      }
      
      vector<double> advantages;
    for (int t = 0; t < rewards.size(); ++t) {
      double td_target = rewards[t] + (t < rewards.size() - 1 ? gamma * values[t + 1] : 0.0);
      advantages.push_back(td_target - values[t]);
    }
    
    //robot->animationStopRecording();
      
    double actorLoss = computeLoss(logProbs, advantages);
      
    double criticLoss = 0.0;
    for (size_t i = 0; i < rewards.size(); ++i) {
      double td_target = rewards[i] + (i < rewards.size() - 1 ? gamma * values[i + 1] : 0.0);
      criticLoss += pow(td_target - values[i], 2);
    }
    criticLoss = rewards.size();
    
    actor.backward({{actorLoss}}, GRADIENT_CLASH_THRESHOLD);
    actor.update_weights();
    
    critic.backward({{criticLoss}}, GRADIENT_CLASH_THRESHOLD);
    critic.update_weights();
    }
      
  }
  
  double computeLoss(const vector<double>& logProbs, const vector<double>& advantages) {
    double loss = 0.0;
    for (int i = 0; i < logProbs.size(); ++ i) {
      loss -= logProbs[i] * advantages[i];
    }
    return loss;
  }
  
  // convert the function output into an action (will change soon)
  void outputFunctionConvert(int outputID, double value) {
    if (outputID == 0) {
      left1->setVelocity(value);
      left2->setVelocity(value);
      left3->setVelocity(value);
    } else if (outputID == 1) {
      right1->setVelocity(value);
      right2->setVelocity(value);
      right3->setVelocity(value);
    } else if (outputID == 2) {
      if (value > 0.5 && value < 1.0) {
        topArm(true);
      } else {
        topArm(false);
      }
    } else if (outputID == 3) {
      if (value > 0.5 && value < 1.0) {
        hook(true);
      } else {
        hook(false);
      }
    } else if (outputID == 4) {
      if (value > 0.5 && value < 1.0) {
        holder(true);
      } else {
        holder(false);
      }
    } else if (outputID == 5) {
      if (value > 0.5 && value < 1.0) {
        clamp(true);
      } else {
        clamp(false);
      }
    } else if (outputID == 6) {
      if (value > 0.5 && value < 1.0) {
        intake(true);
      } else {
        intake(true);
      }
    }
  }
  
  void updateConveyorPosition(bool add1) {
    if (add1 == true) {
      // move hook1 up a spot
      positionPresetSelector = hookPositions[0] + 1;
      logPresetPosition(positionPresetSelector, 1);
      hookPositions[0] = positionPresetSelector;
      
      // move hook2 up a spot
      positionPresetSelector = hookPositions[1] + 1;
      logPresetPosition(positionPresetSelector, 2);
      hookPositions[1] = positionPresetSelector;
      
      // move hook3 up a spot
      positionPresetSelector = hookPositions[2] + 1;
      logPresetPosition(positionPresetSelector, 3);
      hookPositions[2] = positionPresetSelector;
      
      // move hook4 up a spot
      positionPresetSelector = hookPositions[3] + 1;
      logPresetPosition(positionPresetSelector, 4);
      hookPositions[3] = positionPresetSelector;
      
      // check for oversized positions
      for (int i = 0; i < 4; i++) {
        if (hookPositions[i] >= 83) {
          hookPositions[i] = 1;
        }
      }
    }
  }
  
  void moveHook(float x, float y, float z, int hookID) {
    const double translateHook[3] = {x, y, z};
    if (hookID == 1) {
      moveHook1->setSFVec3f(translateHook);
    } else if (hookID == 2) {
      moveHook2->setSFVec3f(translateHook);
    } else if (hookID == 3) {
      moveHook3->setSFVec3f(translateHook);
    } else if (hookID == 4) {
      moveHook4->setSFVec3f(translateHook);
    }
  }
  
  void rotateHook(float x, float y, float z, float rad, int hookID) {
    const double rotateHook[4] = {x, y, z, rad};
    if (hookID == 1) {
      rotateHook1->setSFRotation(rotateHook);
    } else if (hookID == 2) {
      rotateHook2->setSFRotation(rotateHook);
    } else if (hookID == 3) {
      rotateHook3->setSFRotation(rotateHook);
    } else if (hookID == 4) {
      rotateHook4->setSFRotation(rotateHook);
    }
  }
  
  void logPresetPosition(int presetID, int hookID) {
    // hook position presets
    double positionPreset[83][3] = {
      {-0.01, 0.113, 0.113},
      {-0.01, 0.118, 0.122},
      {-0.01, 0.123, 0.13},
      {-0.01, 0.128, 0.139},
      {-0.01, 0.133, 0.148},
      {-0.01, 0.138, 0.157},
      {-0.01, 0.143, 0.166},
      {-0.01, 0.148, 0.175},
      {-0.01, 0.153, 0.184},
      {-0.01, 0.158, 0.193},
      {-0.01, 0.163, 0.202},
      {-0.01, 0.168, 0.211},
      {-0.01, 0.173, 0.22},
      {-0.01, 0.178, 0.229},
      {-0.01, 0.183, 0.238},
      {-0.01, 0.188, 0.247},
      {-0.01, 0.193, 0.256},
      {-0.01, 0.198, 0.265},
      {-0.01, 0.203, 0.274},
      {-0.01, 0.208, 0.283},
      {-0.01, 0.213, 0.292},
      {-0.01, 0.218, 0.301},
      {-0.01, 0.223, 0.31},
      {-0.01, 0.228, 0.319},
      {-0.01, 0.233, 0.328},
      {-0.01, 0.238, 0.337},
      {-0.01, 0.243, 0.346},
      {-0.01, 0.248, 0.355},
      {-0.01, 0.253, 0.364},
      {-0.01, 0.258, 0.373},
      {-0.01, 0.263, 0.382},
      {-0.01, 0.266, 0.385},
      {-0.01, 0.2695, 0.382},
      {-0.01, 0.273, 0.375},
      {-0.01, 0.2755, 0.3735},
      {-0.01, 0.2785, 0.372},
      {-0.01, 0.281, 0.37},
      {-0.01, 0.282, 0.366},
      {-0.01, 0.283, 0.364},
      {-0.01, 0.284, 0.361},
      {-0.01, 0.2823, 0.358},
      {-0.01, 0.2807, 0.355},
      {-0.01, 0.279, 0.352},
      {-0.01, 0.274, 0.343},
      {-0.01, 0.269, 0.334},
      {-0.01, 0.264, 0.325},
      {-0.01, 0.259, 0.316},
      {-0.01, 0.254, 0.305},
      {-0.01, 0.249, 0.296},
      {-0.01, 0.244, 0.287},
      {-0.01, 0.239, 0.278},
      {-0.01, 0.234, 0.269},
      {-0.01, 0.229, 0.26},
      {-0.01, 0.224, 0.251},
      {-0.01, 0.219, 0.242},
      {-0.01, 0.214, 0.233},
      {-0.01, 0.209, 0.224},
      {-0.01, 0.204, 0.215},
      {-0.01, 0.199, 0.206},
      {-0.01, 0.194, 0.197},
      {-0.01, 0.189, 0.188},
      {-0.01, 0.184, 0.179},
      {-0.01, 0.174, 0.161},
      {-0.01, 0.169, 0.152},
      {-0.01, 0.164, 0.143},
      {-0.01, 0.159, 0.134},
      {-0.01, 0.154, 0.125},
      {-0.01, 0.149, 0.116},
      {-0.01, 0.144, 0.107},
      {-0.01, 0.139, 0.098},
      {-0.01, 0.134, 0.089},
      {-0.01, 0.129, 0.08},
      {-0.01, 0.1255, 0.0832},
      {-0.01, 0.1225, 0.0864},
      {-0.01, 0.119, 0.0896},
      {-0.01, 0.116, 0.0903},
      {-0.01, 0.113, 0.0925},
      {-0.01, 0.11, 0.0947},
      {-0.01, 0.10925, 0.096},
      {-0.01, 0.10875, 0.098},
      {-0.01, 0.108, 0.104},
      {-0.01, 0.109, 0.107},
      {-0.01, 0.111, 0.11}
    };
    
    moveHook(positionPreset[presetID - 1][0], positionPreset[presetID - 1][1], positionPreset[presetID - 1][2], hookID);
    if (presetID == 30) {
      logPresetRotation(2, hookID);
    } else if (presetID == 31) {
      logPresetRotation(3, hookID);
    } else if (presetID == 32) {
      logPresetRotation(4, hookID);
    } else if (presetID == 33) {
      logPresetRotation(5, hookID);
    } else if (presetID == 34) {
      logPresetRotation(6, hookID);
    } else if (presetID == 35) {
      logPresetRotation(7, hookID);
    } else if (presetID == 36) {
      logPresetRotation(8, hookID);
    } else if (presetID == 37) {
      logPresetRotation(9, hookID);
    } else if (presetID == 38) {
      logPresetRotation(10, hookID);
    } else if (presetID == 39) {
      logPresetRotation(9, hookID);
    } else if (presetID == 40) {
      logPresetRotation(10, hookID);
    } else if (presetID == 41) {
      logPresetRotation(11, hookID);
    } else if (presetID == 42) {
      logPresetRotation(12, hookID);
    } else if (presetID == 43) {
      logPresetRotation(13, hookID);
    } else if (presetID == 73) {
      logPresetRotation(14, hookID);
    } else if (presetID == 74) {
      logPresetRotation(15, hookID);
    } else if (presetID == 75) {
      logPresetRotation(16, hookID);
    } else if (presetID == 76) {
      logPresetRotation(17, hookID);
    } else if (presetID == 77) {
      logPresetRotation(18, hookID);
    } else if (presetID == 78) {
      logPresetRotation(19, hookID);
    } else if (presetID == 79) {
      logPresetRotation(20, hookID);
    } else if (presetID == 80) {
      logPresetRotation(21, hookID);
    } else if (presetID == 81) {
      logPresetRotation(22, hookID);
    } else if (presetID == 82) {
      logPresetRotation(23, hookID);
    } else if (presetID == 83) {
      logPresetRotation(24, hookID);
    } else if (presetID == 1) {
      logPresetRotation(1, hookID);
    }
  }
  
  void logPresetRotation(int presetID, int hookID) {
    // hook rotation presets
    double rotationPreset[24][4] = {
      {-0.251, 0.251, 0.925, 1.64},
      {-0.36, 0.36, 0.861, 1.72},
      {-0.449, 0.449, 0.772, 1.83},
      {-0.52, 0.52, 0.678, 1.95},
      {-0.579, 0.579, 0.575, 2.1},
      {-0.623, 0.623, 0.475, 2.26},
      {-0.655, 0.655, 0.378, 2.42},
      {-0.679, 0.679, 0.279, 2.6},
      {-0.695, 0.695, 0.184, 2.78},
      {-0.704, 0.704, 0.0927, 2.96},
      {-0.707, 0.707, 0.00224, 3.14},
      {0.704, -0.704, 0.095, 2.95},
      {0.695, -0.695, 0.186, 2.77},
      {0.678, -0.678, 0.283, 2.59},
      {0.654, -0.654, 0.38, 2.41},
      {0.622, -0.622, 0.477, 2.25},
      {0.576, -0.576, 0.58, 2.09},
      {0.519, -0.519, 0.68, 1.95},
      {0.445, -0.445, 0.775, 1.82},
      {0.355, -0.355, 0.865, 1.72},
      {0.248, -0.248, 0.937, 1.64},
      {0.126, -0.126, 0.983, 1.59},
      {0, 0, -1, -1.57},
      {-0.132, 0.132, 0.982, 1.59}
    };
    rotateHook(rotationPreset[presetID - 1][0], rotationPreset[presetID - 1][1], rotationPreset[presetID - 1][2], rotationPreset[presetID - 1][3], hookID);
  }
};
