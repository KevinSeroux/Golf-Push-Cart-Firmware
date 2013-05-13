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

#include "Servo.h"
#include "RTB.h"

#define BUTTON_MODE_PIN 9
#define INCREASE_ENGINES_PIN 10
#define DECREASE_ENGINES_PIN 11
#define LEFT_ENGINE_PIN 10
#define RIGHT_ENGINE_PIN 11

Servo _leftEngine;
Servo _rightEngine;

float _currentSpeed = 1500; //For manual mode

void setup()
{
  pinMode(INCREASE_ENGINES_PIN, INPUT);
  pinMode(DECREASE_ENGINES_PIN, INPUT);
  pinMode(LEFT_ENGINE_PIN, OUTPUT);
  pinMode(RIGHT_ENGINE_PIN, OUTPUT);
  
  _leftEngine.attach(LEFT_ENGINE_PIN);
  _rightEngine.attach(RIGHT_ENGINE_PIN);
  
  RTB* myRTB = 0;
  
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
        if(_currentSpeed <= 1496.251f)
        {
          _currentSpeed += 3.749f;
          _leftEngine.write(_currentSpeed);
          _rightEngine.write(_currentSpeed);
        }
      }
      if(digitalRead(INCREASE_ENGINES_PIN) == 1)
      {
        if(_currentSpeed >= 547.754f)
        {
          _currentSpeed -= 3.749f;
          _leftEngine.write(_currentSpeed);
          _rightEngine.write(_currentSpeed);
        }
      }
    }
    else
      myRTB->sync();
  }
  
  delete myRTB;
}

//We don't use loop() because setup() and loop() encourage us to use global variable, memory leaks, ...
void loop() {}





