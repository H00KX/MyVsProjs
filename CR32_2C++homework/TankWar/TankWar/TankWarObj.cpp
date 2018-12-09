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
    while (p->NextObj != nullptr)
    {
        p = p->NextObj;
    }

    ToBeAdd->PrevObj = p;
    ToBeAdd->NextObj = nullptr;

    p->NextObj = ToBeAdd;

}

void DelObj(TONode* pHead, TONode* ToBeRem)
{
    TONode *p = pHead;
    while (p->NextObj != ToBeRem)
    {
        p = p->NextObj;
    }

    ToBeRem->PrevObj->NextObj = ToBeRem->NextObj;

    if (ToBeRem->NextObj != nullptr)
    {
        ToBeRem->NextObj->PrevObj = ToBeRem->PrevObj;
    }
}
