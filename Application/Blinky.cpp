///////////////////////////////////////////////////////////
//  Blinky.cpp
//  Definition of the class Blinky
//  Created on:      11-Feb-2018 10:42:26
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "Blinky.h"
#include "Thread.h"

void Blinky::Toggle()
{
  led = !led;
}

void Blinky::ToggleWait()
{
  Toggle();
  rtos::Thread::wait(500);
}

Blinky::Blinky(PinName pin)
:led(pin)
{}

void Blinky::HeartBeat()
{
  led = 1;
  rtos::Thread::wait(64);
  led = 0;
  rtos::Thread::wait(128);
  led = 1;
  rtos::Thread::wait(64);
  led = 0;
  rtos::Thread::wait(1744);
}
