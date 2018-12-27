#include "stdafx.h"
#include "HungrySnake.h"

Snake::Snake()
{
    m_nDirect = 1;
    m_Snake.push_back(new Node(1, 2));
    m_Snake.push_back(new Node(2, 2));
    m_Snake.push_back(new Node(3, 2));
}

Snake::~Snake()
{

}

void Snake::Draw()
{
    for each (auto Node in m_Snake)
    {
        WriteChar(Node->m_nY,  // 第 1 行
                  Node->m_nX,  // 第 1 列
                  "■",
                  SetConsoleColor(COLOR_RED, // 黑色前景
                                  COLOR_WHITE));
    }
}

int Snake::TryMove(const char* map, int nWidth, int nDirect)
{
    if (abs(nDirect - m_nDirect) == 2)
    {
        return 0;
    }

    m_nDirect = nDirect;

    Node* head = m_Snake.back();
    int x = head->m_nX;
    int y = head->m_nY;

    //m_nDirect 顺时针，上
    if (m_nDirect == 0)
    {
        if (Impact(map, nWidth, x, y - 1))
        {
            return 1;
            //DelHideTail();
        }
        else
        {
            AddDrawHead(x, y - 1);
            return 1;
        }

    }
    //右
    if (m_nDirect == 1)
    {
        if (Impact(map, nWidth, x + 1, y))
        {
            //DelHideTail();
            return 1;
        }
        else
        {
            AddDrawHead(x + 1, y);
            return 1;
        }

    }
    //下
    if (m_nDirect == 2)
    {
        if (Impact(map, nWidth, x, y + 1))
        {
            //DelHideTail();
            return 1;
        }
        else
        {
            AddDrawHead(x, y + 1);
            return 1;
        }

    }
    //左
    if (m_nDirect == 3)
    {
        if (Impact(map, nWidth, x - 1, y))
        {
            //DelHideTail();
            return 1;
        }
        else
        {
            AddDrawHead(x - 1, y);
        }

    }


    return 1;
}
int Snake::GetSize()
{
    return m_Snake.size();
}
;



//void Snake::Update()
//{
//    if (EatFood())
//    {
//        //尾巴加一节
//        AddDrawTail();
//    }
//    else
//    {
//        //尾巴减一节，头加一节
//        DelHideTail();
//        AddDrawHead();
//    }
//}

int Snake::EatFood(const COORD & food)
{
    Node* head = m_Snake.back();

    return head->m_nX == food.X && head->m_nY == food.Y;
}

int Snake::Impact(const char* map, int nWidth, int x, int y)
{
    return map[y*nWidth + x] == 1;

}

void Snake::AddDrawTail(int x, int y)
{
    m_Snake.push_front(new Node(x, y));
    Node* p = m_Snake.front();
    WriteChar(p->m_nY,  // 第 1 行
              p->m_nX,  // 第 1 列
              "■",
              SetConsoleColor(COLOR_RED, // 黑色前景
                              COLOR_WHITE));
}

void Snake::DelHideTail()
{
    Node* p = m_Snake.front();
    WriteChar(p->m_nY,  // 第 1 行
              p->m_nX,  // 第 1 列
              "  ",
              SetConsoleColor(COLOR_WHITE, // 黑色前景
                              COLOR_WHITE));
    m_Snake.pop_front();
}

void Snake::AddDrawHead(int x, int y)
{
    m_Snake.push_back(new Node(x, y));
    Node* p = m_Snake.back();
    WriteChar(p->m_nY,  // 第 1 行
              p->m_nX,  // 第 1 列
              "■",
              SetConsoleColor(COLOR_RED, // 黑色前景
                              COLOR_WHITE));
}
