#pragma once
#include "Tank.h"
class RobotTank :
    public CTank
{
public:
    RobotTank() = default;
    RobotTank(int x, int y, int nID);
    virtual ~RobotTank() = default;
    virtual void Fire();
    virtual void AutoRun();

};

