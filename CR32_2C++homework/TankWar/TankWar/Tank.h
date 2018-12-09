#pragma once
#include "TankWarObj.h"
class CTank :public TankWarObj
{
public:
    CTank(int nType = 0, int nRotate = 0, int nCurX = 0, int nCurY = 0, int nID = 0);

    virtual ~CTank();

    void OnUp();
    void OnDown();
    void OnLeft();
    void OnRight();
    virtual void Fire();
    //自动运行
    virtual void AutoRun();

    int CurX()
    {
        return m_nCurX;
    }
    int CurY()
    {
        return m_nCurY;
    }

    void SetCurX(int X)
    {
        m_nCurX = X;
    }

    void SetCurY(int Y)
    {
        m_nCurY = Y;
    }

public:
    int m_nRotate;
    int m_nType;
    static int m_nMovStep;

protected:

    int m_nCurX;
    int m_nCurY;
};

