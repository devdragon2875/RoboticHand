//Receiver program

#include <Servo.h>
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l radio = Nrf24l(10, 9);

Servo finger1, finger2, finger3, finger4, finger5;
int servoPin1 = 9;
int servoPin2 = 5;
int servoPin3 = 10;
int servoPin4 = 6;
int flexArray[4];


void setup()
{
  Serial.begin(9600);
  radio.spi = &MirfHardwareSpi;
  radio.init();

  //Set your own address (sender & reciever) using any 5 characters. 
  //Make sure to change your address and channel to be unique
 
  radio.setRADDR((byte *)"MISHR"); //Set receiver address
  //radio.setTADDR((byte *)"ABCDE"); //set transmitter address
  //radio.payload = sizeof(value);
  radio.channel = 90;             //Set the used channel
  radio.config();
  Serial.println("Listening...");  //Start listening to received data
  
  finger1.attach(servoPin1);
  finger2.attach(servoPin2);
  finger3.attach(servoPin3);
  finger4.attach(servoPin4);

  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  pinMode(servoPin3, OUTPUT);
  pinMode(servoPin4, OUTPUT);
}


void loop()
{
  //puts recieved data into joystickVal
  if (radio.dataReady()) { 
    radio.getData((byte *)&flexArray);
    int flex1 = flexArray[0];
    int flex2 = flexArray[1];
    int flex3 = flexArray[2];
    int flex4 = flexArray[3];
  
    int pos1 = map(flex1, 400, 700, 0, 270);
    pos1 = constrain(pos1, 0, 180);
    int pos2 = map(flex2, 400, 700, 0, 270);
    pos2 = constrain(pos2, 0, 180);
    int pos3 = map(flex3, 400, 700, 0, 270);
    pos3 = constrain(pos3, 0, 180);
    int pos4 = map(flex4, 400, 700, 0, 270);
    pos4 = constrain(pos4, 0, 180);

    finger1.write(pos1);
    finger2.write(pos2);
    finger3.write(pos3);
    finger4.write(pos4);
    
  }
  
  delay(50);
  
}
