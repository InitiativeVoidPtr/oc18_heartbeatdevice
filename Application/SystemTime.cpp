///////////////////////////////////////////////////////////
//  SystemTime.cpp
//  Implementation of the class SystemTime
//  Created on:      11-Feb-2018 11:29:15
//  Original author: Jannis
///////////////////////////////////////////////////////////

#include "SystemTime.h"
#include "rtx_os.h"


SystemTime::SystemTime()
{
  // do nothing
}

uint32_t SystemTime::GetActualTimeUs(void)
{
  return ( (uint64_t)osKernelGetSysTimerCount()*1000000U ) / osKernelGetSysTimerFreq() ;
}


uint32_t SystemTime::GetActualTimeMs(void)
{
  return ( (uint64_t)osKernelGetSysTimerCount()*1000U ) / osKernelGetSysTimerFreq() ;
}
