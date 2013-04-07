/*--------------------------------------------------------------------\
| DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                         |
| Version 2, December 2004                                            |
|                                                                     |
| Copyright (C) 2013 Kévin Seroux <kevin.seroux@orange.fr>            |
|                    Jéremy Robert <yro44@orange.fr>                  |
|                    Tristan Lebreton <lebreton-tristan@orange.fr>    |
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
#include "MsTimer2.h"

#define BUTTON_MODE_PIN 9
#define INCREASE_ENGINES_PIN 10
#define DECREASE_ENGINES_PIN 11
#define LEFT_ENGINE_PIN 12
#define RIGHT_ENGINE_PIN 13

float timeHighLeftEngine;
float timeHighRightEngine;
float difference;

void doPWM()
{  
  if(timeHighLeftEngine == timeHighRightEngine)
  {
    if(timeHighLeftEngine > 0)
    {
      digitalWrite(LEFT_ENGINE_PIN, HIGH);
      digitalWrite(RIGHT_ENGINE_PIN, HIGH);
      
      delay(timeHighLeftEngine / 1000);
      delayMicroseconds(static_cast<unsigned int>(timeHighLeftEngine) % 1000);
      
      digitalWrite(LEFT_ENGINE_PIN, LOW);
      digitalWrite(RIGHT_ENGINE_PIN, LOW);
    }
  }
  else if(timeHighLeftEngine > timeHighRightEngine)
  {
    digitalWrite(LEFT_ENGINE_PIN, HIGH);
    if(timeHighRightEngine > 0)
      digitalWrite(RIGHT_ENGINE_PIN, HIGH);
      
    delay(timeHighRightEngine / 1000);
    delayMicroseconds(static_cast<unsigned int>(timeHighRightEngine) % 1000);
    
    if(timeHighRightEngine > 0)
      digitalWrite(RIGHT_ENGINE_PIN, LOW);
    
    difference = timeHighLeftEngine - timeHighRightEngine;
    
    delay(difference / 1000);
    delayMicroseconds(static_cast<unsigned int>(difference) % 1000);
    
    digitalWrite(LEFT_ENGINE_PIN, LOW);
  }
  else //If timeHighRightEngine > timeHighLeftEngine
  {
    if(timeHighLeftEngine > 0)
      digitalWrite(LEFT_ENGINE_PIN, HIGH);
    digitalWrite(RIGHT_ENGINE_PIN, HIGH);
    
    delay(timeHighLeftEngine / 1000);
    delayMicroseconds(static_cast<unsigned int>(timeHighLeftEngine) % 1000);
    
    if(timeHighLeftEngine > 0)
      digitalWrite(LEFT_ENGINE_PIN, LOW);
    
    difference = timeHighRightEngine - timeHighLeftEngine;
    
    delay(difference / 1000);
    delayMicroseconds(static_cast<unsigned int>(difference) % 1000);
    
    digitalWrite(RIGHT_ENGINE_PIN, LOW);
  }
}

void setup()
{
  pinMode(INCREASE_ENGINES_PIN, INPUT);
  pinMode(DECREASE_ENGINES_PIN, INPUT);
  pinMode(LEFT_ENGINE_PIN, OUTPUT);
  pinMode(RIGHT_ENGINE_PIN, OUTPUT);
  
  RTB* myRTB = 0;
  MsTimer2::set(18, doPWM);
  MsTimer2::start();
  
  while(true)
  {
    if(digitalRead(BUTTON_MODE_PIN) == 1)
    {
      if(myRTB == 0)
        myRTB = new RTB();
      else
      {
        delete myRTB;
        myRTB = 0;
      }
    }
    
    if(myRTB != 0)
    {
      if(digitalRead(DECREASE_ENGINES_PIN) == 1)
      {
        if(timeHighLeftEngine < 1992.38f) //1992.38 -> 7.844 * 254
          timeHighLeftEngine += 7.844f; //7.844 -> 2000 / 255
        if(timeHighLeftEngine < 1992.38f)
          timeHighRightEngine += 7.844f;
      }
      if(digitalRead(INCREASE_ENGINES_PIN) == 1)
      {
        if(timeHighLeftEngine > 7.844f)
          timeHighLeftEngine -= 7.844f;
        if(timeHighRightEngine > 7.844f)
          timeHighRightEngine -= 7.844f;
      }
    }
    else
      myRTB->sync();
  }
}

//We don't use loop() because setup() and loop() encourage us to use global variable, memory leaks, ...
void loop() {}





