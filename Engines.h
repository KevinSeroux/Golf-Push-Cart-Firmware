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

#ifndef ENGINES_H
#define ENGINES_H

class Engines
{
  public:
    Engines();
    
    inline void setSpeedsEngines(const char speedLeftEngine, const char speedRightEngine)
    {
        setSpeedLeftEngine(speedLeftEngine);
        setSpeedRightEngine(speedRightEngine);
    }
    
    inline void setSpeedLeftEngine(const char speedLeftEngine)
    {
      _timeHighLeftEngine = speedLeftEngine * 2000 / 255;
    }
    
    inline void setSpeedRightEngine(const char speedRightEngine)
    {
      _timeHighRightEngine = speedRightEngine * 2000 / 255;
    }
    
    inline const unsigned short int getTimeHighLeftEngine()
    {
      return _timeHighLeftEngine;
    }
    
    inline const unsigned short int getTimeHighRightEngine()
    {
      return _timeHighRightEngine;
    }
    
    inline void operator++(int)
    {
      _timeHighLeftEngine++;
      _timeHighRightEngine++;
    }
    
    inline void operator--(int)
    {
      _timeHighLeftEngine--;
      _timeHighRightEngine--;
    }
  private:
    // It's not necessary to declare these variables as 'volatile' because the interrupt doesn't need to change their values
    unsigned short int _timeHighLeftEngine;
    unsigned short int _timeHighRightEngine;
};

#endif
