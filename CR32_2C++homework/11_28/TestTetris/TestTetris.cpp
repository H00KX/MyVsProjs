// TestTetris.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "setdisplay.h"
#include "Sense.h"

int main()
{
    int x = 0;
    int y = 0;

    srand(time(NULL));
    // 1. ���ÿ���̨����ʹ��ڴ�С
    SetWindowSize("����̨��ɫ��������", // ����
                  30, // �߶� 30 �� // ��1920*1080����ʾ�������ֵΪ60
                  30  // ��� 30 �� // 1 �� = 1 ������ �� 2 ��Ӣ�� 
    );

    CSense sense(10, 10);

    sense.DrawBlock();

    while (true)
    {
        if (_kbhit())
        {
            char ch;
            ch = _getch();

            //clearBg();
            if (ch == 's')
            {
                //������
                sense.ClearBlock();
                //�ܹ������ƶ��������»�
                if (sense.BlockTryMove(DOWN))
                {
                    sense.DrawBlock();
                }
                else    //���������ƶ�
                {
                    //�����»�
                    sense.DrawBlock();

                    //�̶�����ת��Ϊǽ
                    sense.FixBlock();
                    int x = 0;
                    int y = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        x = m_nCurX + m_Block.X(i);
                        CheckRow(x);
                    }
                    int a = sense.CheckRow(8);
                    sense.CreateBlock();
                }


            }
            else if (ch == 'w')
            {
                //������
                sense.ClearBlock();
                //�ܹ���ת
                sense.BlockTryRotate();

                sense.DrawBlock();

            }
            else if (ch == 'a')
            {
                //������
                sense.ClearBlock();
                //�ܹ������ƶ�
                sense.BlockTryMove(LEFT);

                sense.DrawBlock();

            }
            else if (ch == 'd')
            {
                //������
                sense.ClearBlock();
                //�ܹ������ƶ�
                sense.BlockTryMove(RIGHT);

                sense.DrawBlock();

            }
        }



    }



    return 0;
}

