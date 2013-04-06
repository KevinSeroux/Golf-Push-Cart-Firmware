/*--------------------------------------------------------------------\
| DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                         |
| Version 2, December 2004                                            |
|                                                                     |
| Copyright (C) 2013 Kévin Seroux <kevin.seroux@orange.fr>            |
|                                                                     |
| Everyone is permitted to copy and distribute verbatim or modified   |
| copies of this license document, and changing it is allowed as long |
| as the name is changed.                                             |
|                                                                     |
| DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                         |
| TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION     |
|                                                                     |
| 0. You just DO WHAT THE FUCK YOU WANT TO.                           |
\-------------------------------------------------------------------*/

#ifndef RTB_H
#define RTB_H

#include <Arduino.h>
#include "SoftwareSerial.h"
#include "Engines.h"

#define DEBUG
#define BATTERY_UPDATE 5000
#define BATTERY_TEST_PIN A5
#define LED_PIN 13
#define BAUD_RATE 9600

class RTB
{
public:
  RTB(Engines *const instance);
#ifdef DEBUG
  ~RTB();
#endif 
  void waitAcq();
  void sync();
private:
  /* inline */ void transmitBatteryLevel();
  /* inline */ void receiveDatas();

  unsigned char _prevBatteryLevel, _batteryLevel;
  unsigned long _prevBatteryUpdate;
  
  Engines* _enginesInstance;
#ifdef DEBUG
  SoftwareSerial* _bluetooth;
  unsigned char _leftSpeedEngine;
  unsigned char _rightSpeedEngine;
#endif
};

#endif
