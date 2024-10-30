// library for sim functions
#include "include/simFunctions.cpp"

// create the sim class
Sim sim;

class Bot{
private:
  double currentScore;
  bool training = true;
  int currentTerm = 25;
  int previousTerm = 0;
  bool E_NEW_NET = true;
public:
  const void* message = " ";
  double functionOutput;

  // activate or deactivate the hook
  void hook(bool activated) {
    if (activated == true) {
      Hook->setPosition(0.2);
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
    } else {
      conveyor->setVelocity(0);
    }
  }
  
  // training functions for network
  void trainingNetwork(NeuralNetwork& actor, NeuralNetwork& critic, int numEpisodes, double gamma, double learningRate, double GRADIENT_CLASH_THRESHOLD, double weight_decay) {
    // initialize variables
    vector<double> state;
    double input1;
    double input2;
    double input3;
    int extraReward;
    int runCount;
    
    AdamWOptimizer actorOptimizer(learningRate, 0.9, 0.999, 0.01, weight_decay);
    AdamWOptimizer criticOptimizer(learningRate, 0.9, 0.999, 0.01, weight_decay);
    
    actor.add_layer(Layer(3, 128, "relu", actorOptimizer));
    actor.add_layer(Layer(128, 128, "relu", actorOptimizer));
    actor.add_layer(Layer(128, 1, "linear", actorOptimizer));
    
    critic.add_layer(Layer(3, 128, "relu", criticOptimizer));
    critic.add_layer(Layer(128, 128, "relu", criticOptimizer));
    critic.add_layer(Layer(128, 1, "linear", criticOptimizer));
    
    if(E_NEW_NET == 1) {
        // Save neural network to file
        actor.save("actor_network_params.txt");
        critic.save("critic_network_params.txt");
    }
    
    for (int episode = 0; episode <= numEpisodes; ++episode) {
      // Load neural network from file
      NeuralNetwork actorLoadedNN;
      NeuralNetwork criticLoadedNN;
      actorLoadedNN.load("actor_network_params.txt");
      criticLoadedNN.load("critic_network_params.txt");
      
      actor = actorLoadedNN;
      critic = criticLoadedNN;
      
      fstream AIshots("ai_rec.html");
    
      vector<vector<double>> states;
      vector<double> actions, rewards, logProbs, values;
      
      if (left1->getVelocity() != 0.0) {
        sim.moveBot(0);
        sim.delay(50, "msec");
      }
      sim.resetSimManual();
      sim.programSetup();
      robot->animationStartRecording("ai_rec.html");
      training = true;
      while (training == true) {
        runCount = runCount + 1;
      
        // average velocities, and insert into array
        input1 = (left1->getVelocity() + left2->getVelocity() + left3->getVelocity()) / 3;
        input2 = (right1->getVelocity() + right2->getVelocity() + right3->getVelocity()) / 3;
        input3 = currentScore;
        
        // erase the vector, and insert the array
        state.assign({input1, input2, input3});
        states.push_back(state);
        
        vector<vector<double>> actionProbs = actor.forward({state});
        
        vector<vector<double>> valueEstimates = critic.forward({state});

        values.push_back(valueEstimates[0][0]);        
                
        sim.delay(64, "msec");
      
        double action = actionProbs[0][0];
        logProbs.push_back(log(max(actionProbs[0][action], 1e-8)));
        
        if (action > 0) {
          functionOutput = action * 10;
        } else if (action < 0) {
          functionOutput = action * -10;
        }
        
        if (functionOutput > 1) {
          functionOutput = functionOutput / 30;
        }
        
        cout << "MAINBOT: functionOutput = " << functionOutput << endl;
        functionConvert(functionOutput);
        
        if (left1->getVelocity() >= 0.1) {
          extraReward = extraReward + 20;
        }
        
        if (left1->getAcceleration() >= 0.01) {
          extraReward = extraReward + 3;
        }
                
        if (invisVision->getRecognitionNumberOfObjects() > 0) {
          extraReward = extraReward + (invisVision->getRecognitionNumberOfObjects() * 3);
        }
        
        if (left1->getVelocity() >= 0 && right1->getVelocity() <= 0) {
          extraReward = extraReward + 15;
        } else if (left1->getVelocity() <= 0 && right1->getVelocity() >= 0) {
          extraReward = extraReward + 20;
        }
        
        if (topRingArm->getTargetPosition() > 0) {
          extraReward = extraReward + 10;
        }
        
        if (intakeHold->getTargetPosition() > 0) {
          extraReward = extraReward + 10;
        }
        
        if (yes->getSpeed() <= 0.05) {
          extraReward = extraReward / 3;
        }
        
        sim.receive();
        if (receiv->getQueueLength() >= 1) {
          message = receiv->getData();
          currentScore = *(double *)message;
          rewards.push_back(input1 + input2 + input3 + extraReward);
          receiv->nextPacket();
        }
        
        if (robot->getTime() >= currentTerm) {
          training = false;
          previousTerm = currentTerm;
          currentTerm = currentTerm + 25;
          extraReward = 0;
          
          actor.save("actor_network_params.txt");
          critic.save("critic_network_params.txt");
        }
      }
      
      vector<double> advantages;
    for (int t = 0; t < rewards.size(); ++t) {
      double td_target = rewards[t] + (t < rewards.size() - 1 ? gamma * values[t + 1] : 0.0);
      advantages.push_back(td_target - values[t]);
    }
    
    if (episode == numEpisodes) {
      robot->animationStopRecording();
    }
      
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
    double loss = -0.005;
    for (int i = 0; i < logProbs.size(); ++ i) {
      loss -= logProbs[i] * advantages[i];
    }
    return loss;
  }
  
  void functionConvert(double functionID) {
    if (functionID >= -0.1 && functionID <= 0.1) {
      sim.moveBot(0);
    } else if (functionID >= 0.1 && functionID <= 0.2) {
      sim.moveBot(1);
    } else if (functionID >= 0.2 && functionID <= 0.3) {
      sim.moveBot(2);
    } else if (functionID >= 0.3 && functionID <= 0.4) {
      sim.moveBot(3);
    } else if (functionID >= 0.4 && functionID <= 0.5) {
      sim.moveBot(4);
    } else {
      sim.moveBot(0);
    }
    
    if (functionID >= 0.5 && functionID <= 0.6) {
      hook(true);
    } else if (functionID >= 0.6 && functionID <= 0.7) {
      hook(false);
    } else if (functionID >= 0.7 && functionID <= 0.8) {
      topArm(true);
    } else if (functionID >= 0.8 && functionID <= 0.9) {
      topArm(false);
    }
  }
};