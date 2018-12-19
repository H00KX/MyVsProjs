#include "stdafx.h"
#include "MyList.h"
#include <iostream>

using std::range_error;

CMyList::CMyList()
{
    m_pHead = new CMyNode(0);
    m_nSize = 0;
}


CMyList::~CMyList()
{
}

//���ڱ���

//llvm, ollvm
void CMyList::push_back(const T_LIST int & n)
{

    CMyNode* p = new CMyNode(n);

    CMyNode* tmp = m_pHead;
    while (tmp->m_pNext != nullptr)
    {
        tmp = tmp->m_pNext;
    }

    tmp->m_pNext = p;
    p->m_pPre = tmp;

    m_nSize++;
    return;
}

//    head    1    2    3
//    head    0    1    2    3

void CMyList::push_front(const T_LIST int & n)
{

    CMyNode* pNew = new CMyNode(n);
    CMyNode* pNext = m_pHead->m_pNext;

    m_pHead->m_pNext = pNew;
    pNew->m_pPre = m_pHead;
    pNew->m_pNext = pNext;

    if (pNext != nullptr)
    {
        pNext->m_pPre = pNew;
    }

    m_nSize++;
}

void CMyList::pop_front()
{
    CMyNode* pFirst = m_pHead->m_pNext;

    if (pFirst != nullptr)
    {
        CMyNode *pSencod = pFirst->m_pNext;
        //�ͷŵ�һ����Ч�ڵ�
        delete pFirst;

        m_pHead->m_pNext = pSencod;
        pSencod->m_pPre = pSencod;
    }
}

void CMyList::pop_back()
{
    CMyNode* pCur = m_pHead;
    //��λ�����һ���ڵ�
    while (pCur->m_pNext != nullptr)
    {
        pCur = pCur->m_pNext;
    }

    //������һ���ڵ� ��ǰ�ڵ㣨��������Ч�ڵ㣩
    if (pCur->m_pPre != nullptr)
    {
        //��ɾ�����ͷ�
        pCur->m_pPre->m_pNext = nullptr;
        delete pCur;
        m_nSize--;
    }

}

CMyList::CMyNode & CMyList::front()
{
    // TODO: �ڴ˴����� return ���
    if (m_nSize <= 0)
    {
        throw new std::range_error("List has no elements");
    }

    CMyNode* pCur = m_pHead->m_pNext;
    return *pCur;
}

CMyList::CMyNode & CMyList::back()
{
    if (m_nSize <= 0)
    {
        throw new std::range_error("List has no elements");
    }

    // TODO: �ڴ˴����� return ���
    CMyNode* pCur = m_pHead->m_pNext;

    while (pCur != nullptr&&pCur->m_pNext != nullptr)
    {
        pCur = pCur->m_pNext;
    }

    return *pCur;
}

bool CMyList::empty() const
{
    if (m_nSize == 0)
    {
        return true;
    }

    return false;
}

size_t CMyList::size() const
{
    return m_nSize;
}

