
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
int motor1Pin = 1;

int commandNumber = 1;

//this runs once as soon as the arduino is turned on
void setup(){
  Serial.begin(9600);
  pinMode(motor1Pin, OUTPUT);

}

//the code in here gets run oveer and over again until the arduino is turned off
void loop(){
      Serial.write(motorOneAddress);
      //send motor command
      Serial.write(commandNumber);
      //send motor speed
      Serial.write(32);
      //send checksum
      int check = (motorOneAddress + commandNumber + 32) & B01111111;
      Serial.write(check);

}


