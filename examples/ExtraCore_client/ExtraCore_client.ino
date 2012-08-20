#include <ExtraCore.h>
#include <TimerOne.h>
#include <Wire.h>
#include <EasyTransferI2C.h>

//create object
ExtraCore extraCore;

void setup()
{
  extraCore.beginClient();
  Serial.begin(9600);
  Serial.println("client ready");
  Timer1.attachInterrupt(recData, 100000);//check for incoming data 10 times a second.
}

void loop() 
{

  //extraCore.sendData();
  
}

void setPinModes()
{
  for(int i = 0; i < IOPINCOUNT; i++)
  {
    // A4 and A5 are reserved for i2c
    if(i == A4 || i == A5) {continue;}
    pinMode(i, extraCore.getPinIOstate(i));
    digitalWrite(i, extraCore.getTriStateValue(i));
  }
}

void setIOstates()
{
  for(int i = 0; i < IOPINCOUNT; i++)
  {
    // A4 and A5 are reserved for i2c
    if(i == A4 || i == A5) {continue;}
    if(extraCore.getPinIOstate(i))
    {
      digitalWrite(i, extraCore.getOutputValue(i));
    }
  }
}

void getPinData()
{
  for(int i = 0; i < IOPINCOUNT; i++)
  {
    // A4 and A5 are reserved for i2c
    if(i == A4 || i == A5) {continue;}
    if(extraCore.getPinIOstate(i) == INPUT)
    {
      extraCore.setInputValue(i, digitalRead(i));
    }
  }
}

void recData()
{
  if(extraCore.ConfigTransfer.receiveData())
  {
    setPinModes();
    setIOstates();
    getPinData();
  }
}



