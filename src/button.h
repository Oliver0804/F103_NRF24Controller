#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button
{
public:
    Button();
    byte getCombinationKey();
    String getCombinationKeyString();
};

#endif // BUTTON_H