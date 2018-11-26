// class_2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Myclock
{
private:
    int m_nHour;
    int m_nMinute;
    int m_nSecond;

public:
    void SetTime(int nH, int nM, int nS);
    void ShowTime();
    int GetH();
    int GetM();
};

void Myclock::SetTime(int nH, int nM, int nS)
{
    if (nH >= 0 && nH <= 24)
    {
        m_nHour = nH;
    }
    if (nM >= 0 && nM <= 60)
    {
        m_nMinute = nM;
    }
    if (nS >= 0 && nS <= 60)
    {
        m_nSecond = nS;
    }
}

void Myclock::ShowTime()
{
    cout << "H: " << m_nHour << endl;
    cout << "M: " << m_nMinute << endl;
    cout << "S: " << m_nSecond << endl;
}

int Myclock::GetH()
{
    return m_nHour;
}

int Myclock::GetM()
{
    return m_nMinute;
}



int main()
{
    Myclock Mc;
    Mc.SetTime(12, 6, 3);
    Mc.ShowTime();
    
    return 0;
}

