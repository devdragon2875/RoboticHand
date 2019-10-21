//Transmitter program
#include <Servo.h>
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l radio = Nrf24l(10,9);

int flexPin1 = A0;
int flexPin2 = A1;
int flexPin3 = A2;
int flexPin4 = A3;
int flexArray[4];
void setup()
{
  Serial.begin(9600);
  radio.spi = &MirfHardwareSpi;
  radio.init();
  //Set your own address (sender address) using any 5 characters. 
  //Make sure to change your address and channel to be unique
 
  //radio.setRADDR((byte *)"ABCDE");   //Set the receiver address
  radio.setTADDR((byte *)"MISHR");     //set transmitter address    
  radio.payload = sizeof(flexArray);
  radio.channel = 90;              //Set the channel used. 
  radio.config();
  
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
  pinMode(flexPin4, INPUT);
}

void loop()
{
  //updates joystick value array with analog read
  int flex1 = analogRead(flexPin1);
  int flex2 = analogRead(flexPin2);
  int flex3 = analogRead(flexPin3);
  int flex4 = analogRead(flexPin4);
  
  flexArray[0] = flex1;
  flexArray[1] = flex2;
  flexArray[2] = flex3;
  flexArray[3] = flex4;
  
  radio.send((byte *)&flexArray);             //sends joystick data
  while (radio.isSending()) delay(1);        //Only keep going if radio finishes sending
  
  Serial.print("Sent joystick values");
  delay(50);
}
