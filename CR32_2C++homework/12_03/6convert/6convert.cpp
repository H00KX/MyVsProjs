// 6convert.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//����
class Test
{
public:
    Test(int nA)
    {
        a = nA;
    }

    ~Test() = default;

public:
    int a;

};


//˽�м̳�
class CPri :private Test
{
public:
    CPri(int nA, int nB) :Test(nA)
    {
        m_pri = nB;
    }

private:
    int m_pri;
};


//�����̳�
class CProt :protected Test
{
public:
    CProt(int nA, int nB) :Test(nA)
    {
        m_prot = nB;
    }

protected:
    int m_prot;
};


int main()
{

    CPri cpri(3, 4);

    CProt cprot(5, 6);


    //����������Բ��ɷ��ʵĻ������ת��

    Test t1 = cpri;
    Test t2 = cprot;


    return 0;
}


