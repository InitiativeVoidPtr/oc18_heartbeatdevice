///////////////////////////////////////////////////////////
//  VoltageReader.cpp
//  Implementation of the class VoltageReader
//  Created on:      11-Feb-2018 11:29:15
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "VoltageReader.h"
#include "SystemTime.h"


VoltageReader::VoltageReader()
{
  ain.push_back(mbed::AnalogIn(A0));
  ain.push_back(mbed::AnalogIn(A1));
  ain.push_back(mbed::AnalogIn(A2));
  ain.push_back(mbed::AnalogIn(A3));
}

float VoltageReader::GetRawValue(uint32_t index)
{
  float returnValue = 0;
  
  if(index < ain.size())
  {
    returnValue = ain[index];
  }
  
  return returnValue;
}

float VoltageReader::GetRawValueWithTimeStamp(uint32_t index, uint32_t& timeStamp)
{
  float returnValue = 0;
  
  if(index < ain.size())
  {
    returnValue = ain[index];
    timeStamp = SystemTime::GetActualTimeMs();
  }
  
  return returnValue;
}


uint32_t VoltageReader::GetVoltageCount()
{
  return ain.size();
}
