#include <iostream>
#include <ctime>

/*
8.创建两个功能相同的函数f1()和f2()，f1()是内联函数，f2()是非内联函数。
    使用<ctime>中的标准C库函数clock()标记这两个函数的开始点和结束点，
    比较它们看哪一个运行得更快，为了得到有效的数字，
    也许需要在计时循环中重复调用这两个函数。
*/

void funA()
{
    int a = 5;
    a++;

}

inline void funB()
{
    int a = 5;
    a++;
}

int main()
{
    int nIndex = 0;
    long lTimeStart = clock();

    while (nIndex < 1000000)
    {
        funA();
        nIndex++;
    }

    long lTimeEnd = clock();
    printf("No Inline times: %ld\r\n", lTimeEnd - lTimeStart);

    nIndex = 0;
    lTimeStart = clock();
    while (nIndex < 1000000)
    {
        funB();
        nIndex++;
    }
    lTimeEnd = clock();
    printf("Inline times: %ld", lTimeEnd - lTimeStart);

}