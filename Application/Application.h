///////////////////////////////////////////////////////////
//  Application.h
//  Definition of the class Application
//  Created on:      10-Feb-2018 22:48:35
//  Original author: Vitalij
///////////////////////////////////////////////////////////


#ifndef APPLICATION_H
#define APPLICATION_H

#include "ApplicationThread.h"

class Application
{
public:
  void Run(void);

private:
  ApplicationThread thread;
  
};

#endif // APPLICATION_H
