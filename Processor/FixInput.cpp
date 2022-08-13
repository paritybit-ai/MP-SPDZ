/*
 * FixInput.cpp
 *
 */

#include "FixInput.h"
#include "Tools/MemoryStream.h"

#include <math.h>

template<>
void FixInput_<Integer>::read(std::istream& in, const int* params, int nmemflag)
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
    items[0] = x * exp2(*params);
}

template<>
void FixInput_<bigint>::read(std::istream& in, const int* params, int nmemflag)
{
#ifdef HIGH_PREC_INPUT
    mpf_class x;
    if (0 == nmemflag)
    {
        in >> x;
    }
    else
    {
        CMemoryStream& memStream = dynamic_cast<CMemoryStream&>(in);
        memStream >> x;
    }
//    in >> x;
    items[0] = x << *params;
#else
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
    items[0] = x * exp2(*params);
#endif
}
