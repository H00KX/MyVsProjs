#include <iostream>

/*

写一个程序，在其中尝试以下操作：
(1)创建一个引用，在其创建时没有被初始化。
（2)在一个引用被初始化后，改变它的指向，使之指向另一个对象。
（3)创建一个NULL引用

*/

int main()
{
    ////报错，引用变量需要初始值设定项
    //int &refN;


    //int nVara = 1;
    //int nVarb = 2;
    //int &refN = nVara;
    //refN = nVarb;
    ////引用一旦建立映射关系后，无法更改引用的对象

    const int &RefN = NULL;
    //这里忘了为什么可以设定常量引用
}