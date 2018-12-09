#pragma once
#include "TankWarObj.h"
class Bullet :public TankWarObj
{
public:
    Bullet(int nType, int nCurX, int nCurY, int nRotate,int nID);
    ~Bullet() = default;

    void AutoRun();

    void OnUp();

    void OnDown();

    void OnLeft();

    void OnRight();

public:
    int m_nID;
    int m_nType;
    int m_nCurX;
    int m_nCurY;
    int m_nRotate;
};

