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
#include <iostream>

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
      for(uint32_t i = 0; i <= 50; i++)
      {
        const uint32_t waitTime = 10;
        float data;
        data = voltage.GetRawValueWithTimeStamp(0,timestamp);
        values.push_back(data);
//        std::cout << timestamp << ";" << data << std::endl ;
        
        rtos::Thread::wait(waitTime);
        values.push_back(timestamp);
      }
    }
    client.Run(values);
  }
}


// Reset in case of an unexpected behavior
void mbed_die(void) {
  NVIC_SystemReset();
}

void HardFault_Handler()
{
  NVIC_SystemReset();
}

void MemManage_Handler()
{
  NVIC_SystemReset();
}

void BusFault_Handler()
{
  NVIC_SystemReset();
}

void UsageFault_Handler(){
  NVIC_SystemReset();
}
