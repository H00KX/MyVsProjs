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

    //����Ϸ���汳��
    void DrawBg();
    //�������
    void DrawBlock();

    //�������һ����
    void ShowBlock(int x, int y);
    //��������һ����
    void ShowBg(int x, int y);

    //��������һ�������
    void CreateBlock();
    //����ʾ�����
    void ClearBlock();
    //�̶�����飬ת��Ϊǽ
    void FixBlock();

    //�����ƶ������
    bool BlockTryMove(int nDiret);
    //����ת�������
    bool BlockTryRotate();

    //������������У���ȫ����� ����Ϊ ��
    void ResetBlockRowForE();
    //��һ���ǿ��У�ת�Ƶ�һ��ȫ���У����������ǵı��
    void MoveRow(int nSrcRow, int nDstRow);
    //�������ȫ�� ���� ����
    int CheckRowForE(int nRow);
    
    //��������
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

