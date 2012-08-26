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

#ifndef ExtraCore_h
#define ExtraCore_h

#include "Arduino.h"
#include <Wire.h>
#include <EasyTransferI2C.h>

#define IOPINCOUNT 20
#define INPUTPINCOUNT 22
#define ANALOGPINCOUNT 8
#define I2C_CLIENT_ADDRESS 1
#define I2C_MANAGER_ADDRESS 2



struct SEND_CONFIG_STRUCT
{
	//Digital Pins 0-13
	unsigned long mode; //INPUT, OUTPUT
	unsigned long tri; //High Impedance ignore unless INPUT
	unsigned long output; //HIGH, LOW  ingnored unless OUTPUT
	//Fails to recieve when this array is to big. raw send looked OK-ish.
	unsigned int analogOutputs[6];//6 pwm outputs.
};

struct SEND_PIN_READINGS
{
	unsigned long digitalInputs;
	unsigned int analogInputs[ANALOGPINCOUNT];
};

class ExtraCoreHelper;
class ExtraCore 
{
public:
	ExtraCore();
	void setPinIOstate(int, boolean);
	void setDigitalOutput(int, boolean);
	void setAnalogOutput(int, int);
	void setTriStateValue(int, boolean);
	void setDigitalReading(int pin, boolean value);
	void setAnalogReading(int pin, int value);
	boolean getPinIOstate(int);
	boolean getOutputValue(int);
	boolean getTriStateValue(int);
	SEND_CONFIG_STRUCT getConfigData();
	void sendConfig();
	void sendData();
	boolean getConfigSetting(int pin);
	boolean getOutputSetting(int pin);
	boolean getAnalogOutputSetting(int pin);
	boolean getTriStateSetting(int pin);
	int getAnalogSetting(int pin);
	void beginManager();
	void beginClient();
	boolean getDigitalReading(int pin);
	int getAnalogReading(int pin);
	boolean isDataNew();
private:
	ExtraCoreHelper* _helper;
	void _begin();
	const static byte _pwmMap[6];
	boolean _newData;
};

class ExtraCoreHelper
{
public:
	static ExtraCoreHelper* getInstance()
	{	
		if(_instance == NULL)
		{
			_instance = new ExtraCoreHelper;
		}
		return _instance;
	}
	
	EasyTransferI2C ConfigTransfer;
	EasyTransferI2C ReadingsTransfer;
	SEND_CONFIG_STRUCT ConfigData;
	SEND_PIN_READINGS ReadingData;
	bool isManager;
	bool isDataNew;
	void *OnRequestData(void (*)(void) );	
	void ReceiveData();
private:
	static ExtraCoreHelper* _instance;
	ExtraCoreHelper(){}
	ExtraCoreHelper(ExtraCoreHelper const&);
	void operator=(ExtraCoreHelper const&);
};


#endif