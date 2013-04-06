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
    
    inline void setSpeedsEngines(const char leftEngine, const char rightEngine)
    {
        _speedLeftEngine = leftEngine;
        _speedRightEngine = rightEngine;
    }
    
    inline void setSpeedLeftEngine(const char leftEngine)
    {
      _speedLeftEngine = leftEngine;
    }
    
    inline void setSpeedRightEngine(const char rightEngine)
    {
      _speedRightEngine = rightEngine;
    }
    
    inline const char getSpeedLeftEngine()
    {
      return _speedLeftEngine;
    }
    
    inline const char getSpeedRightEngine()
    {
      return _speedRightEngine;
    }
    
    inline void operator++(int)
    {
      _speedLeftEngine++;
      _speedRightEngine++;
    }
    
    inline void operator--(int)
    {
      _speedLeftEngine--;
      _speedRightEngine--;
    }
  private:
    char _speedLeftEngine;
    char _speedRightEngine;
};

#endif
