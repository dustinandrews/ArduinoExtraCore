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

//This Manager example is meant to show the ways you can interact with a remote.
//You can and should adapt it to your scenario.
//It's best not to use the remote for timing critical applications.
//Indeed you should assume messages will sometimes be dropped and the remote state
//will be out of sync at times.
//Remote readings will only come in 100 times a second. You should assume they can
//also get stale.

/*************************
* Keep this block intact *
*************************/
ExtraCore extraCore;
void r(int numBytes)
{
  extraCore.ReadingsTransfer.receiveData();
}

void setup()
{
  Wire.onReceive(r);//keep this line
  

  pinMode(13, OUTPUT); //set local pin13 to output.
  extraCore.beginManager();//begin Manager role. (beginClient() on remote)
  extraCore.setPinIOstate(6, OUTPUT);//set remote pin to output.
  extraCore.setPinIOstate(13, OUTPUT);//set remote pin to output.
  Serial.begin(9600);  
  Serial.println("Manager Ready.");
}

  
void loop()
{
  delay(10);//Don't remove this delay. Sending updates too quickly will block data returning.
 
  //Setup PWM example.
  //setup an LED with a resistor on Pin6 to + to and - to GND on the remote to see it.
  static byte pwm = 0;
  static byte amt = 17;
  if(pwm == 255)
  {
    amt = -17;
  }
  else if (pwm == 0)
  {
    amt = 17;
  }
  pwm+=amt;
  extraCore.setAnalogOutput(6, pwm);//steps LED brightness up and down.
  
  
  ////Wire remote 13 to remote 2.
  //Flash local 13 in time with remote 13.
  digitalWrite(13, HIGH);
  extraCore.setDigitalOutput(13, HIGH);//Set the remote to the same as local.
  extraCore.sendConfig();//changes won't take effect until you sendConfig();
  delay(50);
  
  //readings are updated 100 times a second automatically.
  Serial.print("Remote D2 (expect 1): ");
  Serial.println(extraCore.getDigitalReading(2));//Should be 1
  Serial.print("Remote A0: ");
  Serial.println(extraCore.getAnalogReading(A0));//expect random floating values.
  delay(50);
  
  extraCore.setDigitalOutput(13, LOW);
  extraCore.sendConfig();
  digitalWrite(13, LOW);
  analogWrite(3, 0);
  delay(50);
  Serial.print("Remote D2 (expect 0): ");
  Serial.println(extraCore.getDigitalReading(2));
  delay(40);
}

