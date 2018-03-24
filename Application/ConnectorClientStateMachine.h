///////////////////////////////////////////////////////////
//  ConnectorClientStateMachine.h
//  Declaration of the class ConnectorClientStateMachine
//  Created on:      18-Mar-2018 13:01:28
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef CONNECTORCLIENTSTATEMACHINE_H
#define CONNECTORCLIENTSTATEMACHINE_H

#include "m2mnsdlinterface.h"
#include "SimpleValue.h"
#include "mbed-client/m2mdevice.h"

class ConnectorClient;

class ConnectorClientStateMachine
{
public:
  void Start(void);
  void Run(void);

  ConnectorClientStateMachine(ConnectorClient* connector);

private:
  enum State
  {
    IDLE,
    CONNECTING,
    SETUP,
    REGISTER,
    UPDATE,
    UNREGISTER,
    DETACH,
    ERROR
  };

  ConnectorClient* connector;
  M2MObjectList objectList;
  SimpleValue value;


  void Connecting(void);
  void Setup(void);
  void Register(void);
  void Update(void);
  void Unregister(void);
  void Detach(void);
  void Error(void);

  State state;

  void PrintNetworkInfo(void);
};


#endif // CONNECTORCLIENTSTATEMACHINE_H
