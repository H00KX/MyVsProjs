// 6convert.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//基类
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


//私有继承
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


//保护继承
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


    //报错，不允许对不可访问的基类进行转换

    Test t1 = cpri;
    Test t2 = cprot;


    return 0;
}


