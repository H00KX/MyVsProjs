// StringManage.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "stringManage.h"

extern TCHAR       g_tszManaged[MAX_SIZE];
extern stStrManageList     g_stMs[MAX_SIZE];

//�����ַ���
int InsertStr(stStrManageList *curptr, TCHAR str[], int nInsertLen)
{
    _tcscpy(&g_tszManaged[curptr->nHeadIndex], str);
    //�ڵ���Ϊ�����ַ���
    curptr->nExist = TRUE;
    //�±�С������±꣬���ռ���ʣ�࣬����ӽڵ�
    if ((curptr->nHeadIndex + nInsertLen) < MAX_SIZE)
    {
        AddNode(curptr);
        curptr->nTailIndex = curptr->nHeadIndex + nInsertLen - 1;
        curptr->Listnext->nHeadIndex = curptr->nTailIndex + 1;
    }
    curptr->nTailIndex = curptr->nHeadIndex + nInsertLen - 1;

    return TRUE;
}

//ɾ���ַ���
int DelStr(stStrManageList *head, int nIndex)
{
    //�����������ַ���
    stStrManageList *curptr = SearchStrIndex(head, nIndex);
    if (curptr != NULL)
    {
        //ɾ�����������տ�
        curptr->nExist = FALSE;
        //�����¿տ�
        if (curptr->Listnext != NULL)
        {
            //�����¿տ�ϲ�
            if (curptr->Listnext->nExist == FALSE)
            {
                curptr->nTailIndex = curptr->Listnext->nTailIndex;
                DelNode(curptr->Listnext);
            }
        }

        //�����Ͽտ�
        if (curptr->Listprev != NULL)
        {
            //�����Ͽտ�ϲ�
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

//�ж�ʣ��ռ��Ƿ��㹻
int IsFreeEnough(stStrManageList *curptr, int nInsertLen)
{
    int nFreeLen = curptr->nTailIndex - curptr->nHeadIndex + 1;

    if (nFreeLen >= nInsertLen)
    {
        return  TRUE;
    }

    return FALSE;
}

//���԰����������ַ�����֧��ģ������
int SearchStrContent(stStrManageList * head, TCHAR str[])
{
    //��ǰ���
    int counter = 0;
    //�׵�ַ��
    int nHaddr = 0;
    //β��ַ
    int nTaddr = 0;
    //�鳤��
    int nBlockLen = 0;

    //��¼��ǰ�ڵ�
    stStrManageList *curptr = head;
    //��¼�������ϸ��ڵ�
    stStrManageList *back = head;

    //��������û�������꣬�����������һ�ڵ�
    while (curptr != NULL)
    {
        //���ڴ�
        if (curptr->nExist == TRUE)
        {

            //�����ַ���������ģ������
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
//���԰���ַ�����ַ���
int SearchStrAddr(stStrManageList * head, int addr)
{
    int counter = 0;

    stStrManageList *curptr = head;
    //��¼�������ϸ��ڵ�
    stStrManageList *back = head;

    //��������û�������꣬�����������һ�ڵ�
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

//�޸��ַ���
void ChangeStr(stStrManageList * head, TCHAR str[], int nIndex)
{
    //�ַ�������
    int nInsertLen = _tcslen(str) + 1;
    stStrManageList *curptr = NULL;

    //��ɾ��
    DelStr(head, nIndex);

    //�����
    curptr = FindInsertPos(head, nInsertLen);
    InsertStr(curptr, str, nInsertLen);
}

/************** WORKING     **********************/
//��Ƭ����
void Arrange(stStrManageList * head)
{
}


//�洢��Ϣ
void StroageInfo(stStrManageList * head)
{
    //��ǰ���
    int counter = 0;
    //�׵�ַ��
    int nHaddr = 0;
    //β��ַ
    int nTaddr = 0;
    //�鳤��
    int nBlockLen = 0;

    //��¼��ǰ�ڵ�
    stStrManageList *curptr = head;
    //��¼�������ϸ��ڵ�
    stStrManageList *back = head;

    //��������û�������꣬�����������һ�ڵ�
    while (curptr != NULL)
    {
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);

        //��ǰ�ڵ����ַ���
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


//ͳ���ַ���Ϣ
void CharAnalysis(stStrManageList * head)
{
    //��ǰ���
    int counter = 0;
    //�׵�ַ��
    int nHaddr = 0;
    //β��ַ
    int nTaddr = 0;
    //�鳤��
    int nBlockLen = 0;
    
    //ѭ������
    int i = 0;
    //ȡ�������ַ�
    TCHAR tCh = 0;
    //���ַ�Ϊ�±꣬������ֵĸ���
    int num[MAXASCIICHAR] = { 0 };

    //��¼��ǰ�ڵ�
    stStrManageList *curptr = head;
    //��¼�������ϸ��ڵ�
    stStrManageList *back = head;

    //��������û�������꣬�����������һ�ڵ�
    while (curptr != NULL)
    {
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);

        //��ǰ�ڵ����ַ���
        if (curptr->nExist == TRUE)
        {

            //���ַ�Ϊ�±꣬�����ַ��ĸ���
            for (i = 0; i < nBlockLen - 1; i++)
            {
                tCh = ((TCHAR*)nHaddr)[i];
                num[tCh] = num[tCh] + 1;
            }

            
            for (i = 0; i < MAXASCIICHAR; i++)
            {
                if (num[i] != 0)
                    _tprintf(_T("�ַ�%c����%d��\n"), (TCHAR)i, num[i]);
            }
        }

        back = curptr;
        curptr = curptr->Listnext;
        counter++;
    }
}

//��ӡ����
void ShouAll(stStrManageList * head)
{
    //��ǰ���
    int counter = 0;
    //�׵�ַ��
    int nHaddr = 0;
    //β��ַ
    int nTaddr = 0;
    //�鳤��
    int nBlockLen = 0;

    //��¼��ǰ�ڵ�
    stStrManageList *curptr = head;
    //��¼�������ϸ��ڵ�
    stStrManageList *back = head;

    //��������û�������꣬�����������һ�ڵ�
    while (curptr != NULL)
    {
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);

        //��ǰ�ڵ����ַ���
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

//��ʼ�����������ͷ�ڵ�
stStrManageList * ListNodeInit(stStrManageList * head)
{
    //��ʼ������ͷ�ڵ� ����g_stMs[0],��Ϊͷ�ڵ�

    g_stMs[0].nUsed = TRUE;
    g_stMs[0].nExist = FALSE;
    g_stMs[0].nHeadIndex = 0;
    g_stMs[0].nTailIndex = MAX_SIZE - 1;
    g_stMs[0].Listprev = NULL;
    g_stMs[0].Listnext = NULL;


    head = &g_stMs[0];
    return head;
}

//���ҿɲ����ַ���λ��
stStrManageList * FindInsertPos(stStrManageList *head, int nInsertLen)
{

    //��ǰ�ڵ�
    stStrManageList *curptr = head;
    //��¼�������ϸ��ڵ�
    stStrManageList *back = head;

    //��������û�������꣬�����������һ�ڵ�
    while (curptr != NULL)
    {
        //�ڵ㱻ʹ�ã��Ҵ��ڴ�
        if (curptr->nExist == TRUE)
        {
            back = curptr;
            curptr = curptr->Listnext;
        }
        //��ʹ�ã��������ڴ�
        else
        {
            //ʣ��ռ��㹻
            if (IsFreeEnough(curptr, nInsertLen) == TRUE)
            {
                return curptr;
            }
            //ʣ��ռ䲻������������
            else
            {
                back = curptr;
                curptr = curptr->Listnext;
            }
        }

    }

    return NULL;
}

//���԰���������ַ���
stStrManageList * SearchStrIndex(stStrManageList * head, int nIndex)
{
    //��ǰ���
    int counter = 0;
    //�׵�ַ��
    int nHaddr = 0;
    //β��ַ
    int nTaddr = 0;
    //�鳤��
    int nBlockLen = 0;


    //��¼��ǰ�ڵ�
    stStrManageList *curptr = head;
    //��¼�������ϸ��ڵ�
    stStrManageList *back = head;

    //��������û�������꣬�����������һ�ڵ�
    while (curptr != NULL&&counter < nIndex)
    {
        back = curptr;
        curptr = curptr->Listnext;
        counter++;
    }

    if (counter == nIndex)
    {
        //��ѯʱ���
        nHaddr = (int)&g_tszManaged[curptr->nHeadIndex];
        nTaddr = (int)&g_tszManaged[curptr->nTailIndex] + sizeof(TCHAR) - 1;
        nBlockLen = (nTaddr - nHaddr + 1) / sizeof(TCHAR);
        _tprintf(_T("[%-3d] Size=%-3d HeadAdr = %p TailAdr = %p %s\r\n"),
                 counter, nBlockLen, nHaddr, nTaddr, &g_tszManaged[curptr->nHeadIndex]);

        return curptr;
    }
    return NULL;
}

//��ӽڵ�
stStrManageList * AddNode(stStrManageList * curptr)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        //�ҵ����õĿ��нڵ�
        if (g_stMs[i].nUsed == FALSE)
        {
            //��ʼ���ڵ�
            g_stMs[i].nUsed = TRUE;
            g_stMs[i].nExist = FALSE;
            g_stMs[i].nHeadIndex = ERRINDEX;
            g_stMs[i].nTailIndex = curptr->nTailIndex;
            g_stMs[i].Listprev = curptr;
            g_stMs[i].Listnext = curptr->Listnext;
            //���ڵ��������
            curptr->Listnext = &g_stMs[i];
            curptr = &g_stMs[i];

            //���ظո���ӵĽڵ�
            return curptr;
        }
    }

    return NULL;
}

//ɾ���ڵ�
stStrManageList * DelNode(stStrManageList * curptr)
{
    //���ڵ���Ϊδʹ�ã������ٴ�ʹ�ô˽ڵ�
    curptr->nUsed = FALSE;
    //���ַ�����Ϊ��ɾ��
    curptr->nExist = FALSE;

    //���Ͻڵ��£�ָ������
    curptr->Listprev->Listnext = curptr->Listnext;
    //���½ڵ��ϣ�ָ������
    if (curptr->Listnext != NULL)
    {
        curptr->Listnext->Listprev = curptr->Listprev;
    }

    //���ر�ɾ�ڵ���ϸ��ڵ�
    return curptr->Listprev;
}