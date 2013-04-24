#include <stdio.h>
#include "test.h"
#include "test.h"

#define PI  3.14
#define FWD 0

#define ADD(a, b)  ((a) + (b))

#define PI2 PI

int z;

#define MYVARIABLE z

int main(void)
{
    int x;
    int y;

    x = 0;
    y = FWD;

    y = ADD(x, y);
    y = ((x) + (y));

    MYVARIABLE = 1;

    return 1;
}
