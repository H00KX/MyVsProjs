// TestLIst.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <list>
#include "MyList.h"

////����
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



    //����
    for (int i = 0; i < 1; i++)
    {
        lt.push_back(i);
    }




    //���
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

