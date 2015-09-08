//Heavily stripped down and modified version of James Starkman's code which controlled the NASA robot in the May, 2014 competition

int motorOneAddress = 128;
int motor1Pin = 25;

//this runs once as soon as the arduino is turned on
void setup(){
  Serial.begin(9600); //pc connection
  }
  pinMode(motor1, OUTPUT);
}

//the code in here gets run oveer and over again until the arduino is turned off
void loop(){
    //write code here to send all the commands you impliment once
    driveMotor(motorOneAddress,100);
    //etc
}


//commands 0,1
//this sends a command to the motor specified by address, and sets it to the given speed. //Speed is -127-127, where -127 is full speed reverse and 127 is full speed forward

void driveMotor(int address, int speed){

      Serial1.write(address);
      //send motor command
      int command = 0; //motor 1
      if(speed < 0){
        command++;
        speed *= -1;
      }
      Serial1.write(command);
      //send motor speed
      Serial1.write(speed);
      //send checksum
      int check = (sabaddress + command + datab[i]) & B01111111;
      Serial1.write(check);
  }

}
