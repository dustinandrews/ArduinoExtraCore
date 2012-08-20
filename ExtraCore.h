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
	unsigned long tri; //High Impedance ignore unless INPUT
	unsigned long output; //HIGH, LOW  ingnored unless OUTPUT
};

struct SEND_PIN_READINGS
{
	unsigned long inputValues;
};


class ExtraCore 
{
public:
	void foo();
	void setPinIOstate(int, boolean);
	void setOutputValue(int, boolean);
	void setTriStateValue(int, boolean);
	void setInputValue(int pin, boolean value);
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
	boolean getTriStateSetting(int pin);
	void beginManager();
	void beginClient();
	
private:
	void _begin();
	SEND_CONFIG_STRUCT _configData;
	SEND_PIN_READINGS _readingData;

};



#endif