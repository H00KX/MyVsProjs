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
    srand(time(NULL));
    // 1. ���ÿ���̨����ʹ��ڴ�С
    SetWindowSize("����̨��ɫ��������", // ����
                  30, // �߶� 30 �� // ��1920*1080����ʾ�������ֵΪ60
                  30  // ��� 30 �� // 1 �� = 1 ������ �� 2 ��Ӣ�� 
    );

    CSense sense(20, 30);


    while (true)
    {
        int nOffset = 10;
        //�����ɫ
        for (int i = 0; i < 4; i++)
        {
            //�ֱ��ӡ���ĸ������
            /*sense.ShowBlock(sense.m_Block.X(i) + nOffset,
                            sense.m_Block.Y(i) + nOffset);*/
        }


        if (_kbhit())
        {
            char ch;
            ch = _getch();


            /*  clearBg();
              if (ch == 'a') {
                  block.LeftRotate();

              }
              else if (ch == 'd') {
                  block.RightRotate();
              }*/
        }



    }



    return 0;
}

