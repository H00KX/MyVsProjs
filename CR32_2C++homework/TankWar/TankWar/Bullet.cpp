#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(int nType, int nCurX, int nCurY, int nRotate, int nID)
{
    m_nType = nType;
    m_nCurX = nCurX;
    m_nCurY = nCurY;
    m_nRotate = nRotate;
    m_nID = nID;
}

void Bullet::AutoRun()
{
    if (m_nRotate == 0)
    {
        OnUp();
    }
    if (m_nRotate == 1)
    {
        OnRight();
    }
    if (m_nRotate == 2)
    {
        OnDown();
    }
    if (m_nRotate == 3)
    {
        OnLeft();
    }
}

void Bullet::OnUp()
{
    //m_nRotate = 0;
    m_nCurY -= 25;
}

void Bullet::OnDown()
{
    //m_nRotate = 2;
    m_nCurY += 25;
}

void Bullet::OnLeft()
{
    //m_nRotate = 3;
    m_nCurX -= 25;
}

void Bullet::OnRight()
{
    //m_nRotate = 1;
    m_nCurX += 25;
}