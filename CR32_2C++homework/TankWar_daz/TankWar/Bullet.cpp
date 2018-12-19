#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(int x, int y, int nRotate, int nID, int nType, int nWillFire)
{
    m_nCurX = x;
    m_nCurY = y;
    m_nRotate = nRotate;
    m_nID = nID;
    m_nType = nType;
    m_nWillFire = nWillFire;
}


int Bullet::CheckWall(unsigned char mapData[][26], int x, int y)
{

    //2是铁，或出界
    if (x < 0 || x + 1 > 25)
    {
        return 2;
    }

    //2是铁，或出界
    if (y - 1 < 0 || y > 25)
    {
        return 2;
    }

    //2是铁，或出界
    if (mapData[y][x] == 0x2)
    {
        return 2;
    }

    //1是土墙或老爷
    if (mapData[y][x] == 0x1 || mapData[y][x] == 0x6)
    {
        return 1;
    }


    //0是可移动
    return 0;
}


//x,y是预测位置 碰撞返回0 ，没碰撞，返回1
int Bullet::CheckObj(TankWarObj *obj, TankWarObj *another)
{
    int x = obj->CurX() / 25;
    int y = obj->CurY() / 25;

    int nX = another->CurX() / 25;
    int nY = another->CurY() / 25;

    ObjPos otherTank[4] = {
        { nX, nY - 1 },{ nX + 1, nY - 1 },
        { nX, nY },{ nX + 1,   nY }
    };

    //子弹碰到坦克
    if (another->m_nID == 0 || another->m_nID == 1)
    {
        //是敌方坦克
        if (obj->m_nID - 2 != another->m_nID)
        {
            for (int i = 0; i < 4; i++)
            {
                if (otherTank[i].x == x&&otherTank[i].y == y)
                {
                    return 0;
                }
            }
        }

    }


    return 1;
}