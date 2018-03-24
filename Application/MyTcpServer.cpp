///////////////////////////////////////////////////////////
//  MyTcpServer.cpp
//  Definition of the class MyTcpServer
//  Created on:      16-Feb-2018 18:26:23
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "MyTcpServer.h"

MyTcpServer::MyTcpServer()
: port(1337),
  simultanConnections(1),
  stateMachine(TcpStateMachine(this))
{
  ;
}

void MyTcpServer::Start()
{
  stateMachine.Start();
}

void MyTcpServer::Run()
{
  stateMachine.Run();
}
