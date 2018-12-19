#pragma once
#include "Tank.h"
class RobotTank : public CTank
{
public:
    RobotTank() = default;
    //(int nCurX, int nCurY, int nID, int nType, int nWillFire);
    RobotTank(int x, int y, int nRotate = 0, int nID = 1, int nType = 0, int nWillFire = 0);
    virtual ~RobotTank() = default;
    virtual void SetFire(int nF);

    virtual void SetRotate(int nR);

};

