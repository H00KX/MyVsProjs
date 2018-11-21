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
    b = v;      //C++  报错：不能将“void *”类型值分配到“bird *”类型的实体
}