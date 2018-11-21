#include <iostream>

/*
    6. 创建一个函数，使其用char&作参数并修改该参数。在main()函数里，
    打印一个char变量，使用这个变量做参数，调用我们设计的函数。
    然后，再次打印此变量以证明它已被改变。请问这影响了程序的可读性吗？

*/


void fun(char &pc)
{
    pc += 1;
}

int main()
{
    char ch = 'a';
    printf("%c", ch);

    fun(ch);
    printf("%c", ch);

}