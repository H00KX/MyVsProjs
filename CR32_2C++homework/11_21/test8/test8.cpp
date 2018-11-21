#include <iostream>
#include <ctime>

/*
8.��������������ͬ�ĺ���f1()��f2()��f1()������������f2()�Ƿ�����������
    ʹ��<ctime>�еı�׼C�⺯��clock()��������������Ŀ�ʼ��ͽ����㣬
    �Ƚ����ǿ���һ�����еø��죬Ϊ�˵õ���Ч�����֣�
    Ҳ����Ҫ�ڼ�ʱѭ�����ظ�����������������
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