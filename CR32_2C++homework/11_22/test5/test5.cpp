// test5.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>


using namespace std;

int main()
{
    float fT = 2.45;

    cout.setf(ios::dec);
    cout << fT << endl;

    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << fT << endl;

    cout.unsetf(ios::hex);
    cout.precision(6);
    cout << fT << endl;

    return 0;
}

