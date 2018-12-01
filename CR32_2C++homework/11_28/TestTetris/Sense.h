#pragma once
#include <iostream>
#include <memory>
#include "Block.h"
#include "setdisplay.h"

#define DOWN 2
#define LEFT  0
#define RIGHT 1

#define FULL 1
#define EMPTY 0
#define NOTFULL 2

using  namespace std;

class CSense
{
public:
    CSense() = delete;
    CSense(int xSize, int ySize);

    //画游戏界面背景
    void DrawBg();
    //画活动方块
    void DrawBlock();

    //画方块的一个点
    void ShowBlock(int x, int y);
    //画背景的一个点
    void ShowBg(int x, int y);

    //重新生成一个活动方块
    void CreateBlock();
    //不显示活动方块
    void ClearBlock();
    //固定活动方块，转化为墙
    void FixBlock();

    //尝试移动活动方块
    bool BlockTryMove(int nDiret);
    //尝试转动活动方块
    bool BlockTryRotate();

    //将活动方块所在行，的全满标记 重置为 空
    void ResetBlockRowForE();
    //将一个非空行，转移到一个全空行，并设置他们的标记
    void MoveRow(int nSrcRow, int nDstRow);
    //检查行是全满 还是 半满
    int CheckRowForE(int nRow);
    
    //尝试消行
    void CSenseTryScroll();

    int  m_nCurX;
    int  m_nCurY;
    CBlock m_Block;

private:

    std::shared_ptr<char> m_pMap;
    std::shared_ptr<char> m_nMapRowForE;

    int m_nMapWidth;
    int m_nMapHeight;

};

