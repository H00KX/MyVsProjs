#pragma once
class Monster
{
public:
    Monster();
    Monster(int nId);
    virtual ~Monster();

    virtual int Attack();
    virtual int Move();
    virtual int Say(int a);


protected:
    int m_nID;
};

