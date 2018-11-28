#include "stdafx.h"
#include "Sense.h"
#include <stdlib.h>


CSense::CSense(int xSize, int ySize)
{
    m_nMapWidth = xSize;
    m_nMapHeight = ySize;

    m_pMap = shared_ptr<char>(new char[m_nMapWidth * m_nMapHeight], \
                              std::default_delete<char[]>());

    m_nCurX = 0;
    m_nCurY = 10;

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

    //��ʼ������
    m_Block = CBlock();
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

bool CSense::BlockMoveable(int nDiret)
{
    return false;
}

bool CSense::BlockRotateable()
{
    return false;
}
