#pragma once
#include "TankWarObj.h"
class CTank :public TankWarObj
{
    
public:
    CTank() = default;
    CTank(int x, int y, int nRotate = 0, int nID = 1, int nType = 0, int nWillFire = 0);

    virtual ~CTank();

    virtual void SetRotate(int nR);
    virtual void SetFire(int nF);
};

