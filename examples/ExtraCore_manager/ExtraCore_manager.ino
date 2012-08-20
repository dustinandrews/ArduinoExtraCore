#include <ExtraCore.h>
#include <Wire.h>
#include <EasyTransferI2C.h>
#include <TimerOne.h>

//create object
ExtraCore extraCore;

void setup()
{
  pinMode(13, OUTPUT);
  extraCore.beginManager();
  extraCore.setPinIOstate(13, OUTPUT);//set remote pin to output.
  Serial.begin(9600);
  Serial.println("Manager Ready.");
  Timer1.attachInterrupt(recData, 100000);//check for incoming data 10 times a second.
}

void loop()
{
  digitalWrite(13, HIGH);
  extraCore.setOutputValue(13, HIGH);
  extraCore.sendConfig();
  delay(2000);
  extraCore.setOutputValue(13, LOW);
  extraCore.sendConfig();
  digitalWrite(13, LOW);
  delay(2000);
}

void recData()
{
  if(extraCore.ReadingsTransfer.receiveData())
  {
    Serial.println("data");
  }
}

