#include "stdafx.h"
#include "Sense.h"
#include <stdlib.h>


CSense::CSense(int xSize, int ySize)
{
    m_nMapWidth = xSize;
    m_nMapHeight = ySize;

    m_pMap = shared_ptr<char>(new char[m_nMapWidth * m_nMapHeight], \
                              std::default_delete<char[]>());


    //����ǽ��Ҫ��ʼ��

    for (int i = 0; i < m_nMapHeight; i++)
    {

        for (int j = 0; j < m_nMapWidth; j++)
        {

            if (j == 0 || j == m_nMapWidth - 1 || i == m_nMapHeight - 1)
            {
                //���ñ߽�
                (&*m_pMap)[i*m_nMapWidth + j] = 1;
            }
            else
            {
                (&*m_pMap)[i*m_nMapWidth + j] = 0;
            }

        }
    }

    //��ʼ��һ���·���
    CreateBlock();

    DrawBg();
}


void CSense::DrawBg()
{

    for (int i = 0; i < m_nMapHeight; i++)
    {
        for (int j = 0; j < m_nMapWidth; j++)
        {
            //��ʾ�ÿ�Ϊ��
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

//���Ʒ���
void CSense::ShowBlock(int x, int y)
{
    WriteChar(x,  // �� 1 ��
              y,  // �� 1 ��
              "  ",
              SetConsoleColor(COLOR_BLACK, // 
                              COLOR_WHITE)  // ��ɫ����
    );
}

//���Ʊ���
void CSense::ShowBg(int x, int y)
{
    WriteChar(x,  // �� 1 ��
              y,  // �� 1 ��
              "  ",
              SetConsoleColor(COLOR_WHITE, // ��ɫǰ��
                              COLOR_BLACK)  // ��ɫ����
    );
}

void CSense::CreateBlock()
{
    m_nCurX = 5;
    m_nCurY = 3;
    m_Block = CBlock();
}

bool CSense::BlockTryMove(int nDiret)
{
    //Ҫ�ƶ��ķ������һ��������
    int x = 0;
    int y = 0;
    if (nDiret == DOWN)
    {
        //���Ƶ��ж�
        for (int i = 0; i < 4; i++)
        {
            //�������������-1��ʼ��ת��ΪSense������Ҫ - ��-1)
            x = m_nCurX + m_Block.X(i) + 1;
            y = m_nCurY + m_Block.Y(i);

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1 ||
                x >= m_nMapHeight - 1 || y >= m_nMapWidth - 1)
            {
                return false;
            }
        }

        m_nCurX++;  //x�����һ��������
        return true;
    }


    if (nDiret == RIGHT)
    {
        for (int i = 0; i < 4; i++)
        {
            //�������������-1��ʼ��ת��ΪSense������Ҫ ƫ�� ��-1)
            x = m_nCurX + m_Block.X(i);
            y = m_nCurY + m_Block.Y(i) + 1;

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1)
            {
                return false;
            }
        }

        m_nCurY++;  //y�����һ��������
        return true;
    }

    if (nDiret == LEFT)
    {
        for (int i = 0; i < 4; i++)
        {
            //�������������-1��ʼ��ת��ΪSense������Ҫ - ��-1)
            x = m_nCurX + m_Block.X(i);
            y = m_nCurY + m_Block.Y(i);

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1)
            {
                return false;
            }
        }

        m_nCurY--;  //y�����һ��������
        return true;
    }
}

bool CSense::BlockTryRotate()
{
    int x = 0;
    int y = 0;
    //����ת��֮���ж��Ƿ����ص������У���ת��ȥ��
    m_Block.RightRotate();

    for (int i = 0; i < 4; i++)
    {
        //�������������-1��ʼ��ת��ΪSense������Ҫ - ��-1)
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
