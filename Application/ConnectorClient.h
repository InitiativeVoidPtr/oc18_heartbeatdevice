///////////////////////////////////////////////////////////
//  ConnectorClient.h
//  Definition of the class ConectorClient
//  Created on:      17-Mar-2018 22:42:32
//  Original author: Vitalij
///////////////////////////////////////////////////////////
#ifndef CONNECTORCLIENT_H
#define CONNECTORCLIENT_H

#include "Simpleclient.h"
#include "EthernetInterface.h"
#include "ConnectorClientStateMachine.h"

class ConnectorClient
{
public:
  ConnectorClient(void);
  void Start(void);
  void Run(void);

private:
  MbedClient mbedClient;
  EthernetInterface eth;

  ConnectorClientStateMachine stateMachine;

  friend class ConnectorClientStateMachine;
};

#endif //CONNECTORCLIENT_H
