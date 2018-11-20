// StringManage.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "stringManage.h"

extern TCHAR       g_tszManaged[MAX_SIZE];
extern stStrManageList     g_stMs[MAX_SIZE];

//插入字符串
int InsertStr(stStrManageList *curptr, TCHAR str[], int nInsertLen)
{
    _tcscpy(&g_tszManaged[curptr->nHeadIndex], str);
    //节点标记为存在字符串
    curptr->nExist = TRUE;
    //下标小于最大下标，即空间有剩余，才添加节点
    if ((curptr->nHeadIndex + nInsertLen) < MAX_SIZE)
    {
        AddNode(curptr);
        curptr->nTailIndex = curptr->nHeadIndex + nInsertLen - 1;
        curptr->Listnext->nHeadIndex = curptr->nTailIndex + 1;
    }
    curptr->nTailIndex = curptr->nHeadIndex + nInsertLen - 1;

    return TRUE;
}

//删除字符串
int DelStr(stStrManageList *head, int nIndex)
{
    //按索引搜索字符串
    stStrManageList *curptr = SearchStrIndex(head, nIndex);
    if (curptr != NULL)
    {
        //删除串，产生空块
        curptr->nExist = FALSE;
        //存在下空块
        if (curptr->Listnext != NULL)
        {
            //，与下空块合并
            if (curptr->Listnext->nExist == FALSE)
            {
                curptr->nTailIndex = curptr->Listnext->nTailIndex;
                DelNode(curptr->Listnext);
            }
        }

        //存在上空块
        if (curptr->Listprev != NULL)
        {
            //，与上空块合并
            if (curptr->Listprev->nExist == FALSE)
            {
                curptr->Listprev->nTailIndex = curptr->nTailIndex;
                DelNode(curptr);
            }
        }


        return TRUE;
    }

    return FALSE;
}

//判断剩余空间是否足够
int IsFreeEnough(stStrManageList *curptr, int nInsertLen)
{
    int nFreeLen = curptr->nTailIndex - curptr->nHeadIndex + 1;

    if (nFreeLen >= nInsertLen)
    {
        return  TRUE;
    }

    return FALSE;
}

//尝试按内容搜索字符串，支持模糊查找
int SearchStrContent(stStrManageList * head, TCHAR str[])
{
    //当前序号
    int counter = 0;
    //首地址，
    int nHaddr = 0;
    //尾地址
    int nTaddr = 0;
    //块长度
    int nBlockLen = 0;

    //记录当前节点
    stStrManageList *curptr = head;
    //记录遍历的上个节点
    stStrManageList *back = head;

    //管理链表没有搜索完，则继续搜索下一节点
    while (curptr != NULL)
    {
        //存在串
        if (curptr->nExist == TRUE)
        {

            //按子字符串，进行模糊搜索
            if (_tcsstr(&g_tszManaged[curptr->nHeadIndex], str) != NULL)
            {
                nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
                nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
                nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);

                _tprintf(_T("[%-3d] Size=%-3d HeadAdr = %p TailAdr = %p %s\r\n"),
                         counter, nBlockLen, nHaddr, nTaddr, &g_tszManaged[curptr->nHeadIndex]);

            }
            back = curptr;
            curptr = curptr->Listnext;
        }
        counter++;
    }
    return FALSE;
}

/************** WORKING     **********************/
//尝试按地址搜索字符串
int SearchStrAddr(stStrManageList * head, int addr)
{
    int counter = 0;

    stStrManageList *curptr = head;
    //记录遍历的上个节点
    stStrManageList *back = head;

    //管理链表没有搜索完，则继续搜索下一节点
    while (curptr != NULL)
    {
        if ((int)&g_tszManaged[curptr->nHeadIndex] == addr)
        {
            _tprintf(_T("%d  %p  %s\r\n"), counter, &g_tszManaged[curptr->nHeadIndex], &g_tszManaged[curptr->nHeadIndex]);
            return TRUE;
        }
        back = curptr;
        curptr = curptr->Listnext;
        counter++;
    }

    return FALSE;
}

//修改字符串
void ChangeStr(stStrManageList * head, TCHAR str[], int nIndex)
{
    //字符串长度
    int nInsertLen = _tcslen(str) + 1;
    stStrManageList *curptr = NULL;

    //先删除
    DelStr(head, nIndex);

    //再添加
    curptr = FindInsertPos(head, nInsertLen);
    InsertStr(curptr, str, nInsertLen);
}

/************** WORKING     **********************/
//碎片整理
void Arrange(stStrManageList * head)
{
}


//存储信息
void StroageInfo(stStrManageList * head)
{
    //当前序号
    int counter = 0;
    //首地址，
    int nHaddr = 0;
    //尾地址
    int nTaddr = 0;
    //块长度
    int nBlockLen = 0;

    //记录当前节点
    stStrManageList *curptr = head;
    //记录遍历的上个节点
    stStrManageList *back = head;

    //管理链表没有搜索完，则继续搜索下一节点
    while (curptr != NULL)
    {
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);

        //当前节点有字符串
        if (curptr->nExist == TRUE)
        {
            while (nHaddr <= nTaddr)
            {
                if (*(char*)nHaddr != 0)
                {
                    _tprintf(_T("F"));
                }

                else
                {
                    _tprintf(_T("U"));
                }

                nHaddr += sizeof(TCHAR);
            }
            _tprintf(_T("\t"));
        }
        else
        {

            _tprintf(_T("* Size=%-3d U *\t"),
                     nBlockLen);

        }

        back = curptr;
        curptr = curptr->Listnext;
        counter++;
    }

}


//统计字符信息
void CharAnalysis(stStrManageList * head)
{
    //当前序号
    int counter = 0;
    //首地址，
    int nHaddr = 0;
    //尾地址
    int nTaddr = 0;
    //块长度
    int nBlockLen = 0;
    
    //循环索引
    int i = 0;
    //取出单个字符
    TCHAR tCh = 0;
    //以字符为下标，保存出现的个数
    int num[MAXASCIICHAR] = { 0 };

    //记录当前节点
    stStrManageList *curptr = head;
    //记录遍历的上个节点
    stStrManageList *back = head;

    //管理链表没有搜索完，则继续搜索下一节点
    while (curptr != NULL)
    {
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);

        //当前节点有字符串
        if (curptr->nExist == TRUE)
        {

            //以字符为下标，保存字符的个数
            for (i = 0; i < nBlockLen - 1; i++)
            {
                tCh = ((TCHAR*)nHaddr)[i];
                num[tCh] = num[tCh] + 1;
            }

            
            for (i = 0; i < MAXASCIICHAR; i++)
            {
                if (num[i] != 0)
                    _tprintf(_T("字符%c出现%d次\n"), (TCHAR)i, num[i]);
            }
        }

        back = curptr;
        curptr = curptr->Listnext;
        counter++;
    }
}

//打印所有
void ShouAll(stStrManageList * head)
{
    //当前序号
    int counter = 0;
    //首地址，
    int nHaddr = 0;
    //尾地址
    int nTaddr = 0;
    //块长度
    int nBlockLen = 0;

    //记录当前节点
    stStrManageList *curptr = head;
    //记录遍历的上个节点
    stStrManageList *back = head;

    //管理链表没有搜索完，则继续搜索下一节点
    while (curptr != NULL)
    {
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);

        //当前节点有字符串
        if (curptr->nExist == TRUE)
        {

            _tprintf(_T("[%-3d] Size=%-3d HeadAdr = %p TailAdr = %p %s\r\n"),
                     counter, nBlockLen, nHaddr, nTaddr, nHaddr);

        }
        else
        {

            _tprintf(_T("[%-3d] Size=%-3d HeadAdr = %p TailAdr = %p ** EMPTY BLOCK **\r\n"),
                     counter, nBlockLen, nHaddr, nTaddr);

        }

        back = curptr;
        curptr = curptr->Listnext;
        counter++;
    }
}

//初始化管理链表的头节点
stStrManageList * ListNodeInit(stStrManageList * head)
{
    //初始化链表头节点 ：将g_stMs[0],设为头节点

    g_stMs[0].nUsed = TRUE;
    g_stMs[0].nExist = FALSE;
    g_stMs[0].nHeadIndex = 0;
    g_stMs[0].nTailIndex = MAX_SIZE - 1;
    g_stMs[0].Listprev = NULL;
    g_stMs[0].Listnext = NULL;


    head = &g_stMs[0];
    return head;
}

//查找可插入字符串位置
stStrManageList * FindInsertPos(stStrManageList *head, int nInsertLen)
{

    //当前节点
    stStrManageList *curptr = head;
    //记录遍历的上个节点
    stStrManageList *back = head;

    //管理链表没有搜索完，则继续搜索下一节点
    while (curptr != NULL)
    {
        //节点被使用，且存在串
        if (curptr->nExist == TRUE)
        {
            back = curptr;
            curptr = curptr->Listnext;
        }
        //被使用，但不存在串
        else
        {
            //剩余空间足够
            if (IsFreeEnough(curptr, nInsertLen) == TRUE)
            {
                return curptr;
            }
            //剩余空间不够，继续搜索
            else
            {
                back = curptr;
                curptr = curptr->Listnext;
            }
        }

    }

    return NULL;
}

//尝试按编号搜索字符串
stStrManageList * SearchStrIndex(stStrManageList * head, int nIndex)
{
    //当前序号
    int counter = 0;
    //首地址，
    int nHaddr = 0;
    //尾地址
    int nTaddr = 0;
    //块长度
    int nBlockLen = 0;


    //记录当前节点
    stStrManageList *curptr = head;
    //记录遍历的上个节点
    stStrManageList *back = head;

    //管理链表没有搜索完，则继续搜索下一节点
    while (curptr != NULL&&counter < nIndex)
    {
        back = curptr;
        curptr = curptr->Listnext;
        counter++;
    }

    if (counter == nIndex)
    {
        //查询时输出
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);
        _tprintf(_T("[%-3d] Size=%-3d HeadAdr = %p TailAdr = %p %s\r\n"),
                 counter, nBlockLen, nHaddr, nTaddr, &g_tszManaged[curptr->nHeadIndex]);

        return curptr;
    }
    return NULL;
}

//添加节点
stStrManageList * AddNode(stStrManageList * curptr)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        //找到可用的空闲节点
        if (g_stMs[i].nUsed == FALSE)
        {
            //初始化节点
            g_stMs[i].nUsed = TRUE;
            g_stMs[i].nExist = FALSE;
            g_stMs[i].nHeadIndex = ERRINDEX;
            g_stMs[i].nTailIndex = curptr->nTailIndex;
            g_stMs[i].Listprev = curptr;
            g_stMs[i].Listnext = curptr->Listnext;
            //将节点插入链表
            curptr->Listnext = &g_stMs[i];
            curptr = &g_stMs[i];

            //返回刚刚添加的节点
            return curptr;
        }
    }

    return NULL;
}

//删除节点
stStrManageList * DelNode(stStrManageList * curptr)
{
    //本节点标记为未使用，便于再次使用此节点
    curptr->nUsed = FALSE;
    //将字符串标为已删除
    curptr->nExist = FALSE;

    //我上节点下，指向我下
    curptr->Listprev->Listnext = curptr->Listnext;
    //我下节点上，指向我上
    if (curptr->Listnext != NULL)
    {
        curptr->Listnext->Listprev = curptr->Listprev;
    }

    //返回被删节点的上个节点
    return curptr->Listprev;
}