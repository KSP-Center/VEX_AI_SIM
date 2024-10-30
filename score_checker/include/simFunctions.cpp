#define CHANNEL_NUMBER 0.0
#define RANGE 999.9

class Sim{
private:
  const void* message1 = " ";
  int yes = 0;

public:
  // setup the bot
  int programSetup() {
    // CAMERAS
    // enable actual sensor
    moveGoal1->enable(TIME_STEP);
    moveGoal2->enable(TIME_STEP);
    moveGoal3->enable(TIME_STEP);
    moveGoal4->enable(TIME_STEP);
    moveGoal5->enable(TIME_STEP);

    // turn on recognition
    moveGoal1->recognitionEnable(TIME_STEP);
    moveGoal2->recognitionEnable(TIME_STEP);
    moveGoal3->recognitionEnable(TIME_STEP);
    moveGoal4->recognitionEnable(TIME_STEP);
    moveGoal5->recognitionEnable(TIME_STEP);

    // CONNECTORS
    connect1->enablePresence(TIME_STEP);
    connect2->enablePresence(TIME_STEP);
    connect3->enablePresence(TIME_STEP);
    connect4->enablePresence(TIME_STEP);
    connect5->enablePresence(TIME_STEP);
    
    // EMITTER AND RECEIVER
    receiv1->enable(TIME_STEP);
    receiv1->setChannel(CHANNEL_NUMBER);
    emit1->setChannel(CHANNEL_NUMBER);
    emit1->setRange(RANGE);
    
    return 0;
  }
  
  // delay the program
  int delay (double time, const char* unit) {
    if (unit == "msec") {
      time = time * 0.001;
    }
    float current_time_1 = float(score_checker->getTime());
    float current_time_2= float(score_checker->getTime());
    do {
      current_time_2 = float(score_checker->getTime());
      score_checker->step(1);
    } while(current_time_2 < (current_time_1 + time));
    
    return 0;
  }
  
  // send a message through the radio
  int sendMessage(const void* data, int size) {
    emit1->send(data, size);
    //cout << "SCORE: sending message" << endl;
    
    return 0;
  }
  
  // check for a message through the radio
  int receive() {
    if (receiv1->getQueueLength() != 0) {
      message1 = static_cast<const char *>(receiv1->getData());
      //cout << "SCORE: received: " << message1 << endl;
    } else {
      //cout << "SCORE: no messages received" << endl;
    }
    
    return 0;
  }
  
  // dismiss the message if called
  int dismissMessage() {
    receiv1->nextPacket();
    
    return 0;
  }
};