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
#include "Engines.h"
#include "MsTimer2.h"

#define BUTTON_MODE_PIN 9
#define INCREASE_ENGINES_PIN 10
#define DECREASE_ENGINES_PIN 11
#define LEFT_ENGINE_PIN 12
#define RIGHT_ENGINE_PIN 13

/* Exceptionaly, we use a global instance to solve the MsTimer2() problem.
   But only because the program use this instance all the time, anyway */
Engines myEngines;

/* This function isn't in the Engines class because MsTimer2() don't support class (C++).
   It is write in C */
void doPWM() {}

void setup()
{
  pinMode(LEFT_ENGINE_PIN, OUTPUT);
  pinMode(RIGHT_ENGINE_PIN, OUTPUT);
  
  bool remoteMode = false;
  RTB* myRTB;
  MsTimer2::set(18, doPWM);
  MsTimer2::start();
  
  while(true)
  {
    if(digitalRead(BUTTON_MODE_PIN) == 1)
    {
      if(remoteMode == false)
      {
        myRTB = new RTB(&myEngines);
        remoteMode = true;
      }
      else
      {
        delete myRTB;
        remoteMode = false;
      }
    }
    
    if(remoteMode = false)
    {
      if(digitalRead(DECREASE_ENGINES_PIN) == 1)
        myEngines++;
      else if(digitalRead(INCREASE_ENGINES_PIN) == 1)
        myEngines--;
    }
    else
      myRTB->sync();
  }
}

//We don't use loop() because setup() and loop() encourage us to use global variable, memory leaks, ...
void loop() {}





