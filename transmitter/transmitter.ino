#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//define joystick pins
int jsPin1 = A0;//X Axis
int jsPin2 = A1;//Y Axis

int joystick[2]; 

void setup()
{
  radio.begin();
  Serial.begin(9600);
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  joystick[0] = analogRead(jsPin1);
  joystick[1] = analogRead(jsPin2);

  //Send message to receiver  
  radio.write(&joystick, sizeof(joystick));
/*
  Serial.print("x = ");
  Serial.println(analogRead(jsPin1));
  Serial.print("y = ");
  Serial.println(analogRead(jsPin2));
  delay(1000);
*/  
}
