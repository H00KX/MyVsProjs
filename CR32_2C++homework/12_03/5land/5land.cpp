// 5land.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class SpaceShip
{
public:
    SpaceShip() = default;
    ~SpaceShip() = default;

};

class SHuttle :public SpaceShip
{
public:
    void land()
    {
        cout << "test" << endl;
    };
};



int main()
{
    SpaceShip ss;
    SHuttle sh;
    ss = sh;


    //SpaceShip û�г�Աland();
    ss.land();

    return 0;
}

