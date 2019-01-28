#include "qsutil.h"
#include <math.h>

float eswapFloat(const float *f)
{
    const unsigned char *p = (const unsigned char *)f;
    unsigned char buf[4];
    buf[0] = p[3];
    buf[1] = p[2];
    buf[2] = p[1];
    buf[3] = p[0];
    return *(float*)buf;
}
