///////////////////////////////////////////////////////////
//  Blinky.h
//  Declaration of the class Blinky
//  Created on:      10-Feb-2018 23:08:36
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef BLINKY_H
#define BLINKY_H

#include "PinNames.h"
#include "DigitalOut.h"

class Blinky
{
public:
  void Toggle(void);

  void ToggleWait(void);
  
  Blinky(PinName pin);

  void HeartBeat(void);

private:
mbed::DigitalOut led;
 
};

#endif // BLINKY_H
