///////////////////////////////////////////////////////////
//  ApplicationThread.cpp
//  Definition of the class ApplicationThread
//  Created on:      11-Feb-2018 13:38:58
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include"ApplicationThread.h"
#include "DebugClass.h"
#include "VoltageReader.h"
#include "Thread.h"
#include "ConnectorClient.h"

void ApplicationThread::Start()
{
  thread.start(mbed::callback(ApplicationThread::Run));
}

void ApplicationThread::Run()
{
  DebugClass::Print("ApplicationThread started");

  VoltageReader voltage;
  ConnectorClient client;

  client.Start();

  float voltageArray[voltage.GetVoltageCount()];
  for(uint32_t i = 0; i < voltage.GetVoltageCount(); i++)
  {
    voltageArray[i] = voltage.GetRawValue(i);
  }

  DebugClass::Print("Voltage 0: ", voltageArray[0]);
  DebugClass::Print("Voltage 1: ", voltageArray[1]);
  DebugClass::Print("Voltage 2: ", voltageArray[2]);
  DebugClass::Print("Voltage 3: ", voltageArray[3]);
  rtos::Thread::wait(500);

  for(;;)
  {
    client.Run();
  }
}
