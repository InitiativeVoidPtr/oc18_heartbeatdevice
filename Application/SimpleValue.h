///////////////////////////////////////////////////////////
//  SimpleValue.h
//  Declaration of the class SimpleValue
//  Created on:      20-Mar-2018 18:47:28
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef SIMPLEVALUE_H
#define SIMPLEVALUE_H

#include "mbed-client/m2mobject.h"

class SimpleValue
{
public:
  SimpleValue(void);

  M2MObject* GetObject(void);

  void setValue(float  value);

private:
  M2MObject* valueObject;
  float value;

};

#endif // SIMPLEVALUE_H

