#include <stdio.h>



/*

�ֱ�ʹ��C��C++��������Ĵ��룬������ʲô����Ϊʲô?
*/

struct bird
{
    int nBird;
};

struct rock
{
    int rock;
};

void main()
{
    struct bird* b;
    struct rock* r;
    void* v;
    v = r;
    b = v;          //  C   ������������
}