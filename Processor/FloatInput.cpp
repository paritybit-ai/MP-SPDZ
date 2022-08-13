/*
 * FloatInput.cpp
 *
 */

#include "FloatInput.h"
#include "Tools/MemoryStream.h"

#include <math.h>

const char* FloatInput::NAME = "real number";

void FloatInput::read(std::istream& in, const int* params, int nmemflag)
{
    double x;
    if (0 == nmemflag)
    {
        in >> x;
    }
    else
    {
        CMemoryStream& memStream = dynamic_cast<CMemoryStream&>(in);
        memStream >> x;
    }
    int exp;
    double mant = fabs(frexp(x, &exp));

    items[0] = round(mant * (1LL << *params));
    items[1] = exp - *params;
    items[2] = (x == 0);
    items[3] = (x < 0);
}
