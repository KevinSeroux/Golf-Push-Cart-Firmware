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

void doPWM()
{
  
}

void setup()
{
  Engines myEngines;
  RTB myRTB(myEngines);
  MsTimer2::set(18, doPWM);
  MsTimer2::start();
  
  while(true)
  {
    myRTB.sync();
  }
}

//We don't use loop() because setup() and loop() encourage us to use global variable, memory leaks, ...
void loop() {}





