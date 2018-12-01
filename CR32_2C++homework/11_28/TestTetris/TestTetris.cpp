// TestTetris.cpp : 定义控制台应用程序的入口点。
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
    // 1. 设置控制台标题和窗口大小
    SetWindowSize("控制台颜色测试用例", // 标题
                  29, // 高度 30 行 // 在1920*1080的显示器中最大值为60
                  60  // 宽度 30 列 // 1 列 = 1 个汉字 或 2 个英文 
    );

    CSense sense(30, 30);

    sense.DrawBg();
    sense.DrawBlock();

    

    while (true)
    {
        if (_kbhit())
        {
            char ch;
            ch = _getch();

            //clearBg();
            if (ch == 'S')
            {
                //先消除
                sense.ClearBlock();
                //能够向下移动，再重新画
                if (sense.BlockTryMove(DOWN))
                {
                    sense.DrawBlock();
                }
                else    //不能向下移动
                {
                    //再重新画
                    sense.DrawBlock();

                    //固定，并转化为墙
                    sense.FixBlock();

                    sense.ResetBlockRowForE();
                    sense.CSenseTryScroll();
                    sense.CreateBlock();

                    system("cls");
                    sense.DrawBg();
                    sense.DrawBlock();
                }


            }
            else if (ch == 'W')
            {
                //先消除
                sense.ClearBlock();
                //尝试旋转
                sense.BlockTryRotate();

                sense.DrawBlock();

            }
            else if (ch == 'A')
            {
                //先消除
                sense.ClearBlock();
                //尝试向左移动
                sense.BlockTryMove(LEFT);

                sense.DrawBlock();

            }
            else if (ch == 'D')
            {
                //先消除
                sense.ClearBlock();
                //尝试向右移动
                sense.BlockTryMove(RIGHT);

                sense.DrawBlock();

            }
        }



    }



    return 0;
}

