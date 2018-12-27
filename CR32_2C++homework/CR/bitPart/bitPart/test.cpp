#include <stdio.h>
#include <stdlib.h>

struct BitPart
{
    int a : 1;
    int e : 1;
    //int : 0;
    int b : 1;
    int c : 3;
    char d : 7;
}bp;


int main()
{
    bp.a = 0xffffffff;
    bp.e = 0xffffffff;
    bp.b = 0xffffffff;
    bp.d = 0xffffffff;

    system("pause");
    return 0;
}