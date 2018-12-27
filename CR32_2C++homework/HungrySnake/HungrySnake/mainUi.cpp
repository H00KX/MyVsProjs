// HungrySnake.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HungrySnake.h"
#include "map.h"
#include "setdisplay.h"
#include <conio.h>

void GameOver()
{

    WriteChar(32,  // 第 1 行
              7,  // 第 1 列
              "*************G G**************\r\n",
              SetConsoleColor(COLOR_RED, // 黑色前景
                              COLOR_WHITE));

}

int main()
{
    SetWindowSize("贪食蛇 v0.1", // 标题
                  36, // 高度 30 行 // 在1920*1080的显示器中最大值为60
                  30  // 宽度 30 列 // 1 列 = 1 个汉字 或 2 个英文 
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

