#include <stdio.h>

#include "WsCamera.h"
#include "Timer.h"

int vision_task_main()
{
  bool keepGoing = true;


  // The silly camera has to boot up, give it some time
  Wait(3.0);
  printf("before axis cam\n");
  AxisCamera &axisCam = AxisCamera::GetInstance();
  printf("after axis cam\n");
  WsCamera camera = WsCamera(&axisCam);
  printf("after axis cam\n");

  /* loop fooooooorrrrrrreeeeeevvvvvveeeeerrrrrrr */
  while (keepGoing == true)
  {
      Wait(1.0);
  }

  return 0;
}

