// class_3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


class test
{
public:
    int a;
protected:
    int b;
private:
    int c;
};

int main()
{
    test t;
    t.a = 0;
    t.b = 2;
    //��test::b��: �޷����� protected ��Ա(�ڡ�test����������)
    t.c = 6;
    //��test::c��: �޷����� private ��Ա(�ڡ�test����������)

    return 0;
}

