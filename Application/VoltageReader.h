///////////////////////////////////////////////////////////
//  VoltageReader.h
//  Declaration of the class VoltageReader
//  Created on:      11-Feb-2018 11:15:56
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef VOLTAGEREADER_H
#define VOLTAGEREADER_H

#include <vector>
#include "AnalogIn.h"


class VoltageReader
{
public:
  VoltageReader();
  float GetRawValue(uint32_t index);
  uint32_t GetVoltageCount(void);
  
private:
  std::vector<mbed::AnalogIn> ain;
};

#endif //VOLTAGEREADER_H
