// class_7.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class EmptyCls
{
public:
    EmptyCls();
    ~EmptyCls();

private:

};

EmptyCls::EmptyCls()
{
}

EmptyCls::~EmptyCls()
{
}


struct EmptySt
{

};

int main()
{
    EmptyCls Ec;
    EmptySt Es;

    cout << "sizeof EMPTY CLASS: " << sizeof(Ec) << endl;
    cout << "sizeof EMPTY STRUCT: " << sizeof(Es) << endl;

    return 0;
}

