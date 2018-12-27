#pragma once
#include "Monster.h"
class Mon_Dog :
    public Monster
{
public:
    Mon_Dog(int nId, int nNameID);
    virtual ~Mon_Dog();

    int Attack();
    int Move();
    int Say(int a);

private:
    int m_nameId;
};

