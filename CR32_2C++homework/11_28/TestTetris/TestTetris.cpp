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


    while (true)
    {
        if (_kbhit())
        {
            char ch;
            ch = _getch();

            //clearBg();
            if (ch = 'a')
            {
                for (int i = 0; i < 4; i++)
                {
                    x = sense.m_nCurX + sense.m_Block.X(i);
                    y = sense.m_nCurY + sense.m_Block.Y(i) + 1;
                    sense.ShowBlock(x, y);
                }
                //�ܹ���ת
                if (sense.BlockTryRotate())
                {
                    system("cls");
                    sense.DrawBg();
                    for (int i = 0; i < 4; i++)
                    {
                        x = sense.m_nCurX + sense.m_Block.X(i);
                        //y����0������ߵ�ǽ������y��ӡ����Ҫ��һ
                        y = sense.m_nCurY + sense.m_Block.Y(i) + 1;
                        sense.ShowBlock(x, y);
                    }
                }


                //�ܹ������ƶ�
                if (sense.BlockTryMove(DOWN))
                {
                    system("cls");
                    sense.DrawBg();
                    for (int i = 0; i < 4; i++)
                    {
                        x = sense.m_nCurX + sense.m_Block.X(i);
                        //y����0������ߵ�ǽ������y��ӡ����Ҫ��һ
                        y = sense.m_nCurY + sense.m_Block.Y(i) + 1;
                        sense.ShowBlock(x, y);
                    }

                    cout << "LEFT Move" << endl;
                }
                else    //���������ƶ�
                {
                    //�̶�����ת��Ϊǽ
                    sense.FixBlock();
                    sense.CreateBlock();
                }

            }
            else if (ch == 'd')
            {
                //block.RightRotate();
            }
        }



    }



    return 0;
}

