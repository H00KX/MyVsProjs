// CMyString.cpp : 定义控制台应用程序的入口点。
//
#include "CMyString.h"
#include "MyRefCount.h"


CMystring::CMystring()
{
    InitSelf();
}

CMystring::CMystring(const char * pStr)
{
    m_Ref = new CRefCount(pStr);
}

CMystring::CMystring(CMystring & obj)
{
    m_Ref = obj.m_Ref;
    obj.m_Ref->Add();
}

CMystring::~CMystring()
{
    if (m_Ref != nullptr)
    {
        m_Ref->Dec();
    }
}

CMystring & CMystring::operator=(CMystring & obj)
{
    if (this == &obj)
    {
        return *this;
    }
    if (m_Ref != nullptr)
    {
        m_Ref->Dec();
    }

    m_Ref = obj.m_Ref;
    obj.m_Ref->Add();

    return *this;
}

CMystring & CMystring::operator+(const char * pStr)
{
    Cat(pStr);
    return *this;
}

CMystring & CMystring::operator+=(const char * pStr)
{
    Cat(pStr);
    return *this;

}

inline int CMystring::GetBufferSize() const
{
    return m_Ref->BufLen;
}

inline int CMystring::GetStrlen() const
{
    return m_Ref->Len;
}

/************************************/
int CMystring::Format(const char * strFormat, ...)
{
    return 0;
}

int CMystring::Cmp(const char * strSrc) const
{
    return strcmp(m_Ref->Str(), strSrc);
}

int CMystring::Cmp(const CMystring & strCmp) const
{
    return strcmp(m_Ref->Str(), strCmp.m_Ref->Str());
}

char * CMystring::GetBuffer(int nMinBuffLen)
{
    return m_Ref->Str();
}

char * CMystring::GetStr() const
{
    return m_Ref->Str();
}

/************************************/
int CMystring::SetStr(const char * strSrc)
{
    return 0;
}

/************************************/
void CMystring::Cat(const char * strCat)
{
}

void CMystring::InitSelf()
{
    m_Ref = nullptr;
}

void CMystring::ReleaseSelf()
{
    if (m_Ref != nullptr)
    {
        m_Ref->Dec();
    }
}


void CMystring::ToUpper()
{
    _strupr_s(m_Ref->Str(), m_Ref->Len());
}


void CMystring::ToLower()
{
    _strlwr_s(m_Ref->Str(), m_Ref->Len());
}
