// test3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "NamespaceInt.h"


/*

    ���ļ�Arithmetic.cpp�У�
    ˵����һ��������ʹ�õ�usingָ�������չ����������ķ�Χ֮�⡣


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

    //�����ˣ�δ�����ʶ��
    Integer x;


    return 0;
}

