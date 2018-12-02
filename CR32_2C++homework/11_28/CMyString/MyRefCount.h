#include <iostream>
//引用计数


class CRefCount
{
public:
    CRefCount(const char* pszName)
    {
        m_nCount = 1;
        m_nStrLen = strlen(pszName);
        m_nBuffLen = m_nStrLen + 1;

        char* pBuf = new char[strlen(pszName) + 1];
        strcpy_s(pBuf, strlen(pszName) + 1, pszName);

        m_pStr = pBuf;

    }

    ~CRefCount()
    {
        if (m_pStr != nullptr)
        {
            delete[] m_pStr;
        }
    }

    void Add()
    {
        m_nCount++;
    }

    void Dec()
    {
        if (--m_nCount == 0)
        {
            delete  this; //对象自杀
        }
    }

    int Len()
    {
        return m_nStrLen;
    }

    int BufLen()
    {
        return m_nBuffLen;
    }

    char *Str()
    {
        return m_pStr;
    }


private:
    int m_nCount;
    int m_nBuffLen;
    int m_nStrLen;
    char *m_pStr;
};