#include <iostream>

/*
    4. дһ���������ú���ʹ��ָ����Ϊ������
        �޸�ָ����ָ���ݣ�Ȼ�������÷���ָ����ָ�����ݡ�

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