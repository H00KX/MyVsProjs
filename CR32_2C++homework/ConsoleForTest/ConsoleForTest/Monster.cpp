#include "Monster.h"
#include <iostream>


Monster::Monster()
{

}

Monster::Monster(int nId)
{
    m_nID = nId;
}


Monster::~Monster()
{
}

int Monster::Attack()
{
    std::cout << "monster attact " << std::endl;
    return 0;
}

int Monster::Move()
{
    std::cout << "monster move" << std::endl;
    return 0;
}

int Monster::Say(int a)
{
    std::cout << " monster say" << a << std::endl;
    return 0;
}



