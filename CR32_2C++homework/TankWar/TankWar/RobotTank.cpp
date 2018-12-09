#include "stdafx.h"
#include "RobotTank.h"
#include <cstdlib>

RobotTank::RobotTank(int x, int y, int nID)
{
    m_nRotate = rand() % 4;
    m_nCurX = x;
    m_nCurY = y;
    m_nType = rand() % 4;
    m_nID = nID;
}

void RobotTank::Fire()
{

}

void RobotTank::AutoRun()
{
    m_nRotate = rand() % 4;

    if (m_nRotate == 0)
    {
        m_nRotate = 0;
        m_nCurY += CTank::m_nMovStep;
    }
    if (m_nRotate == 1)
    {
        m_nRotate = 1;
        m_nCurX -= CTank::m_nMovStep;
    }
    if (m_nRotate == 2)
    {
        m_nRotate = 2;
        m_nCurY -= CTank::m_nMovStep;
    }
    if (m_nRotate == 3)
    {
        m_nRotate = 3;
        m_nCurX += CTank::m_nMovStep;
    }

    //4分之一的几率开枪
    if (rand() % 4 == 0)
    {
        Fire();
    }

}

