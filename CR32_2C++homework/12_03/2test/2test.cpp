// 2test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


class A
{
public:
    A()
    {

    };
    ~A() = default;
};

class B
{
public:
    B()
    {

    };
    ~B() = default;

};

class C :public A
{
    B nb;
};



int main()
{
    C nc;

    C t = nc;

    return 0;
}

