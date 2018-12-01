#include "stdafx.h"
#include "Sense.h"
#include <stdlib.h>


CSense::CSense(int xSize, int ySize)
{
    m_nMapWidth = xSize;
    m_nMapHeight = ySize;

    m_pMap = shared_ptr<char>(new char[m_nMapWidth * m_nMapHeight], \
                              std::default_delete<char[]>());


    //背景墙需要初始化

    for (int i = 0; i < m_nMapHeight; i++)
    {

        for (int j = 0; j < m_nMapWidth; j++)
        {

            if (j == 0 || j == m_nMapWidth - 1 || i == m_nMapHeight - 1)
            {
                //设置边界
                (&*m_pMap)[i*m_nMapWidth + j] = 1;
            }
            else
            {
                (&*m_pMap)[i*m_nMapWidth + j] = 0;
            }

        }
    }

    //初始化一个新方块
    CreateBlock();

    DrawBg();
}

//画整个背景
void CSense::DrawBg()
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
}

//画整个方块
void CSense::DrawBlock()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        x = m_nCurX + m_Block.X(i);
        //y坐标0，是左边的墙，所以y打印坐标要加一
        y = m_nCurY + m_Block.Y(i) + 1;
        ShowBlock(x, y);
    }
}

//绘制方块色
void CSense::ShowBlock(int x, int y)
{
    WriteChar(x,  // 第 1 行
              y,  // 第 1 列
              "  ",
              SetConsoleColor(COLOR_WHITE, // 黑色背景
                              COLOR_WHITE)  // 红色前景
    );
}

//抹掉整个方块
void CSense::ClearBlock()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        x = m_nCurX + m_Block.X(i);
        //y坐标0，是左边的墙，所以y打印坐标要加一
        y = m_nCurY + m_Block.Y(i) + 1;
        ShowBg(x, y);
    }
}

//检查指定行是否全满，行满则返回1
bool CSense::CheckRow(int nRow)
{
    for (int i = 1; i < m_nMapWidth - 1; i++)
    {
        if ((&*m_pMap)[nRow*m_nMapWidth + i] == 0)
        {
            return false;
        }
    }

    return true;
}


//消行  然后将上面的行下移
void CSense::ClearRow()
{

}

//绘制背景色
void CSense::ShowBg(int x, int y)
{
    WriteChar(x,  // 第 1 行
              y,  // 第 1 列
              "  ",
              SetConsoleColor(COLOR_WHITE, // 白色背景
                              COLOR_BLACK)  // 黑色前景
    );
}

//创建一个新方块
void CSense::CreateBlock()
{
    m_nCurX = 3;
    m_nCurY = 3;
    m_Block = CBlock();
}

//尝试移动
bool CSense::BlockTryMove(int nDiret)
{
    //要移动的方向的下一个块坐标
    int x = 0;
    int y = 0;
    if (nDiret == DOWN)
    {
        //下移的判断
        for (int i = 0; i < 4; i++)
        {
            //方块矩阵索引从-1开始，转换为Sense索引，要 - （-1)
            x = m_nCurX + m_Block.X(i) + 1;
            y = m_nCurY + m_Block.Y(i) + 1;

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1 ||
                x >= m_nMapHeight - 1)
            {
                return false;
            }
        }

        m_nCurX++;  //x坐标加一，即下移
        return true;
    }


    if (nDiret == RIGHT)
    {
        for (int i = 0; i < 4; i++)
        {
            //方块矩阵索引从-1开始，转换为Sense索引，要 偏移 （-1)
            x = m_nCurX + m_Block.X(i);
            y = m_nCurY + m_Block.Y(i) + 2;

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1 ||
                y >= m_nMapWidth - 1)
            {
                return false;
            }
        }

        m_nCurY++;  //y坐标加一，即右移
        return true;
    }

    if (nDiret == LEFT)
    {
        for (int i = 0; i < 4; i++)
        {
            //方块矩阵索引从-1开始，转换为Sense索引，要 - （-1)
            x = m_nCurX + m_Block.X(i);
            y = m_nCurY + m_Block.Y(i);

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1 || y <= 0)
            {
                return false;
            }
        }

        m_nCurY--;  //y坐标减一，即左移
        return true;
    }
}

//尝试旋转
bool CSense::BlockTryRotate()
{
    int x = 0;
    int y = 0;
    //先旋转，之后判断是否有重叠，若有，再转回去。
    m_Block.RightRotate();

    for (int i = 0; i < 4; i++)
    {
        //方块矩阵索引从-1开始，转换为Sense索引，要 - （-1)
        x = m_nCurX + m_Block.X(i);
        y = m_nCurY + m_Block.Y(i) + 1;

        if ((&*m_pMap)[x*m_nMapWidth + y] == 1)
        {
            m_Block.LeftRotate();
            return false;
        }
    }
    return true;
}

//固定，转化为墙
void CSense::FixBlock()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        x = m_nCurX + m_Block.X(i);
        y = m_nCurY + m_Block.Y(i) + 1;
        (&*m_pMap)[x*m_nMapWidth + y] = 1;
    }
}
