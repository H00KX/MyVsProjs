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
                  30, // 高度 30 行 // 在1920*1080的显示器中最大值为60
                  30  // 宽度 30 列 // 1 列 = 1 个汉字 或 2 个英文 
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
                //能够旋转
                if (sense.BlockTryRotate())
                {
                    system("cls");
                    sense.DrawBg();
                    for (int i = 0; i < 4; i++)
                    {
                        x = sense.m_nCurX + sense.m_Block.X(i);
                        //y坐标0，是左边的墙，所以y打印坐标要加一
                        y = sense.m_nCurY + sense.m_Block.Y(i) + 1;
                        sense.ShowBlock(x, y);
                    }
                }


                //能够向下移动
                if (sense.BlockTryMove(DOWN))
                {
                    system("cls");
                    sense.DrawBg();
                    for (int i = 0; i < 4; i++)
                    {
                        x = sense.m_nCurX + sense.m_Block.X(i);
                        //y坐标0，是左边的墙，所以y打印坐标要加一
                        y = sense.m_nCurY + sense.m_Block.Y(i) + 1;
                        sense.ShowBlock(x, y);
                    }

                    cout << "LEFT Move" << endl;
                }
                else    //不能向下移动
                {
                    //固定，并转化为墙
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

