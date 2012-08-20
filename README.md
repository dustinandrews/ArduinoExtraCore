ArduinoExtraCore
================

An Arduino Library that allows one client Arduino to be used as an I/O extender for a manager Arduino.


Warning:
-----

This library is brand new and missing large chunks of functionality.

Working:
--------
- Two way i2c
- remote set digital pin modes
- remote set digital outputs.


TODO:
-----
- Test Digital input works.
- Create PWM output
- Create Analog input



Requirements
------------

- Two arduino UNO's or compatible.
- TimerOne library
- EasyTransferI2C library
- Wire library


Installation
------------

- Copy .H and .CPP to into .../Ardunio/Libraries/ExtraCore directory
- Connect pin A4 on both Arduinos together
- Connect pin A5 on both Arduinos together
- Connect GND on both Arduinos together
- load the manager sketch on the primary
- load the client on the secondary



