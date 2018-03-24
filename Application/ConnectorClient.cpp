///////////////////////////////////////////////////////////
//  ConnectorClient.cpp
//  Declaration of the class ConectorClient
//  Created on:      17-Mar-2018 22:42:34
//  Original author: Vitalij
///////////////////////////////////////////////////////////
#include "ConnectorClient.h"
#include "mbedtls/entropy_poll.h"


struct MbedClientDevice device = {
  "Initiative-void*",         // Manufacturer
  "Heartbeat",                // Type
  "0x0001",                   // ModelNumber
  "0x00000001"                // SerialNumber
};

ConnectorClient::ConnectorClient()
  :mbedClient(device),
  stateMachine(ConnectorClientStateMachine(this))
{
  unsigned int seed;
  size_t len;
  
  mbedtls_hardware_poll(NULL, (unsigned char *) &seed, sizeof seed, &len);
  srand(seed);
}

void ConnectorClient::Start()
{
  stateMachine.Start();
}

void ConnectorClient::Run()
{
  stateMachine.Run();
}
