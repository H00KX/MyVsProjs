#pragma once
#include <iostream>
#include <math.h>
#include <Windows.h>
#include <memory>

using namespace std;


class CMap
{
public:
    //CMap() = delete;
    CMap(int nWidth, int nHeight);

    void ShowBg(int x, int y);
    void ShowBlock(int x, int y);
    void DrawBg();
    void ReInitFood();
    void DrawFood();



    const COORD& GetFood()const;
    const char* GetMap()const;

private:
    COORD   posFood;

private:
    int m_nMapWidth;
    int m_nMapHeight;

    std::shared_ptr<char> m_pMap;
};