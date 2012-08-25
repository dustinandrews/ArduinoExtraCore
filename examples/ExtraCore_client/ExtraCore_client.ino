/*
 ExtraCore Library
Copyright Dustin Andrews 2012 
Licensed under the follwing license:

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
in the documentation and/or other materials provided with the distribution. 
The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <ExtraCore.h>
#include <Wire.h>
#include <EasyTransferI2C.h>

//This Client example is meant to be used as-is with the manager example.
//You shouldn't find a need to change this sketch. Though, if you find a way
//to improve it please do submit a patch.

//create object
ExtraCore extraCore;

void setup()
{
  Wire.onReceive(r);
  Serial.begin(9600);  
  extraCore.beginClient();
  Serial.println("client ready");
}

void loop() 
{
//  extraCore.ReadingsTransfer.receiveData();
  getDigitalData();
  getAnalogData();
  extraCore.ReadingsTransfer.sendData(2);
  delay(10);//Sending data back too fast will block getting updates.
}

void r(int numBytes)
{
  extraCore.ConfigTransfer.receiveData();
  setPinModes();
  setIOstates();
}

void setPinModes()
{
  for(int i = 0; i < IOPINCOUNT; i++)
  {
    // A4 and A5 are reserved for i2c
    if(i == A4 || i == A5) { continue; }
    pinMode(i, extraCore.getPinIOstate(i));
    digitalWrite(i, extraCore.getTriStateValue(i));
  }
}

void setIOstates()
{
  for(int i = 0; i < IOPINCOUNT; i++)
  {
    // A4 and A5 are reserved for i2c
    if(i == A4 || i == A5) { continue; }
    if(extraCore.getPinIOstate(i)  &&  extraCore.getAnalogSetting(i) == 0)
    {
      digitalWrite(i, extraCore.getOutputValue(i));
    }

    if(extraCore.getPinIOstate(i) && extraCore.getAnalogSetting(i))
    {
      analogWrite(i, extraCore.getAnalogSetting(i));
    }
  }
}

void getDigitalData()
{
  for(int i = 0; i < IOPINCOUNT; i++)
  {
    // A4 and A5 are reserved for i2c
    if(i == A4 || i == A5) { continue; }
    if(extraCore.getPinIOstate(i) == INPUT)
    {
      extraCore.setDigitalReading(i, digitalRead(i));
    }
  }
}

void getAnalogData()
{
  for(int i = A0; i < A6 + 1; i++)
  {
    // A4 and A5 are reserved for i2c
    if(i == A4 || i == A5) { continue; }
    if(extraCore.getPinIOstate(i) == INPUT)
    {
      extraCore.setAnalogReading(i, analogRead(i));
    }  
  }
}






