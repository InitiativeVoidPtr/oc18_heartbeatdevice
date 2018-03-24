///////////////////////////////////////////////////////////
//  Communication.h
//  Declaration of the class Communication
//  Created on:      10-Feb-2018 17:17:35
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "EthernetInterface.h"

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

class Communication : public EthernetInterface
{
public:
  nsapi_error_t Connect();

private:
  void PrintNetworkInfo();
};


#endif // COMMUNICATION_H
