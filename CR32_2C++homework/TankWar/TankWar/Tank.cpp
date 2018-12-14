#include "stdafx.h"
#include "Tank.h"
#include <cstdlib>

//(int nCurX, int nCurY, int nRotate, int nID, int nType);
CTank::CTank(int x, int y, int nRotate, int nID, int nType, int nWillFire)
{
    m_nRotate = nRotate;
    m_nCurX = x;
    m_nCurY = y;
    m_nID = nID;
    m_nType = nType;
    m_nWillFire = nWillFire;
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


void CTank::SetRotate(int nR)
{
    m_nRotate = nR;
}

void CTank::Fire()
{

}

void CTank::SetFire(int nF)
{
    m_nWillFire = nF;
}

int CTank::WillFire()
{
    return m_nWillFire;
}

void CTank::AutoRun()
{

}
