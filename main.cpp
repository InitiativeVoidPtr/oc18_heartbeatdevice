// main() runs in its own thread in the OS

#include "Blinky.h"
#include "Application.h"
#include "mbed-trace/mbed_trace.h"

int main() 
{
  mbed_trace_init();
 
  Blinky blinky(LED1);
  Application app;
  
  app.Run();

  for(;;) 
  {
    blinky.HeartBeat();
  }
}
