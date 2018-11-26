// class_3.cpp : 定义控制台应用程序的入口点。
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
    //“test::b”: 无法访问 protected 成员(在“test”类中声明)
    t.c = 6;
    //“test::c”: 无法访问 private 成员(在“test”类中声明)

    return 0;
}

