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
//Variable Declarations
const byte ExtraCore::_pwmMap[6] = {3,5,6,9,10,11};

/****************************
* Callbacks for Wire Library *
****************************/
static void wireLibRecieveCallback(int numBytes)
{
	ExtraCoreHelper* helper = ExtraCoreHelper::getInstance();
	helper->ReceiveData();
}

ExtraCore::ExtraCore()
{
	_helper = ExtraCoreHelper::getInstance();
}

// Set a pin on the remote to 0 (input) or 1 (output)
void ExtraCore::setPinIOstate(int pin, boolean state)
{
	if(state)
	{
		bitSet(_helper->ConfigData.mode, pin);
	}
	else
	{
		bitClear(_helper->ConfigData.mode, pin);
	}
}

// set a pin to digitalWrite value, ignored if the pins IOstate is 0.
void ExtraCore::setDigitalOutput(int pin, boolean value)
{
	if(value)
	{
		bitSet(_helper->ConfigData.output, pin);
	}
	else
	{
		bitClear(_helper->ConfigData.output, pin);
	}
}

//Set the PWM output value (0-255) of an Analog pin. Ignored if IOstate is 0.
void ExtraCore::setAnalogOutput(int pin, int value)
{
	for(int i = 0; i < 6; i++)
	{
		if(pin == _pwmMap[i])
		{
			_helper->ConfigData.analogOutputs[i] = value;
		}
	}	
}

//Set a reading from the remote to send back to the manager.
void ExtraCore::setDigitalReading(int pin, boolean value)
{
	if(value)
	{
		bitSet(_helper->ReadingData.digitalInputs, pin);
	}
	else
	{
		bitClear(_helper->ReadingData.digitalInputs, pin);
	}
}

//Set a reading from the remote to send back to the manager.
void ExtraCore::setAnalogReading(int pin, int value)
{
	_helper->ReadingData.analogInputs[pin - A0] = value;	
}


//If setTriStateValue(pin, TRUE) is
//On the remote set pinMode(pin, OUTPUT); digitalWrite(pin, HIGH);
//Clearing TriState won't change the I/O bit. but will digitalWrite(pin, LOW) on the remote.
void ExtraCore::setTriStateValue(int pin, boolean value)
{
	if(value)
	{
		bitSet(_helper->ConfigData.tri, pin);
		bitSet(_helper->ConfigData.mode, pin);
	}
	else
	{
		bitClear(_helper->ConfigData.tri, pin);
	}
}

//Read the desired state of the pin
boolean ExtraCore::getPinIOstate(int pin)
{
	return bitRead(_helper->ConfigData.mode, pin);
}

//Read the desired output value of the pin.
boolean ExtraCore::getOutputValue(int pin)
{
	return bitRead(_helper->ConfigData.output, pin);
}

//Get the desired pullup state of the pin
boolean ExtraCore::getTriStateValue(int pin)
{
	return bitRead(_helper->ConfigData.tri, pin);
}

//Get the desired PWM value of the pin.
int ExtraCore::getAnalogValue(int pin)
{
	for(int i = 0; i < 6; i++)
	{
		if(pin == _pwmMap[i])
		{
			return _helper->ConfigData.analogOutputs[i];
		}
	}
	return 0;
}

//Begin running as a manager.
void ExtraCore::beginManager()
{
	Wire.begin(I2C_MANAGER_ADDRESS);
	_helper->isManager = 1;
	_begin();
}

//Begin running as a client
void ExtraCore::beginClient()
{
	Wire.begin(I2C_CLIENT_ADDRESS);
	_helper->isManager = 0;
	_begin();
}

void ExtraCore::_begin()
{
	Wire.onReceive(wireLibRecieveCallback);
	_helper->ConfigTransfer.begin(details(_helper->ConfigData), &Wire);
	_helper->ReadingsTransfer.begin(details(_helper->ReadingData), &Wire);
}

//Send the desired pin state to the remote.
void ExtraCore::sendConfig()
{
	_helper->ConfigTransfer.sendData(I2C_CLIENT_ADDRESS);
}

//Send readings back to the manager.
void ExtraCore::sendData()
{
	_helper->ReadingsTransfer.sendData(I2C_MANAGER_ADDRESS);
}

//Get the reading from a digital pin.
boolean ExtraCore::getDigitalReading(int pin)
{
	return bitRead(_helper->ReadingData.digitalInputs, pin);
}

//Get the analog reading from a pin
int ExtraCore::getAnalogReading(int pin)
{
	return _helper->ReadingData.analogInputs[pin - A0];	
}

boolean ExtraCore::isDataNew()
{
	boolean b = _helper->isDataNew;
	_helper->isDataNew = 0;
	return b;
}


/**********************************
* ExtraCoreHelper class functions *
**********************************/
ExtraCoreHelper* ExtraCoreHelper::_instance;
void ExtraCoreHelper::ReceiveData()
{
	if(isManager)
	{
		//Serial.println("ReadingsTransfer.receiveData();");
		ReadingsTransfer.receiveData();
	}
	else
	{
		//Serial.println("ConfigTransfer.receiveData();");
		ConfigTransfer.receiveData();
	}
	isDataNew = 1;
}