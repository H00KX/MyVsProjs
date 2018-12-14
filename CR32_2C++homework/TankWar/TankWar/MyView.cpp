#include "stdafx.h"
#include <malloc.h>
#include "MyView.h"

#include "glut\glut.h"


int TankWarObj::m_nMovStep = 25;

unsigned char g_mapData[26][26] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
    0x01, 0x01, 0x00, 0x00, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x01,  0x01,
    0x02, 0x02, 0x00, 0x00, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x02,  0x02,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00,	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00,  0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x00, 0x01, 0x00,	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00,
};

CMyView::CMyView()
{
    //��pcx�ļ��ּ���̹��ͼƬ�ز�
    CImageBuf ImageBuf;
    ImageBuf.LoadPcx("data\\object.pcx");

    //��ȡש���ݵ�Ԫ��
    for (int i = 1; i <= 5; i++)
    {
        ImageBuf.CopyImage(0 + (i - 1) * 25, 256, 25, 25, MapPic[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(150 + (i + 1) * 50, 50, 50, 49, TankPic[0][i]);             //�����ϡ��¡����ҳ���tank
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(150 + (i + 1) * 50, 0, 50, 49, TankPic[1][i]);             //�����ϡ��¡����ҳ���tank
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(0 + (i) * 50, 0, 50, 49, TankPic[2][i]);             //�����ϡ��¡����ҳ���tank
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(150 + (i + 1) * 50, 201, 50, 49, TankPic[3][i]);             //�����ϡ��¡����ҳ���tank
    }

    for (int i = 0; i <= 5; i++)
    {
        ImageBuf.CopyImage(50 + i * 50, 150, 50, 50, BoomPic[i]);                       //for boom
    }

    for (int i = 0; i < 2; i++)
    {
        ImageBuf.CopyImage(i * 15, 150, 15, 15, BulletPic[i]);             //�����ϡ��¡����ҳ���tank
    }

    ImageBuf.CopyImage(0, 100, 50, 50, HomeBase);             //�����ϡ��¡����ҳ���tank


                                                              //��ʼ����ǰ������
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            m_mapData[i][j] = g_mapData[i][j];
        }
    }

    //xyΪ̹�����½��ڵ�ͼ�е�����
    m_MyTank.SetCurX(9 * 25);
    m_MyTank.SetCurY(25 * 25);

    TONode *p = nullptr;
    tList.Obj = &m_MyTank;

    p = (TONode*)malloc(sizeof(TONode));
    p->Obj = new RobotTank(0, 25);
    AddObj(&tList, p);

    p = (TONode*)malloc(sizeof(TONode));
    p->Obj = new RobotTank(8 * 25, 25);
    AddObj(&tList, p);

    p = (TONode*)malloc(sizeof(TONode));
    p->Obj = new RobotTank(16 * 25, 25);
    AddObj(&tList, p);

    p = (TONode*)malloc(sizeof(TONode));
    p->Obj = new RobotTank(24 * 25, 25);
    AddObj(&tList, p);

}

CMyView::~CMyView()
{
}

void CMyView::drawMap()
{

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (m_mapData[i][j] == 0x01)
            {
                DrawElement(j * 25, (25 - i) * 25, m_mapData[i][j]);
            }
            else if (m_mapData[i][j] == 0x02)
            {
                DrawElement(j * 25, (25 - i) * 25, m_mapData[i][j]);
            }
            else if (m_mapData[i][j] == 0x05)
            {
                DrawElement(j * 25, (25 - i) * 25, m_mapData[i][j]);
            }
            else if (m_mapData[i][j] == 0x06)
            {
                DrawHomeBase(j * 25, (25 - i) * 25);
            }
        }
    }

    //����ϵԭ��(0,0) Ϊ���½ǣ�x��ֱ���ϣ�yˮƽ����
    //��ʼ����̹��

    TONode *p = &tList;
    while (p != nullptr)
    {
        if (p->Obj->m_nID == 0 || p->Obj->m_nID == 1)
        {
            DrawTank(p->Obj->CurX(), 650 - p->Obj->CurY() - 25, p->Obj->m_nType, p->Obj->m_nRotate);
        }
        if (p->Obj->m_nID == 2 || p->Obj->m_nID == 3)
        {
            DrawBullet(p->Obj->CurX(), 650 - p->Obj->CurY(), p->Obj->m_nType);
        }
        p = p->Next;
    }
}

//CurX,CurY ̹�˵����½� �ڵ�ͼ����ϵ��ԭ��(0,0)���е�λ��

//��ͼ����ϵԭ��(0,0) Ϊ���½ǣ�x��ֱ���ϣ�yˮƽ����
void CMyView::OnUp()
{

    TONode *p = &tList;

    while (p->Obj != nullptr&&p->Obj->m_nID != 0)
    {
        p = p->Next;
    }

    p->Obj->SetRotate(0);
    RunEach(p);

    return;
}

void CMyView::OnDown()
{

    TONode *p = &tList;

    while (p->Obj != nullptr&&p->Obj->m_nID != 0)
    {
        p = p->Next;
    }

    p->Obj->SetRotate(2);
    RunEach(p);

    return;

}

void CMyView::OnLeft()
{
    TONode *p = &tList;

    while (p->Obj != nullptr&&p->Obj->m_nID != 0)
    {
        p = p->Next;
    }

    p->Obj->SetRotate(3);
    RunEach(p);

    return;

}

void CMyView::OnRight()
{
    TONode *p = &tList;

    while (p->Obj != nullptr&&p->Obj->m_nID != 0)
    {
        p = p->Next;
    }

    p->Obj->SetRotate(1);
    RunEach(p);

    return;
}

void CMyView::OnFire()
{
    TONode *p = &tList;

    while (p->Obj != nullptr&&p->Obj->m_nID != 0)
    {
        p = p->Next;
    }

    p->Obj->SetFire(1);
    ObjFire(p->Obj);
    p->Obj->SetFire(0);
    //RunEach(p);
    AllRun();
    return;
}

//������ң����Զ�����
int CMyView::AllRun()
{
    TONode *p = &tList;

    while (p->Obj != nullptr)
    {
        if (p->Obj->m_nID != 0)
        {
            p->Obj->SetRotate(0);
            //��ǹ
            if (p->Obj->m_nID == 1)
            {
                p->Obj->SetFire(1);
                ObjFire(p->Obj);
                p->Obj->SetFire(0);
            }
        }
        if (p->Next != NULL)
        {
            p = p->Next;
        }
        else
        {
            break;
        }

    }

    p = &tList;
    while (p->Obj != nullptr)
    {
        if (p->Obj->m_nID != 0)
        {
            RunEach(p);
        }
        if (p->Next != NULL)
        {
            p = p->Next;
        }
        else
        {
            break;
        }

    }

    return 0;
}

//��������ײ
int CMyView::CheckObj(TankWarObj *obj, TankWarObj *another)
{
    return obj->CheckObj(obj, another);
}

//�ɵ���ǽ����ү
void CMyView::DestroyWallForObj(TankWarObj * obj)
{
    int x = 0;
    int y = 0;

    if (obj->m_nRotate == 0)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() - 1 * obj->m_nMovStep) / 25;

    }
    if (obj->m_nRotate == 1)
    {
        x = (obj->CurX() + 1 * obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }
    if (obj->m_nRotate == 2)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() + 1 * obj->m_nMovStep) / 25;
    }
    if (obj->m_nRotate == 3)
    {
        x = (obj->CurX() - 1 * obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }

    if (m_mapData[y][x] == 0x1)
    {
        m_mapData[y][x] = 0;
    }

    if (m_mapData[y][x] == 0x6)
    {
        std::cout << "��ү���ˣ�����\r\n";
        system("pause");
        exit(EXIT_SUCCESS);
    }
}

//���������Զ�����
void CMyView::RunEach(TONode * p)
{
    TONode *another = &tList;

    //nFlag ==0 ��ʾ�����ƶ�
    //nFlag ==1 ��ʾ�������ƶ�
    int nFlag = 0;
    int nChkWall = 0;

    //����ײǽ�������ƶ�
    nChkWall = CheckWall(p->Obj);
    //����1 ��ʾ̹��ײǽ�� �ӵ�ײ��ǽ
    if (nChkWall == 1)
    {
        //���ӵ�,�ٵ�ǽ
        if (p->Obj->m_nID == 2 || p->Obj->m_nID == 3)
        {
            DestroyWallForObj(p->Obj);
            p = DelObj(&tList, p);
            return;
        }
    }
    //����2 ��ʾ�ӵ����磬 ײ��
    else if (nChkWall == 2)
    {
        p = DelObj(&tList, p);
        return;
    }
    //û��ײǽ
    else
    {
        another = &tList;
        while (another->Obj != nullptr)
        {

            if (p != another)
            {   //����0����ײ,�����ƶ�
                if (CheckObj(p->Obj, another->Obj) == 0)
                {
                    nFlag = 1;
                    //��ײ���У����ӵ���������������
                    //��̹0����̹1�����ӵ�2�����ӵ�3
                    if ((p->Obj->m_nID | another->Obj->m_nID) != 1)
                    {
                        if (p->Obj->m_nID == 0 || another->Obj->m_nID == 0)
                        {
                            //��ұ����С��˳�
                            std::cout << "������ˣ�����\r\n";
                            system("pause");
                            exit(EXIT_SUCCESS);
                        }
                        p = DelObj(&tList, p);
                        another = DelObj(&tList, another);
                    }
                    break;
                }

            }
            if (another->Next != NULL)
            {
                another = another->Next;
            }
            else
            {
                break;
            }


        }
        //���Ϊ���ƶ�
        if (nFlag == 0)
        {
            //ûײǽ��û��ײ
            //���ƶ�
            p->Obj->Move();
        }

    }
}

void CMyView::ObjFire(TankWarObj * obj)
{
    int x = 0;
    int y = 0;

    if (obj->m_nRotate == 0)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() - 1 * obj->m_nMovStep) / 25;

    }
    if (obj->m_nRotate == 1)
    {
        x = (obj->CurX() + 1 * obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }
    if (obj->m_nRotate == 2)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() + 1 * obj->m_nMovStep) / 25;
    }
    if (obj->m_nRotate == 3)
    {
        x = (obj->CurX() - 1 * obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }

    //����
    TONode *pB = (TONode*)malloc(sizeof(TONode));
    pB->Obj = new Bullet(x * 25, y * 25, obj->m_nRotate, obj->m_nID + 2);
    AddObj(&tList, pB);

}

//���ײǽ
int CMyView::CheckWall(TankWarObj * obj)
{
    int x = 0;
    int y = 0;

    if (obj->m_nRotate == 0)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() - obj->m_nMovStep) / 25;

    }
    if (obj->m_nRotate == 1)
    {
        x = (obj->CurX() + obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }
    if (obj->m_nRotate == 2)
    {
        x = obj->CurX() / 25;
        y = (obj->CurY() + obj->m_nMovStep) / 25;
    }
    if (obj->m_nRotate == 3)
    {
        x = (obj->CurX() - obj->m_nMovStep) / 25;
        y = obj->CurY() / 25;
    }

    return obj->CheckWall(m_mapData, x, y);
}

void MixPic(int x, int y, int w, int h, unsigned char *buf)             //glReadPixels 
{
    int PixelByte = 4;        //for RGBA color

    int SrcTempPos = 0, TempPos = 0;
    unsigned char *Temp = new unsigned char[w*h*PixelByte];

    glReadPixels(x, y, w, h, GL_RGB, GL_UNSIGNED_BYTE, Temp);
    glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, Temp);
    for (int i = 0; i < w*h; i++)
    {
        if ((buf[SrcTempPos + 3]) == 0)          //�ҳ��˱߿�Ϊ��ɫ�Ĳ���
        {
            memcpy(&buf[SrcTempPos], &Temp[TempPos], 3);         //��ʾ����ɫ
        }
        SrcTempPos += 4;
        TempPos += PixelByte;
    }
    delete[]Temp;
}

//���ƻ���Ԫ�أ� nType = 1 ��ʾש  2 �� 3 ǳ������ 4 �������� 5 �� 
void CMyView::DrawElement(int x, int y, int nType)
{
    glRasterPos2i(x, y);      //Ϊ���ز���ָ����դλ��  ��25*i j  Ϊ����ʾͼ��Ĳ��ص�
    MixPic(25, 25, 25, 25, MapPic[nType]);
    glDrawPixels(25, 25, GL_RGBA, GL_UNSIGNED_BYTE, MapPic[nType]);  //��һ�����ؿ�д��֡����  
}

void CMyView::DrawBg(int x, int y)
{
    //���ƾ���
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x, y, x + 25.0f, y + 25.0f);
}

void CMyView::DrawBoom(int x, int y, int nType)
{

    glRasterPos2i(x, y);      //Ϊ���ز���ָ����դλ��  ��25*i j  Ϊ����ʾͼ��Ĳ��ص�
    glDrawPixels(50, 50, GL_RGBA, GL_UNSIGNED_BYTE, BoomPic[nType]);  //��һ�����ؿ�д��֡����  
}

void CMyView::DrawTank(int x, int y, int nType, int nRotate)
{

    glRasterPos2i(x, y);      //Ϊ���ز���ָ����դλ��  ��25*i j  Ϊ����ʾͼ��Ĳ��ص�
    glDrawPixels(50, 49, GL_RGBA, GL_UNSIGNED_BYTE, TankPic[nType][nRotate]);  //��һ�����ؿ�д��֡����  
}

void CMyView::DrawHomeBase(int x, int y)
{

    glRasterPos2i(x, y);      //Ϊ���ز���ָ����դλ��  ��25*i j  Ϊ����ʾͼ��Ĳ��ص�				
    glDrawPixels(50, 50, GL_RGBA, GL_UNSIGNED_BYTE, HomeBase);  //��һ�����ؿ�д��֡����  

}

void CMyView::DrawBullet(int x, int y, int nType)
{

    glRasterPos2i(x, y);      //Ϊ���ز���ָ����դλ��  ��25*i j  Ϊ����ʾͼ��Ĳ��ص�
    glDrawPixels(15, 15, GL_RGBA, GL_UNSIGNED_BYTE, BulletPic[nType]);  //��һ�����ؿ�д��֡����  
}

