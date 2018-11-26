// class_8.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Test
{
private:
    int nVar;
public:
    void tFun(int a);
};


typedef void(Test::*PFN_tFun)(int a);


int main()
{
    Test t;
    PFN_tFun pfn;
    pfn = &Test::tFun;

    t.tFun(1);

    (t.*pfn)(2);

    return 0;
}

void Test::tFun(int a)
{
    nVar = a;
}
