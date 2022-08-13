
#ifndef __MEMORY_SSTREAM__
#define __MEMORY_SSTREAM__

#include <iostream>
#include <vector>

using namespace std;

typedef enum _tagEMEMINPUTTYPE{
    EMEMINPUTTYPE_NONE              = 0,    //  默认从文件读取
    EMEMINPUTTYPE_VECTORES_INT      = 1,    //  
    EMEMINPUTTYPE_VECTORES_FLOAT    = 2,    //  
    EMEMINPUTTYPE_VECTORES_FIX      = 3,    //  
}EMEMINPUTTYPE, *LPEMEMINPUTTYPE;

typedef struct _tagMEMINPUTCONTEXT{
    _tagMEMINPUTCONTEXT(){
        pInput = 0;
        nSize = 0;
        eType = EMEMINPUTTYPE_NONE;
    }
    void*   pInput;
    int     nSize;
    EMEMINPUTTYPE   eType;
}MEMINPUTCONTEXT, *LPMEMINPUTCONTEXT;

class CBuffer : public streambuf
{
public:
    CBuffer(){
    }
};

class CMemoryStream : public istream
{
public:
    CMemoryStream() : istream(NULL){

    }
    virtual ~CMemoryStream(){

    }

public:
    virtual int peek(){ return 0; }
    virtual CMemoryStream& operator>>(short& __n) = 0;
    virtual CMemoryStream& operator>>(unsigned short& __n) = 0;
    virtual CMemoryStream& operator>>(int& __n) = 0;
    virtual CMemoryStream& operator>>(unsigned int& __n) = 0;
    virtual CMemoryStream& operator>>(long& __n) = 0;
    virtual CMemoryStream& operator>>(unsigned long& __n) = 0;
#ifdef _GLIBCXX_USE_LONG_LONG
    virtual CMemoryStream& operator>>(long long& __n) = 0;
    virtual CMemoryStream& operator>>(unsigned long long& __n) = 0;
#endif
    virtual CMemoryStream& operator>>(float& __f) = 0;
    virtual CMemoryStream& operator>>(double& __f) = 0;
    virtual CMemoryStream& operator>>(long double& __f) = 0;
};

template<class T>
class CVectorStream : public CMemoryStream
{
public:
    CVectorStream(){
        init(&m_Buf);
    }
    CVectorStream(vector<T>& vec){
        init(&m_Buf);
        open(vec);
    }
    virtual ~CVectorStream(){

    }
    int open(vector<T>& vec){
        m_pValue = &vec;
        m_nSize = m_pValue->size();
        m_nPos = 0;
        return 0;
    }
    int close(){
        m_pValue = NULL;
        m_nSize = 0;
        m_nPos = 0;
        return 0;
    }
    virtual int peek(){
        if (m_nPos < m_nSize){
            return 0;
        }
        return EOF;
    }

public:
    virtual CMemoryStream& operator>>(short& __n){
        return _M_extract(__n);
    }
    virtual CMemoryStream& operator>>(unsigned short& __n){
        return _M_extract(__n);
    }
    virtual CMemoryStream& operator>>(int& __n){
        return _M_extract(__n);
    }
    virtual CMemoryStream& operator>>(unsigned int& __n){
        return _M_extract(__n);
    }
    virtual CMemoryStream& operator>>(long& __n){
        return _M_extract(__n);
    }
    virtual CMemoryStream& operator>>(unsigned long& __n){
        return _M_extract(__n);
    }
#ifdef _GLIBCXX_USE_LONG_LONG
    virtual CMemoryStream& operator>>(long long& __n){
        return _M_extract(__n);
    }
    virtual CMemoryStream& operator>>(unsigned long long& __n){
        return _M_extract(__n);
    }
#endif
    virtual CMemoryStream& operator>>(float& __f){
        return _M_extract(__f);
    }
    virtual CMemoryStream& operator>>(double& __f){
        return _M_extract(__f);
    }
    virtual CMemoryStream& operator>>(long double& __f){
        return _M_extract(__f);
    }
    template<class MT >
    CMemoryStream& _M_extract(MT& __v){
        this->setstate(ios_base::goodbit);
        if (NULL == m_pValue){
	    this->setstate(ios_base::badbit);
        }
        else if (m_nPos < m_nSize){
            __v = m_pValue->at(m_nPos);
            m_nPos ++;
            if (m_nPos == m_nSize){
	        this->setstate(ios_base::eofbit);
            }
        }
        else{
	        this->setstate(ios_base::badbit);
        }
        return *this;
    }

private:
    vector<T >* m_pValue;
    int         m_nPos;
    int         m_nSize;
    CBuffer     m_Buf;
};

#endif /* __MEMORY_SSTREAM__ */
