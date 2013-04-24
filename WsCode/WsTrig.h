#if !defined(_WSTRIG_H)
#define _WSTRIG_H

#include <stdio.h>
#include <math.h>

//Pi.  It needs to be more rational.
#define PI 3.1415926535897932384626433832795

//Wrapper for the atan2 function from math.h which returns degrees.
#define ATAN2DEG(y, x) (atan2((float)y, (float)x) * 180 / PI)

//Wrapper for the sine funtion from math.h which accepts degrees.
#define SINDEG(x) (sin(((float)x) * PI / 180))

//Wrapper for the cosine function from math.h which accepts degrees.
#define COSDEG(x) (cos(((float)x) * PI / 180))

//Wrapper for the tangent function from math.h which accepts degrees.
#define TANDEG(x) (tan(((float)x) * PI / 180))

#endif
