#include <iostream>

/*
    9.举例说明何时使用函数默认参及使用时需要注意的什么。

*/

////如下定义报错：默认实参不再形参列表的结尾
//void fun(int a, int b = 3, int c)
//{
//
//}


//如下定义才正确
void fun(int a, int b, int c = 0)
{

}



int main()
{
    fun(1, 2);
    fun(1, 2, 0);
}