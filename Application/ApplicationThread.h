///////////////////////////////////////////////////////////
//  ApplicationThread.h
//  Declaration of the class ApplicationThread
//  Created on:      11-Feb-2018 13:38:58
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef APPLICATIONTHREAD_H
#define APPLICATIONTHREAD_H

#include "Thread.h"

class ApplicationThread
{
public:
  void Start(void);
  
private:
  static void Run(void);
  rtos::Thread thread;

};


#endif // APPLICATIONTHREAD_H
