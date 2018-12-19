#pragma once

class TankWarObj
{
public:
    TankWarObj();
    ~TankWarObj();

    virtual int CurX()
    {
        return m_nCurX;
    }
    virtual int CurY()
    {
        return m_nCurY;
    }

    virtual void SetCurX(int X)
    {
        m_nCurX = X;
    }

    virtual void SetCurY(int Y)
    {
        m_nCurY = Y;
    }

    virtual void SetRotate(int nR)
    {

    }

    virtual void SetFire(int nF)
    {

    };

    virtual int CheckWall(unsigned char mapData[][26], int x, int y);
    virtual int CheckObj(TankWarObj *obj, TankWarObj *another);
    virtual void Move();

public:
    static int m_nMovStep;

    int m_nID;
    int m_nRotate;
    int m_nType;
    int m_nCurX;
    int m_nCurY;
    int m_nWillFire;
};


struct TONode
{
    TONode *Prev;
    TONode *Next;

    TankWarObj *Obj;
};

void AddObj(TONode* pHead, TONode* ToBeAdd);
TONode*  DelObj(TONode* pHead, TONode* ToBeRem);


struct ObjPos
{
    int x;
    int y;
};