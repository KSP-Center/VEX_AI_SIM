#include "include/libraries.h"
// main robot
Supervisor *robot = new Supervisor();

// drivetrain motors
Motor *left1 = robot->getMotor("left1");
Motor *left2 = robot->getMotor("left2");
Motor *left3 = robot->getMotor("left3");
Motor *right1 = robot->getMotor("right1");
Motor *right2 = robot->getMotor("right2");
Motor *right3 = robot->getMotor("right3");

// other motors/pneumatics
Motor *Hook = robot->getMotor("hookPneumatic");
Motor *topRingArm = robot->getMotor("topRingArm");
Motor *intakeHold = robot->getMotor("intakeHold");
Motor *intakeRoll = robot->getMotor("intakeRoll");
Motor *conveyor = robot->getMotor("conveyor");
Motor *ringClampL = robot->getMotor("ringClampL");
Motor *ringClampR = robot->getMotor("ringClampR");

// other deivces
Emitter *emit = robot->getEmitter("emit");
Receiver *receiv = robot->getReceiver("receiv");
Camera *invisVision = robot->getCamera("invisVision");
GPS *yes = robot->getGPS("yes");

// nodes
// robot and goals
Node *mainBotNode = robot->getFromDef("mainBot");
Node *goalNode1 = robot->getFromDef("goal1");
Node *goalNode2 = robot->getFromDef("goal2");
Node *goalNode3 = robot->getFromDef("goal3");
Node *goalNode4 = robot->getFromDef("goal4");
Node *goalNode5 = robot->getFromDef("goal5");

// rings
// red rings
Node *redRing1 = robot->getFromDef("redRing1");
Node *redRing2 = robot->getFromDef("redRing2");
Node *redRing3 = robot->getFromDef("redRing3");
Node *redRing4 = robot->getFromDef("redRing4");
Node *redRing5 = robot->getFromDef("redRing5");
Node *redRing6 = robot->getFromDef("redRing6");
Node *redRing7 = robot->getFromDef("redRing7");
Node *redRing8 = robot->getFromDef("redRing8");
Node *redRing9 = robot->getFromDef("redRing9");
Node *redRing10 = robot->getFromDef("redRing10");
Node *redRing11 = robot->getFromDef("redRing11");
Node *redRing12 = robot->getFromDef("redRing12");
Node *redRing13 = robot->getFromDef("redRing13");
Node *redRing14 = robot->getFromDef("redRing14");
Node *redRing15 = robot->getFromDef("redRing15");
Node *redRing16 = robot->getFromDef("redRing16");
Node *redRing17 = robot->getFromDef("redRing17");
Node *redRing18 = robot->getFromDef("redRing18");
Node *redRing19 = robot->getFromDef("redRing19");
Node *redRing20 = robot->getFromDef("redRing20");
Node *redRing21 = robot->getFromDef("redRing21");
Node *redRing22 = robot->getFromDef("redRing22");
Node *redRing23 = robot->getFromDef("redRing23");

// blue rings
Node *blueRing1 = robot->getFromDef("blueRing1");
Node *blueRing2 = robot->getFromDef("blueRing2");
Node *blueRing3 = robot->getFromDef("blueRing3");
Node *blueRing4 = robot->getFromDef("blueRing4");
Node *blueRing5 = robot->getFromDef("blueRing5");
Node *blueRing6 = robot->getFromDef("blueRing6");
Node *blueRing7 = robot->getFromDef("blueRing7");
Node *blueRing8 = robot->getFromDef("blueRing8");
Node *blueRing9 = robot->getFromDef("blueRing9");
Node *blueRing10 = robot->getFromDef("blueRing10");

// fields
// robot and goals
Field *translateFieldBot = mainBotNode->getField("translation");
Field *rotateFieldBot = mainBotNode->getField("rotation");
Field *translateGoal1 = goalNode1->getField("translation");
Field *translateGoal2 = goalNode2->getField("translation");
Field *translateGoal3 = goalNode3->getField("translation");
Field *translateGoal4 = goalNode4->getField("translation");
Field *translateGoal5 = goalNode5->getField("translation");

// rings
// red rings
Field *translateRedRing1 = redRing1->getField("translation");
Field *translateRedRing2 = redRing2->getField("translation");
Field *translateRedRing3 = redRing3->getField("translation");
Field *translateRedRing4 = redRing4->getField("translation");
Field *translateRedRing5 = redRing5->getField("translation");
Field *translateRedRing6 = redRing6->getField("translation");
Field *translateRedRing7 = redRing7->getField("translation");
Field *translateRedRing8 = redRing8->getField("translation");
Field *translateRedRing9 = redRing9->getField("translation");
Field *translateRedRing10 = redRing10->getField("translation");
Field *translateRedRing11 = redRing11->getField("translation");
Field *translateRedRing12 = redRing12->getField("translation");
Field *translateRedRing13 = redRing13->getField("translation");
Field *translateRedRing14 = redRing14->getField("translation");
Field *translateRedRing15 = redRing15->getField("translation");
Field *translateRedRing16 = redRing16->getField("translation");
Field *translateRedRing17 = redRing17->getField("translation");
Field *translateRedRing18 = redRing18->getField("translation");
Field *translateRedRing19 = redRing19->getField("translation");
Field *translateRedRing20 = redRing20->getField("translation");
Field *translateRedRing21 = redRing21->getField("translation");
Field *translateRedRing22 = redRing22->getField("translation");
Field *translateRedRing23 = redRing23->getField("translation");

// blue rings
Field *translateBlueRing1 = blueRing1->getField("translation");
Field *translateBlueRing2 = blueRing2->getField("translation");
Field *translateBlueRing3 = blueRing3->getField("translation");
Field *translateBlueRing4 = blueRing4->getField("translation");
Field *translateBlueRing5 = blueRing5->getField("translation");
Field *translateBlueRing6 = blueRing6->getField("translation");
Field *translateBlueRing7 = blueRing7->getField("translation");
Field *translateBlueRing8 = blueRing8->getField("translation");
Field *translateBlueRing9 = blueRing9->getField("translation");
Field *translateBlueRing10 = blueRing10->getField("translation");