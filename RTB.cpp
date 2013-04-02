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

RTB::RTB(Engines instance)
{
  _enginesInstance = instance;
  
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
    //delay(500);
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
  if(_bluetooth->available() > 2)
  {
    if(_bluetooth->read() == 255)
    {
      if(_bluetooth->available() > 4)
      {
        _bluetooth->read();
        _bluetooth->read();
        Serial.write("3B removed !\n");
      }
      else
      {
        _leftSpeedEngine = _bluetooth->read();
        _rightSpeedEngine = _bluetooth->read();

        _enginesInstance.setSpeedsEngines(_leftSpeedEngine, _rightSpeedEngine);

        Serial.write("Speed of the golf cart : ");
        Serial.print(_leftSpeedEngine, DEC);
        Serial.write(" | ");
        Serial.println(_rightSpeedEngine, DEC);
      }
    }
    else
    {        
      if(_bluetooth->find("\nDISCONNECT\r\n") == true)
      {
        Serial.write("DISCONNECTION\n");
        _enginesInstance.setSpeedsEngines(0, 0);
        waitAcq();
      }
    }
  }
#else
  if(Serial.available() > 2)
  {
    if(Serial.read() == 255)
    {
      if(Serial.available() > 4)
      {
        Serial.read();
        Serial.read();
      }
      else
        setSpeedsEngines(Serial.read(), Serial.read());
    }
    else
    {        
      if(Serial.find("\nDISCONNECT\r\n") == true)
      {
        setSpeedsEngines(0, 0);
        waitAcq();
      }
    }
  }
#endif
}
