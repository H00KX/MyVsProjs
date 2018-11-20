#pragma once

#define MAX_SIZE        512
#define INPUT_LEN       32
#define TRUE            1
#define FALSE           0
#define ERRINDEX        -1
#define MAXASCIICHAR        256


typedef struct st
{
    int nUsed = FALSE;
    int nExist = FALSE;
    int nHeadIndex = ERRINDEX;
    int nTailIndex = ERRINDEX;

    st * Listprev = NULL;
    st * Listnext = NULL;

}stStrManageList;



//碎片整理
void Arrange(stStrManageList *head);

//存储信息
void StroageInfo(stStrManageList *head);

//统计字符信息
void CharAnalysis(stStrManageList *head);

//打印所有
void ShouAll(stStrManageList *head);

//修改字符串
void ChangeStr(stStrManageList *head, TCHAR str[], int nIndex);

//插入字符串
int InsertStr(stStrManageList *curptr, TCHAR str[], int nInsertLen);

//删除字符串
int DelStr(stStrManageList *head, int nIndex);

//判断剩余空间是否足够
int IsFreeEnough(stStrManageList *curptr, int nInsertLen);

//尝试按内容搜索字符串，支持模糊查找
int SearchStrContent(stStrManageList * head, TCHAR str[]);

//尝试按地址搜索字符串
int SearchStrAddr(stStrManageList * head, int addr);

//初始化管理链表的头节点
stStrManageList * ListNodeInit(stStrManageList *head);

//尝试按编号搜索字符串
stStrManageList * SearchStrIndex(stStrManageList * head, int nIndex);

//查找可插入字符串位置
stStrManageList * FindInsertPos(stStrManageList *head, int nInsertLen);

//添加节点
stStrManageList * AddNode(stStrManageList * curptr);

//删除节点
stStrManageList * DelNode(stStrManageList * curptr);