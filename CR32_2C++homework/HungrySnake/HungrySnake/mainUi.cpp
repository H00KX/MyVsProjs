// HungrySnake.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "HungrySnake.h"
#include "map.h"
#include "setdisplay.h"
#include <conio.h>

void GameOver()
{

    WriteChar(32,  // �� 1 ��
              7,  // �� 1 ��
              "*************G G**************\r\n",
              SetConsoleColor(COLOR_RED, // ��ɫǰ��
                              COLOR_WHITE));

}

int main()
{
    SetWindowSize("̰ʳ�� v0.1", // ����
                  36, // �߶� 30 �� // ��1920*1080����ʾ�������ֵΪ60
                  30  // ��� 30 �� // 1 �� = 1 ������ �� 2 ��Ӣ�� 
    );

    int nWidth = 30;
    int nHeight = 30;
    int nMove = 0;

    CMap  map(nWidth, nHeight);
    Snake* pS = new Snake;

    map.ReInitFood();



    map.DrawBg();
    map.DrawFood();
    pS->Draw();
    //pS->DelHideTail();
    //pS->AddDrawTail();

    while (true)
    {
        nMove = 0;

        if (_kbhit())
        {
            char ch;
            ch = _getch();

            //clearBg();
            if (ch == 'W')
            {
                nMove = pS->TryMove(map.GetMap(), nWidth, 0);

                if (pS->EatFood(map.GetFood()))
                {
                    map.ReInitFood();
                }
                else
                {
                    if (nMove == 1)
                    {
                        pS->DelHideTail();
                        if (pS->GetSize() == 0)
                        {
                            GameOver();
                        }

                    }


                }
            }
            else if (ch == 'D')
            {
                nMove = pS->TryMove(map.GetMap(), nWidth, 1);
                if (pS->EatFood(map.GetFood()))
                {
                    map.ReInitFood();
                }
                else
                {
                    if (nMove == 1)
                    {
                        pS->DelHideTail();
                        if (pS->GetSize() == 0)
                        {
                            GameOver();
                        }
                    }
                }
            }
            else if (ch == 'S')
            {
                nMove = pS->TryMove(map.GetMap(), nWidth, 2);
                if (pS->EatFood(map.GetFood()))
                {
                    map.ReInitFood();
                }
                else
                {
                    if (nMove == 1)
                    {
                        pS->DelHideTail();
                        if (pS->GetSize() == 0)
                        {
                            GameOver();
                        }
                    }
                }
            }


            else if (ch == 'A')
            {
                nMove = pS->TryMove(map.GetMap(), nWidth, 3);
                if (pS->EatFood(map.GetFood()))
                {
                    map.ReInitFood();
                }
                else
                {
                    if (nMove == 1)
                    {
                        pS->DelHideTail();
                        if (pS->GetSize() == 0)
                        {
                            GameOver();
                        }
                    }
                }
            }

        }
    }

    return 0;
}

