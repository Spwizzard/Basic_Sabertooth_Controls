
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
int sabertooth1Pin = 1;
int conveyorButtonPin = 15;
int digWheelButtonPin = 16;
bool activateConveyor = false;
bool activateDigWheel = false;

//this runs once as soon as the arduino is turned on
void setup(){
  Serial.begin(9600); //pc connection
  pinMode(sabertooth1Pin, OUTPUT);
  pinMode(conveyorButtonPin, INPUT);
  pinMode(digWheelButtonPin, INPUT);
  setupMinMaxVoltage(motorOneAddress, 0,128); //sets Min / Max volts
  setupBaudRate(motorOneAddress, 2); //sets baud rate
  setupDeadband(motorOneAddress, 0); //sets the deadband
}

//the code in here gets run over and over again until the arduino is turned off
void loop(){
    //write code here to send all the commands you implement once
    activateButton(conveyorButtonPin, activateConveyor);
    if(activateConveyor){
      driveMotor(motorOneAddress, 1, 32);
    }
    else{
      driveMotor(motorOneAddress, 1, 0);
    }
    activateButton(digWheelButtonPin, activateDigWheel);
    if(activateDigWheel){
      driveMotor(motorOneAddress, 2, 32);
    }
    else{
      driveMotor(motorOneAddress, 2, 0);
    }
}

//if the digitalRead of the given pin is high, then set the boolean to true. If not, set the boolean to false.
void activateButton(int buttonPin, bool buttonBool){
  int value = digitalRead(buttonPin);
  if(value == HIGH){
    buttonBool == true;
    Serial.println(1 + "," + buttonPin);
  }
  else{
    buttonBool == false;
    Serial.println(0 + "," + buttonPin);
  }
}

//commands 0,1 or 4,5
//given address takes inputs of motor 1 or motor 2
//Speed is -127-127, where -127 is full speed reverse and 127 is full speed forward
void driveMotor(int address,int motor, int speed){
  int command;
  if(motor == 1){
   command = 0;
  }
  else if(motor == 2){
    command = 4;
  }
  else{
    return;
  }
  if(speed < 0){
    command++;
    speed *= -1;
  }
  Serial1.write(command);
  sendSerialPacket(address, command, speed);
}

// use this method whenever you need to send a packet to Sabertooth
void sendSerialPacket(int address, int command, int value){ 
  Serial1.write(address); //starts command to given address
  Serial1.write(command); //sends the command name
  Serial1.write(value); //sends the given value to the specified command
  Serial1.write((address + command + value) & 0B01111111); //sends the checksum
}
  
//setup method used to set minimum and maximum voltage to motors
void setupMinMaxVoltage(int address, int minVoltage, int maxVoltage){
  if((minVoltage < 0) || (minVoltage > 120) || (maxVoltage < 0) || (maxVoltage > 128)){ //makes sure inputs are allowed
    return;
  }
  sendSerialPacket(address, 2, minVoltage); // sets the minimum allowed Voltage 
  sendSerialPacket(address, 3, maxVoltage); // sets the maximum allowed Voltage
}

//setup method used to set the baud rate to motors
void setupBaudRate(int address, int baudRate){
  if((baudRate < 1) || (baudRate > 5)){ // makes sure inputs are allowed
    return;
  }

  sendSerialPacket(address, 15, baudRate); // sets the baudRate cooresponding to the value given
}

//setup method used to set the deadband
void setupDeadband(int address, int deadband){
  if((deadband < 0) || (deadband > 127)){ // makes sure inputs are allowed
    return;
  }
  sendSerialPacket(address, 17, deadband); // sets the range to be 127 - deadband < off < 128 + deadband
}

