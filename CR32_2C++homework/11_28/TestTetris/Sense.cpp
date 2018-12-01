#include "stdafx.h"
#include "Sense.h"
#include <stdlib.h>


CSense::CSense(int xSize, int ySize)
{
    m_nMapHeight = xSize;
    m_nMapWidth = ySize;


    m_pMap = shared_ptr<char>(new char[m_nMapWidth * m_nMapHeight], \
                              std::default_delete<char[]>());

    m_nMapRowForE = shared_ptr<char>(new char[m_nMapHeight - 1], \
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

        if (i < m_nMapHeight - 1)
        {
            //m_nMapRowForE[Row]=EMPYT
            (&*m_nMapRowForE)[i] = 0;
        }

    }
    //初始化一个新方块
    CreateBlock();

    //DrawBg();
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

    WriteChar(8,  // 第 1 行
              40,  // 第 1 列
              "welcome to Tetrie！",
              SetConsoleColor(COLOR_RED, // 
                              COLOR_BLACK));
    WriteChar(10,  // 第 1 行
              40,  // 第 1 列
              "your score is :",
              SetConsoleColor(COLOR_RED, // 
                              COLOR_BLACK));
}

//画整个方块
void CSense::DrawBlock()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        x = m_nCurX + m_Block.X(i) + 1;
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
              SetConsoleColor(COLOR_BLUE, // 
                              COLOR_BLACK)  // 红色前景
    );
}

//绘制背景色
void CSense::ShowBg(int x, int y)
{
    WriteChar(x,  // 第 1 行
              y,  // 第 1 列
              "  ",
              SetConsoleColor(COLOR_BLACK, // 黑色前景
                              COLOR_WHITE)  // 黑色前景
    );
}

//抹掉整个方块
void CSense::ClearBlock()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        //方块矩阵 原点 （-1，-1）代表（0行，0列）对应 (CurX,CurY) 
        //实际打印的位置行数应该加一
        x = m_nCurX + m_Block.X(i) + 1;             //改动
        //y坐标0，是左边的墙，所以y打印坐标要加一
        y = m_nCurY + m_Block.Y(i) + 1;
        ShowBg(x, y);
    }
}

//检查指定行的标记，是满则返回1
int CSense::CheckRowForE(int nRow)
{
    for (int i = 1; i < m_nMapWidth - 1; i++)
    {
        if ((&*m_pMap)[nRow*m_nMapWidth + i] == 0)
        {
            return NOTFULL;
        }
    }

    return FULL;
}

//将方块所占的 所有满行  标记为空行
void CSense::ResetBlockRowForE()
{
    int nRow = 0;

    //检查刚刚固定的方块所在的行，是否全满，是则标记为空，表示需要消行
    for (nRow = 0; nRow < 4; nRow++)
    {
        if (nRow + m_nCurX < m_nMapHeight - 1)
        {
            if ((&*m_nMapRowForE)[nRow + m_nCurX] == FULL)
            {
                (&*m_nMapRowForE)[nRow + m_nCurX] = EMPTY;
            }
        }
    }
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

    /*
        x = m_nCurX + m_Block.X(i) + 1;
        y = m_nCurY + m_Block.Y(i) + 1;

        方块矩阵的原点的坐标
    */

    if (nDiret == DOWN)
    {
        //下移的判断
        for (int i = 0; i < 4; i++)
        {
            //方块矩阵索引从-1开始，转换为Sense索引，要 - （-1)
            x = m_nCurX + m_Block.X(i) + 1 + 1;
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
            x = m_nCurX + m_Block.X(i) + 1;     //改动
            y = m_nCurY + m_Block.Y(i) + 1 + 1;

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
            x = m_nCurX + m_Block.X(i) + 1;                     //改动
            y = m_nCurY + m_Block.Y(i) + 1 - 1;

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
        x = m_nCurX + m_Block.X(i) + 1;
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
        x = m_nCurX + m_Block.X(i) + 1;
        y = m_nCurY + m_Block.Y(i) + 1;
        (&*m_pMap)[x*m_nMapWidth + y] = 1;

        if (CheckRowForE(x) == FULL)
        {
            (&*m_nMapRowForE)[x] = FULL;
        }
        else
        {
            (&*m_nMapRowForE)[x] = NOTFULL;
        }
    }
}

//将一行非空行，移动到另一行空行，并设置标记
void CSense::MoveRow(int nSrcRow, int nDstRow)
{
    for (int i = 1; i < m_nMapWidth - 1; i++)
    {
        (&*m_pMap)[nDstRow*m_nMapWidth + i] = (&*m_pMap)[nSrcRow*m_nMapWidth + i];
        (&*m_pMap)[nSrcRow*m_nMapWidth + i] = 0;
    }

    (&*m_nMapRowForE)[nDstRow] = NOTFULL;
    (&*m_nMapRowForE)[nSrcRow] = EMPTY;

}

void CSense::CSenseTryScroll()
{
    int nAllEmpty = 1;
    for (int nRow = m_nMapHeight - 2; nRow > 0; nRow--)
    {
        nAllEmpty = 1;

        //找到空行标记
        if ((&*m_nMapRowForE)[nRow] == EMPTY)
        {
            for (int nUnEmptyRow = nRow - 1; nUnEmptyRow > 0; nUnEmptyRow--)
            {
                //找到空行上面的非空行标记，//将非空行，下落到，最底下的空行
                if ((&*m_nMapRowForE)[nUnEmptyRow] == NOTFULL)
                {
                    nAllEmpty = 0;
                    MoveRow(nUnEmptyRow, nRow);
                    break;
                }
            }

            //如果执行到这里，说明当前空行上面全是空行，可以退出了
            if (nAllEmpty == 1)
            {
                return;
            }
        }

    }
}