#include "stdafx.h"
#include "RobotTank.h"
#include <cstdlib>

RobotTank::RobotTank(int x, int y, int nRotate, int nID, int nType, int nWillFire)
{
    m_nRotate = rand() % 4;
    m_nCurX = x;
    m_nCurY = y;
    m_nType = nType;
    m_nID = nID;
    m_nWillFire = nWillFire;
}

void RobotTank::SetRotate(int nR)
{
    m_nRotate = rand() % 4;
}



void RobotTank::SetFire(int nF)
{
    int n = 0;
    if (nF == 1)
    {
        n = rand() % 10;
        if (n == 1)
        {
            m_nWillFire = 1;
        }
    }
    if (nF == 0)
    {
        m_nWillFire = 0;
    }
}

