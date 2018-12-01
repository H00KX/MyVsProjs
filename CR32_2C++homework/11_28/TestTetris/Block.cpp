#include "stdafx.h"
#include "Block.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

CBlock::CBlock()
{
    SetType();
    SetShape(m_Type);
}


void CBlock::LeftRotate()
{
    int coords[4][2];
    memcpy(coords, m_coords, sizeof(coords));

    for (int i = 0; i < 4; ++i)
    {
        SetX(i, -coords[i][1]);
        SetY(i, coords[i][0]);
    }

}

void CBlock::RightRotate()
{
    int coords[4][2];
    memcpy(coords, m_coords, sizeof(coords));

    for (int i = 0; i < 4; ++i)
    {
        SetX(i, coords[i][1]);
        SetY(i, -coords[i][0]);
    }
}



void CBlock::SetType()
{
    //产生随机的类型
    m_Type = (emBlockType)(rand() % 7 + 1);
}

void CBlock::SetShape(emBlockType nType)
{
    //总共7中类型的方块，每个方块形状，由4个小块组成，每个小块有[x][y]坐标
    /*   每个方块 4行4列,curX=-1,curY=-1 curX + 1 = 0  curX + 2 = 1
            -1    0    1    2

        -1   O    *    *

         0   *    *                 { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 }

         1

         2

    */
    static const int coordsTable[8][4][2] = {
        { { 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 } },
        { { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 } }, //1反 Z
        { { 0, -1 },{ 0, 0 },{ 1, 0 },{ 1, 1 } },   //2正 Z
        { { 0, -1 },{ 0, 0 },{ 0, 1 },{ 0, 2 } },   //3一横
        { { -1, 0 },{ 0, 0 },{ 1, 0 },{ 0, 1 } },   //4右土
        { { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } },    //5正方形
        { { -1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }, //6|____
        { { 1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }   //7|￣￣
    };

    
    //数据按中心对称交换
    for (int i = 0; i < 4; i++)
    {
        m_coords[i][0] = coordsTable[nType][i][0];
        m_coords[i][1] = coordsTable[nType][i][1];
    }
}
