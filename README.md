ArduinoExtraCore
================

An Arduino Library that allows one client Arduino to be used as an I/O extender for a manager Arduino.

Features:
--------
- Two way i2c
- remote set digital pin modes
- remote set digital outputs.
- remote read digital and analog pins.


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
- load the manager sketch on the primary
- load the client on the secondary

Option setup for the test Sketch
--------------------------------

Make sure Pin 13 has an LED/resistor on each. Hook an LED/resistor to pin 6 for PWM output.


