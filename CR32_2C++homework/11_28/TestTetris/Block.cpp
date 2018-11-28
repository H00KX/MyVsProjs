#include "stdafx.h"
#include "Block.h"
#include <stdlib.h>
#include <stdio.h>


CBlock::CBlock()
{
    SetType();
    SetShape(m_Type);
}

//���������ת��???
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

//��ת����


void CBlock::SetType()
{
    //�������������
    m_Type = (emBlockType)(rand() % 7 + 1);
}

void CBlock::SetShape(emBlockType nType)
{
    //�ܹ�7�����͵ķ��飬ÿ��������״����4��С����ɣ�ÿ��С����[x][y]����
    /*
        ÿ������ 4��4��
            -1    0    1    2

        -1        *    *

         0   *    *                 { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 }

         1

         2

    */

    static const int coordsTable[8][4][2] = {
        { { 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 } },
        { { 0, -1 },{ 0, 0 },{ -1, 0 },{ -1, 1 } }, //�� Z
        { { 0, -1 },{ 0, 0 },{ 1, 0 },{ 1, 1 } },   //�� Z
        { { 0, -1 },{ 0, 0 },{ 0, 1 },{ 0, 2 } },   //һ��
        { { -1, 0 },{ 0, 0 },{ 1, 0 },{ 0, 1 } },   //����
        { { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } },    //������
        { { -1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }, //
        { { 1, -1 },{ 0, -1 },{ 0, 0 },{ 0, 1 } }
    };

    for (int i = 0; i < 4; i++)
    {
        m_coords[i][0] = coordsTable[nType][i][0];
        m_coords[i][1] = coordsTable[nType][i][1];
    }
}