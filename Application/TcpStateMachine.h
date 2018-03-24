///////////////////////////////////////////////////////////
//  TcpStateMachine.h
//  Declaration of the class TcpStateMachine
//  Created on:      17-Feb-2018 13:25:48
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef TCPSTATEMACHINE_H
#define TCPSTATEMACHINE_H

class MyTcpServer;

class TcpStateMachine
{
public:
  void Start(void);
  void Run(void);

  TcpStateMachine(MyTcpServer* server);

private:
  enum State
  {
    IDLE,
    CONNECTING,
    OPENING,
    BINDING,
    LISTENING,
    ACCEPTING,
    RUNNING,
    ERROR
  };

  MyTcpServer* server;

  void Connecting(void);
  void Opening(void);
  void Binding(void);
  void Listening(void);
  void Accepting(void);
  void Running(void);
  void Error(void);

  State state;
};


#endif // TCPSTATEMACHINE_H
