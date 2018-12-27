#include "Mon_Dog.h"
#include <iostream>


Mon_Dog::Mon_Dog(int nId, int nNameID)
    :Monster(nId)
{
    m_nameId = nNameID;
}


Mon_Dog::~Mon_Dog()
{
}

int Mon_Dog::Attack()
{
    std::cout << "dog attack" << std::endl;
    return 0;
}

int Mon_Dog::Move()
{
    std::cout << "dog Move" << std::endl;
    return 0;
}

int Mon_Dog::Say(int a)
{
    std::cout << "dog Say" << a << std::endl;
    return 0;
}
