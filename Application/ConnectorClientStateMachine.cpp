///////////////////////////////////////////////////////////
//  ConnectorClientStateMachine.cpp
//  Definition of the class ConnectorClientStateMachine
//  Created on:      18-Mar-2018 13:01:38
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "ConnectorClientStateMachine.h"
#include "DebugClass.h"
#include "Thread.h"
#include "nsapi_types.h"
#include "ConnectorClient.h"
#include <iomanip>
#include <sstream>
#include <iostream>


// This is address to mbed Device Connector
#define MBED_SERVER_ADDRESS "coap://api.connector.mbed.com:5684"


ConnectorClientStateMachine::ConnectorClientStateMachine(ConnectorClient* connector)
: connector(connector),
  state(IDLE)
{
  
}

bool ConnectorClientStateMachine::IsRunning()
{
  if(UPDATE == state)
  {
    return true;
  }
  return false;
}


void ConnectorClientStateMachine::Start()
{
  state = CONNECTING;
}


void ConnectorClientStateMachine::Run(std::vector<float> values)
{
	this->values = values;
	
  switch(state)
  {
    case IDLE:
    {
      rtos::Thread::wait(5000);
      break;
    }

    case CONNECTING:  { Connecting(); break; }
    case SETUP:       { Setup();      break; }
    case REGISTER:    { Register();   break; }
    case UPDATE:      { Update();     break; }
    case UNREGISTER:  { Unregister(); break; }
    case DETACH:      { Detach();     break; }
    case ERROR:       { Error();      break; }

    default:
    {
      DebugClass::Print("Default case reached!");
    }
  }
}

void ConnectorClientStateMachine::PrintNetworkInfo()
{
  DebugClass::Print("IP address: ", connector->eth.get_ip_address());
  DebugClass::Print("MAC address: ", connector->eth.get_mac_address());
  DebugClass::Print("Netmask: ", connector->eth.get_netmask());
  DebugClass::Print("Gateway: ", connector->eth.get_gateway());
}


void ConnectorClientStateMachine::Connecting()
{
  DebugClass::Print("Start connecting");
  nsapi_error_t ret = connector->eth.connect();

  if(NSAPI_ERROR_OK == ret)
  {
    DebugClass::Print("Connection successful");
    PrintNetworkInfo();

    state = SETUP;
  }
}


void ConnectorClientStateMachine::Setup()
{
  DebugClass::Print("Trying to setup");

  connector->mbedClient.create_interface(MBED_SERVER_ADDRESS,
    &connector->eth);

  M2MDevice* deviceObject = 
    connector->mbedClient.create_device_object();

  objectList.push_back(deviceObject);
  objectList.push_back(valueAdc.GetObject());

  state = REGISTER;
}


void ConnectorClientStateMachine::Register()
{
  DebugClass::Print("Register at mbed Device Connector");

  M2MSecurity* registerObject =  
    connector->mbedClient.create_register_object();

  // Set endpoint registration object
  connector->mbedClient.set_register_object(registerObject);

  connector->mbedClient.test_register(registerObject, objectList);

  state = UPDATE;
}


void ConnectorClientStateMachine::Update()
{
  DebugClass::Print("Start Updateing");
  
  std::stringstream stream;
  for(uint32_t i = 0; i < values.size(); i+=2)
  {
    stream << std::fixed << std::setprecision(0) << values[i]*10000 << ",";
    stream << std::fixed << std::setprecision(0) << values[i+1] << ";";
  }
 
  string s = stream.str();
  
  char sArray[s.size()];
  strcpy(sArray, s.c_str());

  valueAdc.setValue((uint8_t*)sArray, s.size());

  if(connector->mbedClient.register_successful())
  {
    connector->mbedClient.test_update_register();
  }
  else
  {
    DebugClass::Print("Registration in progress");
  }
}


void ConnectorClientStateMachine::Unregister()
{
  // TODO
}


void ConnectorClientStateMachine::Detach()
{
  // TODO
}


void ConnectorClientStateMachine::Error()
{
  //rtos::Thread::wait(5000);
}
