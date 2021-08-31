#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

///////////////////////
//joystick values
int joystick[2];
int xAxis;
int yAxis;
///////////////////////

///////////////////////
//define driver pins
int ENA = A0;
int ENB = A1;

int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;

int mspeed1 = 0;
int mspeed2 = 0;
///////////////////////

void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    
    radio.read(&joystick, sizeof(joystick));
    xAxis = joystick[0];
    yAxis = joystick[1];
    
    /*
    Serial.print("xAxis: ");
    Serial.println(xAxis);
    Serial.print("yAxis: ");
    Serial.println(yAxis);
    //delay(1000);
    */

    if((xAxis >= 400) && (yAxis >=800)){
      backward();
    }
    else if((xAxis >= 400) && (yAxis <= 300)){
      forward();
    }
    else if((xAxis == 0) && (yAxis >= 370)){
      left();
    }
    else if((xAxis == 1023) && (yAxis > 500)){
      right();
    }
    else{
      stopfcn();
    }
  }
}

//this function moves the robot forward
void forward(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  mspeed1 = 200;
  mspeed2 = 200;
  analogWrite(ENA,mspeed1);
  analogWrite(ENB,mspeed2);
}

//this function moves the robot backward
void backward(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
  mspeed1 = 200;
  mspeed2 = 200;
  analogWrite(ENA,mspeed1);
  analogWrite(ENB,mspeed2);
}

//this function moves the robot right
void right(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  mspeed1 = 100;
  mspeed2 = 0;
  analogWrite(ENA,mspeed1);
  analogWrite(ENB,mspeed2);
}

//this function moves the robot left
void left(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  mspeed1 = 0;
  mspeed2 = 100;
  analogWrite(ENA,mspeed1);
  analogWrite(ENB,mspeed2);
}

//stop function
void stopfcn(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  mspeed1 = 0;
  mspeed2 = 0;
  analogWrite(ENA,mspeed1);
  analogWrite(ENB,mspeed2);
}
