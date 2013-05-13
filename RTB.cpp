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

#include "RTB.h"

RTB::RTB()
{  
#ifdef DEBUG
  _bluetooth = new SoftwareSerial(2,4);
  _bluetooth->begin(BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);
#endif

  Serial.begin(BAUD_RATE);

#ifdef DEBUG
  _bluetooth->flush(); //We clear the module's memory buffer
#endif

  Serial.flush(); //We clear the Serial's memory buffer

#ifdef DEBUG
  _bluetooth->write("AT+BTCANCEL\r");
  while(_bluetooth->available() < 6); //Waiting "\r\nOK\r\n"
  _bluetooth->flush();

  _bluetooth->write("AT+BTSCAN\r");    
  while(_bluetooth->available() < 6); //Waiting "\r\nOK\r\n"

  waitAcq();
#else
  Serial.write("AT+BTCANCEL\r");
  while(Serial.available() < 6); //Waiting "\r\nOK\r\n"
  Serial.flush();

  Serial.write("AT+BTSCAN\r");
  while(Serial.available() < 6); //Waiting "\r\nOK\r\n"

  waitAcq();
#endif
}

#ifdef DEBUG
RTB::~RTB()
{
  // We must delete the dynamic allocated variable to avoid a memory leak.
  delete _bluetooth;
}
#endif

void RTB::waitAcq()
{
#ifdef DEBUG
  _bluetooth->flush(); //We clear

  while(_bluetooth->available() < 24); //Waiting "\r\nCONNECT 123456789012\r\n"
  _bluetooth->flush();
  
  Serial.write("====================================\nCONNECTION\n====================================\n");
#else
  Serial.flush(); //We clear

  while(Serial.available() < 24); //Waiting "\r\nCONNECT 123456789012\r\n"
  Serial.flush();
#endif
}

void RTB::sync()
{
  if((millis() - _prevBatteryUpdate) >= BATTERY_UPDATE)
  {
#ifdef DEBUG
    digitalWrite(LED_PIN, HIGH);
#endif
    transmitBatteryLevel();
    _prevBatteryUpdate = millis();
#ifdef DEBUG
    digitalWrite(LED_PIN, LOW);
#endif
  }
  receiveDatas();
}

inline void RTB::transmitBatteryLevel()
{
  _batteryLevel = analogRead(BATTERY_TEST_PIN);
  if(_prevBatteryLevel != _batteryLevel)
  {
#ifdef DEBUG
    _bluetooth->print(_batteryLevel);
#else
    Serial.print(_batteryLevel);
#endif
    _prevBatteryLevel = _batteryLevel;
  }
}

inline void RTB::receiveDatas()
{
#ifdef DEBUG
  if(_bluetooth->available() > 1)
  {
    Serial.write("------------------------------------\n");
    Serial.print(_bluetooth->available());
    Serial.write("B available !\n");
  }
  
  if(_bluetooth->available() > 2)
  {
    if(_bluetooth->read() == 255)
    {
      _leftSpeedEngine = _bluetooth->read();
      _rightSpeedEngine = _bluetooth->read();
        
      _leftEngine.write(-3.749f * _leftSpeedEngine + STOP_SPEED);
      _rightEngine.write(-3.749f * _rightSpeedEngine + STOP_SPEED);

      Serial.write("Speed of the golf cart : ");
      Serial.print(-3.749f * _leftSpeedEngine + STOP_SPEED, 0);
      Serial.write(" | ");
      Serial.println(-3.749f * _rightSpeedEngine + STOP_SPEED, 0);
    }
    else
    {
      _leftEngine.write(STOP_SPEED);
      _rightEngine.write(STOP_SPEED);
      
      while(_bluetooth->find("DISCONNECT\r\n") == false);
      Serial.write("====================================\nDISCONNECTION\n====================================\n");
      waitAcq();
    }
  }
#else
  if(Serial.available() > 2)
  {
    if(Serial.read() == 255)
    {
      _leftEngine.write(-3.749f * Serial.read() + STOP_SPEED);
      _rightEngine.write(-3.749f * Serial.read() + STOP_SPEED);
    }
    else
    {
      _leftEngine.write(STOP_SPEED);
      _rightEngine.write(STOP_SPEED);
      
      while(_bluetooth->find("DISCONNECT\r\n") == false);
      waitAcq();
    }
  }
#endif
}
