#include <iostream>


/*
5. ����һ��������ʹ֮����Ϊһ��ָ��ָ���ָ������ã�
        Ҫ��ú���������������޸ġ�Ȼ����main()�е������������

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