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



//��Ƭ����
void Arrange(stStrManageList *head);

//�洢��Ϣ
void StroageInfo(stStrManageList *head);

//ͳ���ַ���Ϣ
void CharAnalysis(stStrManageList *head);

//��ӡ����
void ShouAll(stStrManageList *head);

//�޸��ַ���
void ChangeStr(stStrManageList *head, TCHAR str[], int nIndex);

//�����ַ���
int InsertStr(stStrManageList *curptr, TCHAR str[], int nInsertLen);

//ɾ���ַ���
int DelStr(stStrManageList *head, int nIndex);

//�ж�ʣ��ռ��Ƿ��㹻
int IsFreeEnough(stStrManageList *curptr, int nInsertLen);

//���԰����������ַ�����֧��ģ������
int SearchStrContent(stStrManageList * head, TCHAR str[]);

//���԰���ַ�����ַ���
int SearchStrAddr(stStrManageList * head, int addr);

//��ʼ�����������ͷ�ڵ�
stStrManageList * ListNodeInit(stStrManageList *head);

//���԰���������ַ���
stStrManageList * SearchStrIndex(stStrManageList * head, int nIndex);

//���ҿɲ����ַ���λ��
stStrManageList * FindInsertPos(stStrManageList *head, int nInsertLen);

//��ӽڵ�
stStrManageList * AddNode(stStrManageList * curptr);

//ɾ���ڵ�
stStrManageList * DelNode(stStrManageList * curptr);