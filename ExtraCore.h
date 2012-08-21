#ifndef ExtraCore_h
#define ExtraCore_h

#include "Arduino.h"
#include <Wire.h>
#include <EasyTransferI2C.h>

#define IOPINCOUNT 20
#define INPUTPINCOUNT 22
#define I2C_CLIENT_ADDRESS 1
#define I2C_MANAGER_ADDRESS 2


struct SEND_CONFIG_STRUCT
{
	//Digital Pins 0-13
	unsigned long mode; //INPUT, OUTPUT
	//unsigned long analog; //Distinguish output types.
	unsigned long tri; //High Impedance ignore unless INPUT
	unsigned long output; //HIGH, LOW  ingnored unless OUTPUT
	unsigned int analogOutputs[8];
};

struct SEND_PIN_READINGS
{
	unsigned long digitalInputs;
	unsigned int analogInputs[8];
};


class ExtraCore 
{
public:
	void foo();
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
	EasyTransferI2C ConfigTransfer;
	EasyTransferI2C ReadingsTransfer;
	void sendConfig();
	void sendData();
	static void receive(int numBytes);
	boolean getConfigSetting(int pin);
	boolean getOutputSetting(int pin);
	boolean getAnalogOutputSetting(int pin);
	boolean getTriStateSetting(int pin);
	int getAnalogSetting(int pin);
	void beginManager();
	void beginClient();
	boolean getDigitalReading(int pin);
	int getAnalogReading(int pin);
private:
	void _begin();
	SEND_CONFIG_STRUCT _configData;
	SEND_PIN_READINGS _readingData;

};



#endif