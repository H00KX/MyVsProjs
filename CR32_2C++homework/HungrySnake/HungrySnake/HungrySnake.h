#pragma once
#include "stdafx.h"
#include <list>
#include "setdisplay.h"
#include "map.h"

class Snake
{
private:
    struct Node
    {
        Node(int x, int y)
        {
            m_nX = x;
            m_nY = y;
        }

        int m_nX;
        int m_nY;
    };

public:
    Snake();
    ~Snake();

    int TryMove(const char* map, int nWidth, int nDirect);
    int Impact(const char* map, int nWidth, int x, int y);
    int EatFood(const COORD& food);
    
    int GetSize();


    void Draw();
    void AddDrawTail(int x, int y);
    void DelHideTail();
    void AddDrawHead(int x, int y);


private:
    std::list<Node*> m_Snake;

    /*  ·½Ïò
        0
    3       1
        2
    */
    int m_nDirect;
};
