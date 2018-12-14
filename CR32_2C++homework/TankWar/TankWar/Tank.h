#pragma once
#include "TankWarObj.h"
class CTank :public TankWarObj
{
    //(int nCurX, int nCurY, int nRotate, int nID, int nType)
public:
    CTank() = default;
    CTank(int x, int y, int nRotate = 0, int nID = 1, int nType = 0, int nWillFire = 0);

    virtual ~CTank();

    void OnUp();
    void OnDown();
    void OnLeft();
    void OnRight();
    virtual void SetRotate(int nR);
    virtual void Fire();
    virtual void SetFire(int nF);
    virtual int  WillFire();
    //自动运行
    virtual void AutoRun();
    //virtual int CheckWall(unsigned mapData[][26],int x, int y);

};

