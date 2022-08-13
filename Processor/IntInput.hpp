/*
 * IntInput.cpp
 *
 */

#ifndef PROCESSOR_INTINPUT_HPP_
#define PROCESSOR_INTINPUT_HPP_

#include "IntInput.h"
#include "Tools/MemoryStream.h"

template<class T>
const char* IntInput<T>::NAME = "integer";

template<class T>
void IntInput<T>::read(std::istream& in, const int*, int nmemflag)
{
    if (0 == nmemflag)
    {
        in >> items[0];
    }
    else
    {
        CMemoryStream& memStream = dynamic_cast<CMemoryStream&>(in);
        memStream >> items[0];
    }
}

#endif
