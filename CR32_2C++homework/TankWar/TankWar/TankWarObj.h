#pragma once

class TankWarObj
{
public:
    TankWarObj();
    ~TankWarObj();
    virtual void AutoRun()
    {

    };

public:
    int m_nID;
};


struct TONode
{
    TONode *PrevObj;
    TONode *NextObj;

    TankWarObj *Obj;
};

void AddObj(TONode* pHead, TONode* ToBeAdd);
void DelObj(TONode* pHead, TONode* ToBeRem);