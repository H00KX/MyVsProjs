#include "stdafx.h"
#include "setdisplay.h"
#include "map.h"

CMap::CMap(int nWidth, int nHeight)
{
    m_nMapHeight = nHeight;
    m_nMapWidth = nWidth;

    m_pMap = shared_ptr<char>(new char[m_nMapWidth * m_nMapHeight], \
                              std::default_delete<char[]>());

    for (int i = 0; i < m_nMapHeight; i++)
    {
        for (int j = 0; j < m_nMapWidth; j++)
        {
            if (j == 0 || j == m_nMapWidth - 1 || i == 0 || i == m_nMapHeight - 1)
            {
                (&*m_pMap)[i*m_nMapWidth + j] = 1;
            }
            else
            {
                (&*m_pMap)[i*m_nMapWidth + j] = 0;
            }
        }

    }

}

//绘制背景色
void CMap::ShowBg(int x, int y)
{
    WriteChar(y,  // 第 1 行
              x,  // 第 1 列
              "  ",
              SetConsoleColor(COLOR_BLACK, // 黑色前景
                              COLOR_WHITE)  // 黑色前景
    );
}

//绘制方块色
void CMap::ShowBlock(int x, int y)
{

    WriteChar(y,  // 第 1 行
              x,  // 第 1 列
              "■",
              SetConsoleColor(COLOR_BLACK, // 黑色前景
                              COLOR_WHITE)
              /*SetConsoleColor(COLOR_BLUE, //
                              COLOR_BLACK)  // 红色前景*/
    );
}

void CMap::DrawBg()
{

    for (int i = 0; i < m_nMapHeight; i++)
    {
        for (int j = 0; j < m_nMapWidth; j++)
        {
            //表示该块为空
            if ((&*m_pMap)[i*m_nMapWidth + j] == 0)
            {
                ShowBg(i, j);
            }
            else if ((&*m_pMap)[i*m_nMapWidth + j] == 1)
            {
                ShowBlock(i, j);
            }

        }
    }

    WriteChar(32,  // 第 1 行
              7,  // 第 1 列
              "welcome to 贪食蛇！使用WSAD操作",
              SetConsoleColor(COLOR_RED, // 
                              COLOR_BLACK));
    WriteChar(34,  // 第 1 行
              10,  // 第 1 列
              "your score is :",
              SetConsoleColor(COLOR_RED, // 
                              COLOR_BLACK));
}

void CMap::DrawFood()
{
    WriteChar(posFood.Y,  // 第 1 行
              posFood.X,  // 第 1 列
              "●",
              SetConsoleColor(COLOR_RED, // 黑色前景
                              COLOR_WHITE));
}

const COORD & CMap::GetFood() const
{
    // TODO: 在此处插入 return 语句
    return posFood;
}

const char * CMap::GetMap() const
{
    return &*m_pMap;
}

void CMap::ReInitFood()
{
    posFood.X = (rand() * posFood.X) % (m_nMapWidth - 2) + 1;
    posFood.Y = (rand() + 13 * posFood.Y) % (m_nMapHeight - 2) + 1;

    DrawFood();
}
