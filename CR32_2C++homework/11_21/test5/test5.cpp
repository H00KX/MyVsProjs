#include <iostream>


/*
5. 创建一个函数，使之参数为一个指向指针的指针的引用，
        要求该函数对其参数进行修改。然后，在main()中调用这个函数。

*/

void fun(int** &p)
{
    p = p - 1;
    p = p + 1;
}


int main()
{
    int nA = 1;
    int *nPa = &nA;
    int **nPpa = &nPa;

    fun(nPpa);

}