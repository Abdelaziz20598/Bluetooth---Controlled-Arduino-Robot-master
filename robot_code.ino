#include <SoftwareSerial.h> //LIBRARY TO BLUETOOTH MODULE
#include <Servo.h> // LIBRARY TO SERVO MOTORES 

//BLUETOOTH MODULE 
SoftwareSerial Bluetooth(0, 1); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
//int index = 0;
String dataIn = "";


//SERVO MOTORES(ROBOTIC ARM)
Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
// current position
int servo1Pos, servo2Pos;
int servo3Pos, servo4Pos; 
// previous position
int servo1PPos, servo2PPos;
int servo3PPos, servo4PPos; 

int speedDelay = 20; // DELAY OF SERVO

//*****************************

//DC MOTORES(CAR)
int dcspeed=0; //SPEED OF DC MOTORES
int motorSpeedA = 0;
int motorSpeedB = 0;
// H bridge bins in ardw
#define enA 5
#define in1 13
#define in2 8
#define enB 3
#define in3 7
#define in4 12
void setup() {
  servo01.attach(6); // gripper
  servo02.attach(10); //updown
  servo03.attach(9); //forward back
  servo04.attach(11); // rotation
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  delay(20);
  // Robot arm initial position
  servo1Pos = 90;
  servo01.write(servo1Pos);
  servo2Pos = 180;
  servo02.write(servo2Pos);
  servo3Pos = 0;
  servo03.write(servo3Pos);
  servo4Pos = 140;
  servo04.write(servo4Pos);
  
  //dc motor
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


}


void loop() {


  // Check for incoming data
  if (Bluetooth.available() > 0) { 
    if (dataIn.startsWith("ss")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      speedDelay = dataInS.toInt(); // Change servo speed (delay time)
    }
    if (dataIn.startsWith("dc")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      dcspeed = dataInS.toInt(); // Change motor speed (delay time)
    }
    dataIn = Bluetooth.readString();  // Read the data as string
    //Move Servo 1 to position

    if (dataIn.startsWith("s1")) {
      String dataInS = dataIn.substring(2, dataIn.length()); // Extract only the number. E.g. from "s1120" to "120"
      servo1Pos = dataInS.toInt();  // Convert the string into integer
      servo01.write(servo1Pos);
      delay(speedDelay);    // defines the speed at which the servo rotates
    }
    // Move Servo 2

    if (dataIn.startsWith("s2")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo2Pos = dataInS.toInt();
      servo02.write(servo2Pos);
      delay(speedDelay);
    }

    // Move Servo 3

    if (dataIn.startsWith("s3")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo3Pos = dataInS.toInt();
      servo03.write(servo3Pos);
      delay(speedDelay);
    }
    // Move Servo 4

    if (dataIn.startsWith("s4")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo4Pos = dataInS.toInt();
      servo04.write( servo4Pos);
      delay(speedDelay);
    }

    
    if (dataIn.startsWith("1")) {
      leftup(dcspeed);
    }
    if (dataIn.startsWith("2")) {
      Forward(dcspeed);
    }
    if (dataIn.startsWith("3")) {
      rightup(dcspeed);
    }
    if (dataIn.startsWith("4")) {
      left(dcspeed);
    }
    if (dataIn.startsWith("5")) {
      right(dcspeed);
    }
    if (dataIn.startsWith("6")) {
      leftdown(dcspeed);
    }
    if (dataIn.startsWith("7")) {
      Backward(dcspeed);
    }

    if (dataIn.startsWith("8")) {
      rightdown(dcspeed);
    }

    if (dataIn.startsWith("11")) {
      rotateleft(dcspeed);
    }
    if (dataIn.startsWith("12")) {
      rotateright(dcspeed);
    }
    if (dataIn.startsWith("13")) {
      stopnow();
 
    }
  }
}


void Forward(int dcspeed){
  // Set Motor A forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,dcspeed) ;
  // Set Motor B forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,dcspeed) ;

}
void Backward(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA,dcspeed) ;
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,dcspeed) ;
}
void right(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA,dcspeed) ;
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void left(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,dcspeed) ;
}
void leftup(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enB,dcspeed/2) ;
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,dcspeed) ;
}
void rightup(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enB,dcspeed) ;
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,dcspeed/2) ;
}
void leftdown(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB,dcspeed/2) ;
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,dcspeed) ;
}
void rightdown(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB,dcspeed) ;
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,dcspeed/2) ;
}
void rotateright(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enB,dcspeed) ;
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,dcspeed) ;
}
void rotateleft(int dcspeed){
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enB,dcspeed) ;
  // Set Motor B backward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,dcspeed) ;
}
void stopnow(){
  // Set Motor A backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // Set Motor B backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
