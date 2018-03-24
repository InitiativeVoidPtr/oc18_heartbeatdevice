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

  std::vector<float> values;
  float timestamp = 0.0;
  
	for(;;)
  {
    values.clear();

    if(client.IsRunning())
    {
      DebugClass::Print("Start sampling");
      
      for(uint32_t i = 0; i <= 100; i++)
      {
        const uint32_t waitTime = 10;

        values.push_back(voltage.GetRawValue(0));
        
        rtos::Thread::wait(waitTime);
        timestamp += (float)waitTime;
        values.push_back(timestamp);
      }
      
      DebugClass::Print("Sampling finished");
    }
   
    client.Run(values);
  }
}
