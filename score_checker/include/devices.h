// library for devices
#include "include/libraries.h"

// MAIN BOT
Robot *score_checker = new Robot();

// EMITTER AND RECEIVER
Emitter *emit1 = score_checker->getEmitter("emit1");
Receiver *receiv1 = score_checker->getReceiver("receiv1");

// CAMERAS
// cameras for moveable goals
Camera *moveGoal1 = score_checker->getCamera("moveGoal1");
Camera *moveGoal2 = score_checker->getCamera("moveGoal2");
Camera *moveGoal3 = score_checker->getCamera("moveGoal3");
Camera *moveGoal4 = score_checker->getCamera("moveGoal4");
Camera *moveGoal5 = score_checker->getCamera("moveGoal5");

// CONNECTORS
// connectors for cameras
Connector *connect1 = score_checker->getConnector("connect1");
Connector *connect2 = score_checker->getConnector("connect2");
Connector *connect3 = score_checker->getConnector("connect3");
Connector *connect4 = score_checker->getConnector("connect4");
Connector *connect5 = score_checker->getConnector("connect5");