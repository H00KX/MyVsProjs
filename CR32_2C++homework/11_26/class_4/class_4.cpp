// class_4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class CL1
{
public:

    char name[16];

    void PrintAnother(CL2 *c2);


};

class CL2
{
public:

    char name[16];

    void PrintAnother(CL1 *c1);


};



int main()
{
    CL1 c1;
    CL2 c2;

    c1.name[0] = '1';
    c2.name[0] = '2';

    c1.PrintAnother(&c2);
    c2.PrintAnother(&c1);

    return 0;
}

void CL1::PrintAnother(CL2 *c2)
{
    cout << c2->name << endl;
}

void CL2::PrintAnother(CL1 *c1)
{
    cout << c1->name << endl;
}
