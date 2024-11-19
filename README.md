# VEX_AI_SIM Intro
*AI code written for VEX Robotics team 7686X "Phoenix Rising" using robotic simulator Webots*

This repository contains the code written by two shopomores in high school for the VEX Robotics Team 7686X, aka "Phoenix Rising."
Its main purpose is to write and train an AI into completing the best skills run for robotics it can produce.
In its current written form (on 11-18-24), it contains 21 input neurons and 7 output neurons.
It also contains 128 other neurons to comprise the main AI, with a total neuron count of 146.
The neural netowrk ('nn' for short) learns by varying values of the output until it meets the tasks setup.
If a task is complete, it is rewarded, telling the AI to focus on those values primaraly.
However, if it does something we dont want it to do, the reward counter is reduced.

# What software do you use for the simualtor?
We use a simulator called Webots.
It's a open source, 3D robotics simulator first brought up in 1996, of which became a OG software in 1998.
Since then, it has ran under the cooperation Cyberbotics Ltd.
Cyberbotics provides its own API, and contains the functions and settings of the world defined "Nodes".

# What language does this 'Webots' use?
Webots itself uses a vararity of different coding languages.
It covers the most popular ones, like Python and Java.
But, it also covers C++, MATLAB, and ROS.

# How do I impement this into my own simulator?
Easy said, and somewhat easy done as well.
First, you need to create a controller inside a new world in either the Webots IDE or VS.
Once thats done, all you need to do is copy the files into the controller.

NOTE: This repository DOES NOT contain the actual world file used, so you will have to make the world file yourself.
It is also written in C++.
