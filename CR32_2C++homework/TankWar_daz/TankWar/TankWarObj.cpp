#include "stdafx.h"
#include "TankWarObj.h"


TankWarObj::TankWarObj()
{
}


TankWarObj::~TankWarObj()
{
}


void AddObj(TONode* pHead, TONode* ToBeAdd)
{
    TONode *p = pHead;
    while (p->Next != nullptr)
    {
        p = p->Next;
    }

    ToBeAdd->Prev = p;
    ToBeAdd->Next = nullptr;

    p->Next = ToBeAdd;

}

TONode*  DelObj(TONode* pHead, TONode* ToBeRem)
{
    TONode *p = pHead;
    while (p->Next != ToBeRem)
    {
        p = p->Next;
    }

    ToBeRem->Prev->Next = ToBeRem->Next;

    if (ToBeRem->Next != nullptr)
    {
        ToBeRem->Next->Prev = ToBeRem->Prev;
    }

    return p;
}

//ûײǽ������0
int TankWarObj::CheckWall(unsigned char mapData[][26], int x, int y)
{
    if (x < 0 || x + 1 > 25)
    {
        return 1;
    }

    if (y - 1 < 0 || y > 25)
    {
        return 1;
    }

    if (mapData[y][x] != 0x00 ||
        mapData[y][x + 1] != 0x00 ||
        mapData[y - 1][x] != 0x00 ||
        mapData[y - 1][x + 1] != 0x00)
    {
        return 1;
    }

    return 0;
}

//x,y��Ԥ��λ�� ��ײ����0 ��û��ײ������1
int TankWarObj::CheckObj(TankWarObj *obj,TankWarObj *another)
{
    int x = 0;
    int y = 0;

    if (obj->m_nRotate == 0)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() - obj->m_nMovStep) / 25;

    }
    if (obj->m_nRotate == 1)
    {
        x = (obj->CurX() + obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }
    if (obj->m_nRotate == 2)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() + obj->m_nMovStep) / 25;
    }
    if (obj->m_nRotate == 3)
    {
        x = (obj->CurX() - obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }


    int nX = another->CurX() / 25;
    int nY = another->CurY() / 25;

    //obj��̹��
    ObjPos curTank[4] = {
        { x, y - 1 },{ x + 1, y - 1 },
        { x, y },{ x + 1,   y }
    };

    //���another��̹��
    ObjPos otherTank[4] = {
        { nX, nY - 1 },{ nX + 1, nY - 1 },
        { nX, nY },{ nX + 1,   nY }
    };

    //���another��̹��
    if (another->m_nID == 1 || another->m_nID == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (curTank[i].x == otherTank[j].x &&
                    curTank[i].y == otherTank[j].y)
                {
                    return 0;
                }
            }
        }
    }

    //������ӵ�
    if (another->m_nID == 2 || another->m_nID == 3)
    {
        //�ǵз��ӵ�
        if (another->m_nID - this->m_nID != 2)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (otherTank[i].x == x&&otherTank[i].y == y)
                    {
                        return 0;
                    }
                }
            }
        }
            
    }

    return 1;
}

//��������Ԥ��λ���ƶ�
void TankWarObj::Move()
{
    if (m_nRotate == 0)
    {
        m_nCurY -= m_nMovStep;
    }
    if (m_nRotate == 1)
    {
        m_nCurX += m_nMovStep;
    }
    if (m_nRotate == 2)
    {
        m_nCurY += m_nMovStep;
    }
    if (m_nRotate == 3)
    {
        m_nCurX -= m_nMovStep;
    }
}
