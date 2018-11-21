#include <stdio.h>



/*

分别使用C和C++编译下面的代码，看看有什么区别，为什么?
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
    b = v;          //  C   可以正常编译
}