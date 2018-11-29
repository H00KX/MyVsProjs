#pragma once
#include <iostream>
#include <memory>
#include "Block.h"
#include "setdisplay.h"

#define DOWN -1
#define LEFT  0
#define RIGHT 1

using  namespace std;

class CSense
{
public:
    CSense() = delete;
    CSense(int xSize, int ySize);

    void DrawBg();
    void DrawBlock();

    void ShowBlock(int x, int y);
    void ClearBlock();
    void ShowBg(int x, int y);

    void CreateBlock();
    bool BlockTryMove(int nDiret);
    bool BlockTryRotate();
    void FixBlock();

    int  m_nCurX;
    int  m_nCurY;
    CBlock m_Block;

private:

    std::shared_ptr<char> m_pMap;

    int m_nMapWidth;
    int m_nMapHeight;



};

