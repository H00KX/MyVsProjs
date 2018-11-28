#include "stdafx.h"
#include "Block.h"
#include <stdlib.h>
#include <stdio.h>


CBlock::CBlock()
{
    SetType();
    SetShape(m_Type);
}

//这个才是右转？???
void CBlock::LeftRotate()
{
    int coords[4][2];
    memcpy(coords, m_coords, sizeof(coords));

    for (int i = 0; i < 4; ++i)
    {
        SetX(i, coords[i][1]);
        SetY(i, -coords[i][0]);
    }

}

void CBlock::RightRotate()
{
    int coords[4][2];
    memcpy(coords, m_coords, sizeof(coords));

    for (int i = 0; i < 4; ++i)
    {
        SetX(i, -coords[i][1]);
        SetY(i, coords[i][0]);
    }
}

//旋转方块


void CBlock::SetType()
{
    //产生随机的类型
    m_Type = (emBlockType)(rand() % 7 + 1);
}

void CBlock::SetShape(emBlockType nType)
{
    //总共7中类型的方块，每个方块形状，由4个小块组成，每个小块有[x][y]坐标
    /*
        每个方块 4行4列
            -1    0    1    2

        -1        *    *

         0   *    *                 { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 }

         1

         2

    */

    static const int coordsTable[8][4][2] = {
        { { 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 } },
        { { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 } }, //反 Z
        { { 0, -1 },{ 0, 0 },{ 1, 0 },{ 1, 1 } },   //正 Z
        { { 0, -1 },{ 0, 0 },{ 0, 1 },{ 0, 2 } },   //一横
        { { -1, 0 },{ 0, 0 },{ 1, 0 },{ 0, 1 } },   //右土
        { { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } },    //正方形
        { { -1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }, //
        { { 1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }
    };

    for (int i = 0; i < 4; i++)
    {
        m_coords[i][0] = coordsTable[nType][i][0];
        m_coords[i][1] = coordsTable[nType][i][1];
    }
}
