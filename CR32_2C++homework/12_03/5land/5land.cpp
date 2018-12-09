// 5land.cpp : 定义控制台应用程序的入口点。
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


    //SpaceShip 没有成员land();
    ss.land();

    return 0;
}

