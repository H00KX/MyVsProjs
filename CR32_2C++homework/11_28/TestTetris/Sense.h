#pragma once
#include <iostream>
#include <memory>
#include "Block.h"
#include "setdisplay.h"

using  namespace std;

class CSense
{
public:
    CSense(int xSize, int ySize);

    void DrawBg();

    void ShowBlock(int x, int y);
    void ShowBg(int x, int y);


private:
    //char* m_pMap;

    std::shared_ptr<char> m_pMap;

    int m_nMapWidth;
    int m_nMapHeight;

    CBlock m_Block;
    int  m_nCurX;
    int m_nCurY;

};

