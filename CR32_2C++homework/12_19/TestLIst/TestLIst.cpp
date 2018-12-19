// TestLIst.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include "MyList.h"

////链表
//void foo_list() {
//    std::list<int> lt;
//    for (int i = 1; i < 4; i++){
//        lt.push_back(i);
//    }
//
//    for (std::list<int>::iterator it = lt.begin();
//         it != lt.end(); it++){
//        printf("%d ", *it);
//    }
//
//    printf("\r\n");
//}

void foo_My()
{
    CMyList lt;
    CMyList::CMyNode* p = nullptr;

    bool bEmp = lt.empty();
    int nSize = lt.size();

    CMyList::CMyNode p1 = lt.front();



    //输入
    for (int i = 0; i < 1; i++)
    {
        lt.push_back(i);
    }




    //输出
    p = lt.m_pHead->m_pNext;
    while (p != nullptr)
    {
        printf("%d", p->m_data);
        p = p->m_pNext;
    }

}

int main()
{
    foo_My();

    return 0;
}

