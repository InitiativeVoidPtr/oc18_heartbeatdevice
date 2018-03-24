///////////////////////////////////////////////////////////
//  Communication.cpp
//  Definition of the class Communication
//  Created on:      11-Feb-2018 17:18:47
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "Communication.h"
#include "DebugClass.h"

nsapi_error_t Communication::Connect()
{
  DebugClass::Print("Bringing up the ethernet interface");
  nsapi_error_t error = EthernetInterface::connect();

  if(0 != error)
  {
    DebugClass::Print("Error during networt connection: ", error);
  }
  else
  {
    DebugClass::Print("Connection established");
    PrintNetworkInfo();
  }

  return error;
}

void Communication::PrintNetworkInfo()
{
  DebugClass::Print("IP address: ", EthernetInterface::get_ip_address());
  DebugClass::Print("MAC address: ", EthernetInterface::get_mac_address());
  DebugClass::Print("Netmask: ", EthernetInterface::get_netmask());
  DebugClass::Print("Gateway: ", EthernetInterface::get_gateway());
}
