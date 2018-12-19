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

void CTank::SetRotate(int nR)
{
    m_nRotate = nR;
}

void CTank::SetFire(int nF)
{
    m_nWillFire = nF;
}