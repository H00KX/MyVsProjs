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
    //从pcx文件种加载坦克图片素材
    CImageBuf ImageBuf;
    ImageBuf.LoadPcx("data\\object.pcx");

    //获取砖，草等元素
    for (int i = 1; i <= 5; i++)
    {
        ImageBuf.CopyImage(0 + (i - 1) * 25, 256, 25, 25, MapPic[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(150 + (i + 1) * 50, 50, 50, 49, TankPic[0][i]);             //拷贝上、下、左、右朝向tank
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(150 + (i + 1) * 50, 0, 50, 49, TankPic[1][i]);             //拷贝上、下、左、右朝向tank
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(0 + (i) * 50, 0, 50, 49, TankPic[2][i]);             //拷贝上、下、左、右朝向tank
    }

    for (int i = 0; i < 4; i++)
    {
        ImageBuf.CopyImage(150 + (i + 1) * 50, 201, 50, 49, TankPic[3][i]);             //拷贝上、下、左、右朝向tank
    }

    for (int i = 0; i <= 5; i++)
    {
        ImageBuf.CopyImage(50 + i * 50, 150, 50, 50, BoomPic[i]);                       //for boom
    }

    for (int i = 0; i < 2; i++)
    {
        ImageBuf.CopyImage(i * 15, 150, 15, 15, BulletPic[i]);             //拷贝上、下、左、右朝向tank
    }

    ImageBuf.CopyImage(0, 100, 50, 50, HomeBase);             //拷贝上、下、左、右朝向tank


                                                              //初始化当前的数据
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            m_mapData[i][j] = g_mapData[i][j];
        }
    }

    //xy为坦克左下角在地图中的坐标
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

    //坐标系原点(0,0) 为左下角，x竖直向上，y水平向右
    //开始绘制坦克

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

//CurX,CurY 坦克的左下角 在地图坐标系（原点(0,0)）中的位置

//绘图坐标系原点(0,0) 为左下角，x竖直向上，y水平向右
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

//除了玩家，都自动运行
int CMyView::AllRun()
{
    TONode *p = &tList;

    while (p->Obj != nullptr)
    {
        if (p->Obj->m_nID != 0)
        {
            p->Obj->SetRotate(0);
            //开枪
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

//检查对象碰撞
int CMyView::CheckObj(TankWarObj *obj, TankWarObj *another)
{
    return obj->CheckObj(obj, another);
}

//干掉土墙或老爷
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
        std::cout << "老爷死了，结束\r\n";
        system("pause");
        exit(EXIT_SUCCESS);
    }
}

//单个对象自动运行
void CMyView::RunEach(TONode * p)
{
    TONode *another = &tList;

    //nFlag ==0 表示可以移动
    //nFlag ==1 表示不可以移动
    int nFlag = 0;
    int nChkWall = 0;

    //对象撞墙，死或不移动
    nChkWall = CheckWall(p->Obj);
    //返回1 表示坦克撞墙， 子弹撞土墙
    if (nChkWall == 1)
    {
        //是子弹,毁掉墙
        if (p->Obj->m_nID == 2 || p->Obj->m_nID == 3)
        {
            DestroyWallForObj(p->Obj);
            p = DelObj(&tList, p);
            return;
        }
    }
    //返回2 表示子弹出界， 撞铁
    else if (nChkWall == 2)
    {
        p = DelObj(&tList, p);
        return;
    }
    //没有撞墙
    else
    {
        another = &tList;
        while (another->Obj != nullptr)
        {

            if (p != another)
            {   //返回0，碰撞,死或不移动
                if (CheckObj(p->Obj, another->Obj) == 0)
                {
                    nFlag = 1;
                    //碰撞者中，有子弹，两个对象都死亡
                    //我坦0，敌坦1，我子弹2，敌子弹3
                    if ((p->Obj->m_nID | another->Obj->m_nID) != 1)
                    {
                        if (p->Obj->m_nID == 0 || another->Obj->m_nID == 0)
                        {
                            //玩家被打中。退出
                            std::cout << "玩家死了，结束\r\n";
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
        //标记为可移动
        if (nFlag == 0)
        {
            //没撞墙，没互撞
            //则移动
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

    //开火
    TONode *pB = (TONode*)malloc(sizeof(TONode));
    pB->Obj = new Bullet(x * 25, y * 25, obj->m_nRotate, obj->m_nID + 2);
    AddObj(&tList, pB);

}

//检查撞墙
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
        if ((buf[SrcTempPos + 3]) == 0)          //找出了边框为黑色的部分
        {
            memcpy(&buf[SrcTempPos], &Temp[TempPos], 3);         //显示背景色
        }
        SrcTempPos += 4;
        TempPos += PixelByte;
    }
    delete[]Temp;
}

//绘制基本元素， nType = 1 表示砖  2 铁 3 浅蓝方块 4 深蓝方块 5 草 
void CMyView::DrawElement(int x, int y, int nType)
{
    glRasterPos2i(x, y);      //为像素操作指定光栅位置  用25*i j  为了显示图像的不重叠
    MixPic(25, 25, 25, 25, MapPic[nType]);
    glDrawPixels(25, 25, GL_RGBA, GL_UNSIGNED_BYTE, MapPic[nType]);  //将一个像素块写入帧缓存  
}

void CMyView::DrawBg(int x, int y)
{
    //绘制矩形
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(x, y, x + 25.0f, y + 25.0f);
}

void CMyView::DrawBoom(int x, int y, int nType)
{

    glRasterPos2i(x, y);      //为像素操作指定光栅位置  用25*i j  为了显示图像的不重叠
    glDrawPixels(50, 50, GL_RGBA, GL_UNSIGNED_BYTE, BoomPic[nType]);  //将一个像素块写入帧缓存  
}

void CMyView::DrawTank(int x, int y, int nType, int nRotate)
{

    glRasterPos2i(x, y);      //为像素操作指定光栅位置  用25*i j  为了显示图像的不重叠
    glDrawPixels(50, 49, GL_RGBA, GL_UNSIGNED_BYTE, TankPic[nType][nRotate]);  //将一个像素块写入帧缓存  
}

void CMyView::DrawHomeBase(int x, int y)
{

    glRasterPos2i(x, y);      //为像素操作指定光栅位置  用25*i j  为了显示图像的不重叠				
    glDrawPixels(50, 50, GL_RGBA, GL_UNSIGNED_BYTE, HomeBase);  //将一个像素块写入帧缓存  

}

void CMyView::DrawBullet(int x, int y, int nType)
{

    glRasterPos2i(x, y);      //为像素操作指定光栅位置  用25*i j  为了显示图像的不重叠
    glDrawPixels(15, 15, GL_RGBA, GL_UNSIGNED_BYTE, BulletPic[nType]);  //将一个像素块写入帧缓存  
}

