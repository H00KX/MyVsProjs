#pragma once
#include "TankWarObj.h"
class Bullet :public TankWarObj
{
public:

    Bullet(int x, int y, int nRotate, int nID = 2, int nType = 0, int nWillFire = 0);
    ~Bullet() = default;

    void AutoRun();

    void OnUp();

    void OnDown();

    void OnLeft();

    void OnRight();

    virtual int CheckWall(unsigned char mapData[][26], int x, int y);

    virtual int CheckObj(TankWarObj *obj, TankWarObj *another);

    virtual void SetRotate(int nR)
    {
    };
    virtual void SetFire(int)
    {

    };
};

