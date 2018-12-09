#include "stdafx.h"
#include "Tank.h"
#include <cstdlib>

CTank::CTank(int nType, int nRotate, int nCurX, int nCurY, int nID)
{
    m_nRotate = nRotate;
    m_nCurX = nCurX;
    m_nCurY = nCurY;
    m_nType = nType;
    m_nID = nID;
}


CTank::~CTank()
{

}

void CTank::OnUp()
{
    m_nRotate = 0;
    m_nCurY -= CTank::m_nMovStep;
}

void CTank::OnDown()
{
    m_nRotate = 2;
    m_nCurY += CTank::m_nMovStep;
}

void CTank::OnLeft()
{
    m_nRotate = 3;
    m_nCurX -= CTank::m_nMovStep;
}

void CTank::OnRight()
{
    m_nRotate = 1;
    m_nCurX += CTank::m_nMovStep;
}

void CTank::Fire()
{

}

void CTank::AutoRun()
{

}
