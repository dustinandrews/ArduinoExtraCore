ArduinoExtraCore
================

An Arduino Library that allows one client Arduino to be used as an I/O extender for a manager Arduino.

More info:
http://authenticinvention.com/authentic/?p=304

Features:
--------
- Two way i2c
- remote set digital pin modes
- remote set digital outputs
- remote set PWM outputs
- remote read digital and analog pins


Requirements
------------

- Two arduino UNO's or compatible.
- EasyTransferI2C library
- Wire library


Installation
------------

- Copy .H and .CPP to into .../Ardunio/Libraries/ExtraCore directory
- Connect pin A4 on both Arduinos together
- Connect pin A5 on both Arduinos together
- Connect GND on both Arduinos together
- load the manager sketch from examples on the primary
- load the client sketch from examples on the secondary

Optional setup for the test sketch
--------------------------------

Make sure Pin 13 has an LED/resistor on each board. Hook an LED/resistor to pin 6 for PWM output on the client.

Reference
---------

ExtraCore();
	Constructor

###Manager Methods
void beginManager();
	Start sending and receiving data as the manager.
	
void setPinIOstate(pin, boolean);
	Set the desired INPUT/OUTPUT state of a pin.
	
void setDigitalOutput(pin, boolean);
	Set the desired HIGH, LOW output state of a pin.
	
void setAnalogOutput(pin, pwm);
	Set the desired PWM (0-255) state of a pin. Ignored if not PWM cabable.

void setTriStateValue(int, boolean);
	Set the pullup resistor to TRUE/FALSE. True will automatically set the pin to INPUT.

boolean getDigitalReading(pin);
	Get the last known digital reading from the remote.

int getAnalogReading(pin);
	Get the last known analog reading from the remote.
	
void sendConfig();
	Send the current desired state of all the pins to the remote.
	This is required to for changes to take effect.
	
###Client methods:
void beginClient();
	begin sending and recieving as client.
	
boolean getPinIOstate(pin);
	Get the desired IO state for a pin.
	
boolean getOutputValue(pin);
	Get the desired digital output value for a pin.
	
boolean getTriStateValue(pin);
	get the desired pullup resistor value for a pin.
	
int getAnalogValue(pin);
	Get the desired PWM output for a PWM pin.
	
void setDigitalReading(pin, value);
	Set the digital reading from the remote for a pin.
	
void setAnalogReading(pin, value);
	Set the Analog reading for pin.
	
void sendData();
	Send the currently known pin readings to the manager.
	This is required for updates to take effect.

boolean isDataNew();
	Returns true if new data has arrived since the last time it was checked.
