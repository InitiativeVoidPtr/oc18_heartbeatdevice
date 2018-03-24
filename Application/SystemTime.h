///////////////////////////////////////////////////////////
//  SystemTime.h
//  Declaration of the class SystemTime
//  Created on:      24-Mar-2018 21:37:56
//  Original author: Jannis
///////////////////////////////////////////////////////////

#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H

#include <stdint.h>

class SystemTime
{
public:
  SystemTime();
  static uint32_t GetActualTimeUs(void);
  static uint64_t GetActualTimeMs(void);
  
private:

};

#endif //SYSTEMTIME_H
