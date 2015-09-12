#include <Sabertooth.h>

//Heavily stripped down and modified version of James Starkman's code which controlled the NASA robot in the May, 2014 competition

/*
 * Task:
 * Implement commands 0-5, 15-17 in code that could be run on an arduino. 
 * You are outputting these commands over serial to a wire that is connected to the motor controller. 
 * Assume defaults or make up reasonable values for missing information. 
 * (eg pick any valid motor address, and use baud rate 9600)
 * 
 * If time/interest permits, write some code that has addresses for 4 motors. 
 * Then make commands that turn the two motors on the right faster than the ones on the 
 * left to execute a curving left turn, and make one for right turn etc. Think about making 
 * controls that a person with a joystick could input, and/or functions that take direction 
 * like a computer would give them (vector[angle for direction,magnitude for velocity)
 */
int motorOneAddress = 128;
int motorTwoAddress = 129;
int motor1Pin = 25;

Sabertooth ST1(motorOneAddress);
Sabertooth ST2(motorTwoAddress);

//this runs once as soon as the arduino is turned on
void setup(){
  SabertoothTXPinSerial.begin(9600);
  pinMode(motor1Pin, OUTPUT);
  ST1.autobaud(); //sets the baud rate
  ST1.setMinVoltage(0); //sets min voltage
  ST1.setMaxVoltage(128); //sets max voltage
  ST1.setDeadband(0); //sets the deadband
  ST1.setRamping(26); //sets the ramp speed (full backwards to full forwards). value of 26 is about 1 second.
}

//the code in here gets run oveer and over again until the arduino is turned off
void loop(){
    //write code here to send all the commands you implement once
    ST1.drive(64); //tells both motor 1 and motor 2 to go forward
    delay(500);
    ST1.drive(-64);//tells both motor 1 and motor 2 to go backwards
    delay(500);
}


