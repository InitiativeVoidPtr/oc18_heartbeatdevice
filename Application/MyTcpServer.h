///////////////////////////////////////////////////////////
//  MyTcpServer.h
//  Declaration of the class MyTcpServer
//  Created on:      16-Feb-2018 18:12:14
//  Original author: Vitalij
///////////////////////////////////////////////////////////
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include "TCPServer.h"
#include "Communication.h"
#include "TcpStateMachine.h"

class MyTcpServer : private TCPServer
{
public:
  MyTcpServer(void);
  void Start(void);
  void Run(void);

private:
  Communication eth;
  std::uint16_t port;
  std::int32_t simultanConnections;

  TcpStateMachine stateMachine;

  TCPSocket clientSock;
  SocketAddress clientAddr;

  friend class TcpStateMachine;
};


#endif // MYTCPSERVER_H
