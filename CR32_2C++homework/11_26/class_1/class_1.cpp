// class_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

typedef void(*PFN_SetTime)(void *st, int nH, int nM, int nS);

struct Myclock
{
    int m_nHour;
    int m_nMinute;
    int m_nSecond;

    PFN_SetTime pfn;
};

void SetTime(void *st, int nH, int nM, int nS)
{
    ((Myclock*)st)->m_nHour = nH;
    ((Myclock*)st)->m_nMinute = nM;
    ((Myclock*)st)->m_nSecond = nS;
}


int main()
{
    struct Myclock  Mc;

    Mc.pfn=SetTime;

    Mc.pfn(&Mc, 1, 2, 3);

    return 0;
}

