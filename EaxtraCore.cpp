#include <ExtraCore.h>

void ExtraCore::foo()
{
}


//ex: setPinIOstate(A0, OUTPUT);
void ExtraCore::setPinIOstate(int pin, boolean state)
{
	if(state)
	{
		bitSet(_configData.mode, pin);
	}
	else
	{
		bitClear(_configData.mode, pin);
	}
}

void ExtraCore::setOutputValue(int pin, boolean value)
{
	if(value)
	{
		bitSet(_configData.output, pin);
	}
	else
	{
		bitClear(_configData.output, pin);
	}
}

void ExtraCore::setInputValue(int pin, boolean value)
{
	if(value)
	{
		bitSet(_readingData.inputValues, pin);
	}
	else
	{
		bitClear(_readingData.inputValues, pin);
	}
}

//setTriStateValue(pin, TRUE) is
//the same as setting pinMode(pin, OUTPUT); digitWrite(pin, HIGH);
//Clearing TriState won't change the I/O bit.
void ExtraCore::setTriStateValue(int pin, boolean value)
{
	if(value)
	{
		bitSet(_configData.tri, pin);
		bitSet(_configData.mode, pin);
	}
	else
	{
		bitClear(_configData.tri, pin);
	}
}

boolean ExtraCore::getPinIOstate(int pin)
{
	return bitRead(_configData.mode, pin);
}

boolean ExtraCore::getOutputValue(int pin)
{
	return bitRead(_configData.output, pin);
}

boolean ExtraCore::getTriStateValue(int pin)
{
	return bitRead(_configData.tri, pin);
}


void ExtraCore::beginManager()
{
	Wire.begin(I2C_MANAGER_ADDRESS);
	_begin();
}

void ExtraCore::beginClient()
{
	Wire.begin(I2C_CLIENT_ADDRESS);
	_begin();
}

void ExtraCore::_begin()
{
	Wire.onReceive(receive);
	ConfigTransfer.begin(details(_configData), &Wire);
	ReadingsTransfer.begin(details(_readingData), &Wire);
}

void ExtraCore::sendConfig()
{
	ConfigTransfer.sendData(I2C_CLIENT_ADDRESS);
}

void ExtraCore::sendData()
{
	ReadingsTransfer.sendData(I2C_MANAGER_ADDRESS);
}

void ExtraCore::receive(int numBytes) {}

boolean ExtraCore::getConfigSetting(int pin)
{
	return bitRead(_configData.mode, pin);
}

boolean ExtraCore::getOutputSetting(int pin)
{
	return bitRead(_configData.output, pin);
}

boolean ExtraCore::getTriStateSetting(int pin)
{
	return bitRead(_configData.tri, pin);
}