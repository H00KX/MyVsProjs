#include "stdafx.h"
#include <locale.h>
#include "stringManage.h"

TCHAR       g_tszManaged[MAX_SIZE] = _T(" ");
stStrManageList     g_stMs[MAX_SIZE];

int main()
{
    stStrManageList *head = NULL;
    stStrManageList *current = NULL;
    TCHAR   tszInput[MAX_SIZE * sizeof(TCHAR)] = _T("");
    int nInsertLen = 0;
    int nIndex = 3;

    _tsetlocale(LC_ALL, _T("chs"));

    head = ListNodeInit(head);

    //Ñ­»·Ìí¼Ó×Ö·û´®
    while (1)
    {
        _tscanf(_T("%512s"), &tszInput);
        rewind(stdin);

        nInsertLen = _tcslen(tszInput) + 1;

        current = FindInsertPos(head, nInsertLen);

        if (current != NULL)
        {

            InsertStr(current, tszInput, nInsertLen);
        }
    }

    ShouAll(head);

    CharAnalysis(head);

    StroageInfo(head);


    _tscanf(_T("%512s"), &tszInput);
    rewind(stdin);
    ChangeStr(head, tszInput, 0);

    SearchStrIndex(head, nIndex);
    DelStr(head, nIndex);


    return 0;
}