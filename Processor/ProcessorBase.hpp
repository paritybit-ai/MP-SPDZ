/*
 * ProcessorBase.cpp
 *
 */

#ifndef PROCESSOR_PROCESSORBASE_HPP_
#define PROCESSOR_PROCESSORBASE_HPP_

#include "ProcessorBase.h"
#include "IntInput.h"
#include "FixInput.h"
#include "FloatInput.h"
#include "Tools/Exceptions.h"

#include <iostream>

inline
void ProcessorBase::open_input_memory(void* pValue, int thread_num)
{
    if (nullptr != pmem_stream)
    {
        delete pmem_stream;
        pmem_stream = nullptr;
    }
    //  get the vector of input with the thread_num
    LPMEMINPUTCONTEXT pContext = (LPMEMINPUTCONTEXT)pValue;
    if (pContext->nSize <= thread_num)
    {
        return ;
    }
    switch (pContext->eType)
    {
    case EMEMINPUTTYPE_VECTORES_INT:
        {
            vector<int>* pVecInput = (vector<int>*)pContext->pInput;
            vector<int>& pValue = pVecInput[thread_num];
            CVectorStream<int>* pVecStream = new CVectorStream<int>();
            pVecStream->open(pValue);
            pmem_stream = pVecStream; 
        }break;
    case EMEMINPUTTYPE_VECTORES_FLOAT:
        {
            vector<double>* pVecInput = (vector<double>*)pContext->pInput;
            vector<double>& pValue = pVecInput[thread_num];
            CVectorStream<double>* pVecStream = new CVectorStream<double>();
            pVecStream->open(pValue);
            pmem_stream = pVecStream; 
        }break;
    default:
        break;
    }
}

inline
void ProcessorBase::open_input_file(const string& name)
{
#ifdef DEBUG_FILES
    cerr << "opening " << name << endl;
#endif
    input_file.open(name);
    input_filename = name;
}

template<class T>
T ProcessorBase::get_input(bool interactive, const int* params)
{
    if (nullptr != pmem_stream)
        return get_input_mem<T>(*pmem_stream, "memory input", params);
    if (interactive)
        return get_input<T>(cin, "standard input", params);
    else
        return get_input<T>(input_file, input_filename, params);
}

template<class T>
T ProcessorBase::get_input(istream& input_file, const string& input_filename, const int* params)
{
    T res;
    if (input_file.peek() == EOF)
        throw IO_Error("not enough inputs in " + input_filename);
    res.read(input_file, params);
    if (input_file.fail())
    {
        throw input_error(T::NAME, input_filename, input_file, input_counter);
    }
    input_counter++;
    return res;
}

template<class T>
T ProcessorBase::get_input_mem(CMemoryStream& input_file, const string& input_filename, const int* params)
{
    T res;
    if (input_file.peek() == EOF)
        throw IO_Error("not enough inputs in " + input_filename);
    res.read(input_file, params, true);
    if (input_file.fail())
    {
        throw input_error(T::NAME, input_filename, input_file, input_counter);
    }
    input_counter++;
    return res;
}

#endif
