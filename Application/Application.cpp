///////////////////////////////////////////////////////////
//  Application.cpp
//  Implementation of the class Application
//  Created on:      10-Feb-2018 22:49:23
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "Application.h"
#include "DebugClass.h"


void Application::Run()
{
  DebugClass::Print("Starting application");

  thread.Start();
}
