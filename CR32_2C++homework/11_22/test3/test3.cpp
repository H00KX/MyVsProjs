// test3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NamespaceInt.h"


/*

    在文件Arithmetic.cpp中，
    说明在一个函数中使用的using指令并不能扩展到这个函数的范围之外。


*/


void arithmetic()
{
    using namespace Int;
    Integer x;
    x.setSign(positive);
}

int main()
{

    arithmetic();

    //报错了；未定义标识符
    Integer x;


    return 0;
}

