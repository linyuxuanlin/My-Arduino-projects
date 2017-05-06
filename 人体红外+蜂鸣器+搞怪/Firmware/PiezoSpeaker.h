#ifndef PiezoSpeaker_H
#define PiezoSpeaker_H

#include "BaseSpeaker.h"

class PiezoSpeaker : public BaseSpeaker  {
  public:
    PiezoSpeaker(const int pin);
};


#endif //PiezoSpeaker_H
