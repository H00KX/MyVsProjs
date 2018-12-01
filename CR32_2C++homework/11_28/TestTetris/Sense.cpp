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

        if (i < m_nMapHeight - 1)
        {
            //m_nMapRowForE[Row]=EMPYT
            (&*m_nMapRowForE)[i] = 0;
        }

    }
    //��ʼ��һ���·���
    CreateBlock();

    //DrawBg();
}

//����������
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

    WriteChar(8,  // �� 1 ��
              40,  // �� 1 ��
              "welcome to Tetrie��",
              SetConsoleColor(COLOR_RED, // 
                              COLOR_BLACK));
    WriteChar(10,  // �� 1 ��
              40,  // �� 1 ��
              "your score is :",
              SetConsoleColor(COLOR_RED, // 
                              COLOR_BLACK));
}

//����������
void CSense::DrawBlock()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        x = m_nCurX + m_Block.X(i) + 1;
        //y����0������ߵ�ǽ������y��ӡ����Ҫ��һ
        y = m_nCurY + m_Block.Y(i) + 1;
        ShowBlock(x, y);
    }
}

//���Ʒ���ɫ
void CSense::ShowBlock(int x, int y)
{
    WriteChar(x,  // �� 1 ��
              y,  // �� 1 ��
              "  ",
              SetConsoleColor(COLOR_BLUE, // 
                              COLOR_BLACK)  // ��ɫǰ��
    );
}

//���Ʊ���ɫ
void CSense::ShowBg(int x, int y)
{
    WriteChar(x,  // �� 1 ��
              y,  // �� 1 ��
              "  ",
              SetConsoleColor(COLOR_BLACK, // ��ɫǰ��
                              COLOR_WHITE)  // ��ɫǰ��
    );
}

//Ĩ����������
void CSense::ClearBlock()
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 4; i++)
    {
        //������� ԭ�� ��-1��-1������0�У�0�У���Ӧ (CurX,CurY) 
        //ʵ�ʴ�ӡ��λ������Ӧ�ü�һ
        x = m_nCurX + m_Block.X(i) + 1;             //�Ķ�
        //y����0������ߵ�ǽ������y��ӡ����Ҫ��һ
        y = m_nCurY + m_Block.Y(i) + 1;
        ShowBg(x, y);
    }
}

//���ָ���еı�ǣ������򷵻�1
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

//��������ռ�� ��������  ���Ϊ����
void CSense::ResetBlockRowForE()
{
    int nRow = 0;

    //���ոչ̶��ķ������ڵ��У��Ƿ�ȫ����������Ϊ�գ���ʾ��Ҫ����
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

//����һ���·���
void CSense::CreateBlock()
{
    m_nCurX = 3;
    m_nCurY = 3;
    m_Block = CBlock();
}

//�����ƶ�
bool CSense::BlockTryMove(int nDiret)
{
    //Ҫ�ƶ��ķ������һ��������
    int x = 0;
    int y = 0;

    /*
        x = m_nCurX + m_Block.X(i) + 1;
        y = m_nCurY + m_Block.Y(i) + 1;

        ��������ԭ�������
    */

    if (nDiret == DOWN)
    {
        //���Ƶ��ж�
        for (int i = 0; i < 4; i++)
        {
            //�������������-1��ʼ��ת��ΪSense������Ҫ - ��-1)
            x = m_nCurX + m_Block.X(i) + 1 + 1;
            y = m_nCurY + m_Block.Y(i) + 1;

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1 ||
                x >= m_nMapHeight - 1)
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
            x = m_nCurX + m_Block.X(i) + 1;     //�Ķ�
            y = m_nCurY + m_Block.Y(i) + 1 + 1;

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1 ||
                y >= m_nMapWidth - 1)
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
            x = m_nCurX + m_Block.X(i) + 1;                     //�Ķ�
            y = m_nCurY + m_Block.Y(i) + 1 - 1;

            if ((&*m_pMap)[x*m_nMapWidth + y] == 1 || y <= 0)
            {
                return false;
            }
        }

        m_nCurY--;  //y�����һ��������
        return true;
    }
}

//������ת
bool CSense::BlockTryRotate()
{
    int x = 0;
    int y = 0;
    //����ת��֮���ж��Ƿ����ص������У���ת��ȥ��
    m_Block.RightRotate();

    for (int i = 0; i < 4; i++)
    {
        //�������������-1��ʼ��ת��ΪSense������Ҫ - ��-1)
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

//�̶���ת��Ϊǽ
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

//��һ�зǿ��У��ƶ�����һ�п��У������ñ��
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

        //�ҵ����б��
        if ((&*m_nMapRowForE)[nRow] == EMPTY)
        {
            for (int nUnEmptyRow = nRow - 1; nUnEmptyRow > 0; nUnEmptyRow--)
            {
                //�ҵ���������ķǿ��б�ǣ�//���ǿ��У����䵽������µĿ���
                if ((&*m_nMapRowForE)[nUnEmptyRow] == NOTFULL)
                {
                    nAllEmpty = 0;
                    MoveRow(nUnEmptyRow, nRow);
                    break;
                }
            }

            //���ִ�е����˵����ǰ��������ȫ�ǿ��У������˳���
            if (nAllEmpty == 1)
            {
                return;
            }
        }

    }
}