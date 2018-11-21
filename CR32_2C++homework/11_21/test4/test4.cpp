#include <iostream>

/*
    4. 写一个函数，该函数使用指针作为参数，
        修改指针所指内容，然后用引用返回指针所指的内容。

*/

int&    Fun(int* rp)
{

    int &refP = *rp;

    (*rp)++;


    return refP;
}


int main()
{
    int nNum = 6;
    int *nP = &nNum;
    int &refN = Fun(nP);

    printf("%d", nNum);
}