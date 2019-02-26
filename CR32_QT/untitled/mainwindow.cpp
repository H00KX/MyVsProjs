#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <TlHelp32.h>
#include <string.h>
#include <Qdir>
#include <QListWidget>
#include <QFile>
#include <QFileIconProvider>
#include <QMouseEvent>

#pragma comment(lib,"Advapi32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"Gdi32.lib")
Ui::MainWindow *Tui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TCHAR buf[100];
    DWORD len = GetLogicalDriveStrings(sizeof(buf) / sizeof(TCHAR), buf);
    std::string strDisks;

    for (TCHAR * s = buf; *s; s += wcslen(s) + 1)
    {
        char nchar[256] = { 0 };
        WideCharToMultiByte(CP_ACP, 0, s, -1, nchar, 256, NULL, NULL);
        ui->comboBox->addItem(nchar);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//遍历目录
void updateFile(QString path, Ui::MainWindow *ui)
{
    ui->lineEdit->setText(path);
    QDir dir(path);
    QFileInfo mfi;
    QFileInfoList list = dir.entryInfoList();
    if (list.size() > 0)
    {

        ui->listWidget->clear();
    }

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QFileIconProvider icon_provider;
        QIcon icon = icon_provider.icon(fileInfo);

        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon(icon);
        item->setText(fileInfo.absoluteFilePath());

        ui->listWidget->addItem(item);

    }
}

bool EnumProcess(Ui::MainWindow *ui)
{
    HANDLE hProcessSnap;
        HANDLE hProcess;
        PROCESSENTRY32 pe32;
        DWORD dwPriorityClass;

        // Take a snapshot of all processes in the system.
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            return(FALSE);
        }

        // Set the size of the structure before using it.
        pe32.dwSize = sizeof(PROCESSENTRY32);

        // Retrieve information about the first process,
        // and exit if unsuccessful
        if (!Process32First(hProcessSnap, &pe32))
        {
            CloseHandle(hProcessSnap);          // clean the snapshot object
            return(FALSE);
        }
        ui->tableWidget->setRowCount(0);

        // Now walk the snapshot of processes, and
        // display information about each process in turn
        do
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            QTableWidgetItem *item2 = new QTableWidgetItem();
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            item->setText(QString::fromWCharArray(pe32.szExeFile));
            item2->setText(QString::number(pe32.th32ProcessID));

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,item);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,item2);
            ui->tableWidget->setColumnWidth(0,80);
            ui->tableWidget->setColumnWidth(1,300);
        }
        while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
        return(TRUE);
}

BOOL ListProcessThreads(Ui::MainWindow *ui){
    QTableWidgetItem *item = ui->tableWidget->currentItem();
        DWORD id = item->text().toInt();

        HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (hSnapShot == INVALID_HANDLE_VALUE)
        {
            return false;
        }
        BOOL bRet = FALSE;
        THREADENTRY32  pe32;
        pe32.dwSize = sizeof(THREADENTRY32);
        if (Thread32First(hSnapShot, &pe32))
        {
            ui->tableWidget->setRowCount(0);
            do
            {
                if (pe32.th32OwnerProcessID == id)
                {

                    QTableWidgetItem *item = new QTableWidgetItem();

                    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                    item->setText(QString("%1").arg(pe32.th32ThreadID));
                    //设置表格内容-进程名字
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item);
                    //设置第一项宽度
                    ui->tableWidget->setColumnWidth(0, 250);
                }

            }
            while (Thread32Next(hSnapShot, &pe32));

            bRet = TRUE;
        }
        else
        {
            int err = GetLastError();
            bRet = FALSE;
        }

        CloseHandle(hSnapShot);
        return (bRet);

}

BOOL ListProcessModules(Ui::MainWindow *ui)
{
    QTableWidgetItem *item = ui->tableWidget->currentItem();
        QString str(item->text());
        DWORD id = str.toULong();

        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);
        int a = GetLastError();
        if (hSnap == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        BOOL bRet = FALSE;
        MODULEENTRY32  pe32;
        pe32.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnap, &pe32))
        {
            //清空所有行
            ui->tableWidget->setRowCount(0);
            //增加新内容
            do
            {
                //申请项对象
                QTableWidgetItem *item = new QTableWidgetItem();
                //插入一行
                
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                //获取进程名字
                std::wstring strName = pe32.szModule;
                QString str = QString::fromStdWString(strName);
                //设置项内容-进程名字
                item->setText(str);
                //设置表格内容-进程名字
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item);
                //设置第一项宽度
                ui->tableWidget->setColumnWidth(0, 250);

                OutputDebugString(pe32.szModule);
                OutputDebugStringA("\r\n");

            }
            while (Module32Next(hSnap, &pe32));

            bRet = TRUE;
        }
        else
        {
            int err = GetLastError();
            bRet = FALSE;
        }

        CloseHandle(hSnap);
        return (bRet);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    updateFile(ui->comboBox->currentText(), ui);
}

//刷新文件
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    updateFile(item->text(), ui);
}

//刷新进程
void MainWindow::on_pushButton_clicked()
{
    EnumProcess(ui);
}

//线程
void MainWindow::on_pushButton_2_clicked()
{
    ListProcessThreads(ui);
}

//模块
void MainWindow::on_pushButton_3_clicked()
{
     ListProcessModules(ui);
}


void EnumServices(Ui::MainWindow *ui)
{

    TCHAR szDisplayName[256] = { 0 };
    TCHAR szServiceName[256] = { 0 };
    DWORD pcbBytesNeeded = 0;           // buffer size needed
    DWORD lpServicesReturned = 0;       // number of entries returned
    DWORD lpResumeHandle = 0;           // next entry


    //需要管理员权限
    SC_HANDLE schSCManager = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
    if (schSCManager == 0)
    {
        return;
    }

    ENUM_SERVICE_STATUS ServiceStatus;
    ServiceStatus.lpDisplayName = (LPWSTR)szDisplayName;
    ServiceStatus.lpServiceName = (LPWSTR)szServiceName;
    BOOL bRet = FALSE;

    pcbBytesNeeded = 0;
    lpServicesReturned = 0;

    bRet = EnumServicesStatus(schSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, &ServiceStatus, 0, &pcbBytesNeeded, &lpServicesReturned, &lpResumeHandle);

    ENUM_SERVICE_STATUS* pAry = nullptr;
    ENUM_SERVICE_STATUS* pAryOrg = nullptr;


    if (bRet == 0 && GetLastError() == ERROR_MORE_DATA)
    {
        pAry = (ENUM_SERVICE_STATUS*)new char[pcbBytesNeeded];
        pAryOrg = pAry;
    }

    ui->tableWidget_2->setRowCount(0);

    bRet = EnumServicesStatus(schSCManager, SERVICE_WIN32, SERVICE_STATE_ALL, pAry, pcbBytesNeeded, &pcbBytesNeeded, &lpServicesReturned, &lpResumeHandle);

    for (DWORD i = 0; i < lpServicesReturned; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
        QTableWidgetItem *item3 = new QTableWidgetItem();

        ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());

        item->setText(QString::fromWCharArray(pAry->lpServiceName));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 0, item);
        ui->tableWidget_2->setColumnWidth(0, 250);

        item2->setText(QString::fromWCharArray(pAry->lpDisplayName));
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 1, item2);
        ui->tableWidget_2->setColumnWidth(1, 250);

        QString str3;
        switch (pAry->ServiceStatus.dwCurrentState)
        {
            case SERVICE_RUNNING:
                str3 = "运行";
                break;
            case SERVICE_STOPPED:
                str3 = "停止";
                break;
            default:
                str3 = "其他";
                break;
        }

        item3->setText(str3);
        ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 2, item3);
        ui->tableWidget_2->setColumnWidth(2, 100);
        pAry++;
    }

    delete[] pAryOrg;
}

//刷新服务

void MainWindow::on_pushButton_4_clicked()
{
    EnumServices(ui);
}

//启动
void MainWindow::on_pushButton_6_clicked()
{
    QTableWidgetItem *item = ui->tableWidget_2->currentItem();
        SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (hSc)
        {
            SC_HANDLE hService = OpenService(hSc, item->text().toStdWString().c_str(), SERVICE_ALL_ACCESS);
            if (hService)
            {
                if (StartServiceW(hService, 0, NULL))
                    return;
                CloseServiceHandle(hService);
            }
            CloseServiceHandle(hSc);
        }
}

//停止
void MainWindow::on_pushButton_5_clicked()
{
    QTableWidgetItem *item = ui->tableWidget_2->currentItem();

        SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (hSc)
        {
            SC_HANDLE hService = OpenService(hSc,  item->text().toStdWString().c_str(), SERVICE_ALL_ACCESS);
            if (hService)
            {
                SERVICE_STATUS status;
                if (ControlService(hService, SERVICE_CONTROL_STOP, &status))
                        return;
                CloseServiceHandle(hService);
            }
            CloseServiceHandle(hSc);
        }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    ui->lineEdit_2->setText("");

        HKEY Myhkey;
        if (ui->comboBox_2->currentText() == "HKEY_CLASSES_ROOT")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000000);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_CONFIG")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000005);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_USER")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000001);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_LOCAL_MACHINE")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000002);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_USERS")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000003);
        }
        else
        {
            return;
        }

        ui->listWidget_2->clear();


        HKEY hKey = NULL; //保存注册表的句柄
        DWORD dwIndexs = 0; //需要返回子项的索引
        TCHAR keyName[MAX_PATH] = { 0 }; //保存子键的名称
        DWORD charLength = 256;  //想要读取多少字节并返回实际读取到的字符长度


        if (RegOpenKeyEx(Myhkey, NULL, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
        {
            while (RegEnumKeyEx(hKey, dwIndexs, keyName, &charLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
            {
                QListWidgetItem *dropbox_item = new QListWidgetItem();
                dropbox_item->setText(QString::fromStdWString(keyName));
                ui->listWidget_2->addItem(dropbox_item);

                ++dwIndexs;
                charLength = 256;
            }
        }





        if (hKey != NULL)
        {
            RegCloseKey(hKey);
        }
}

void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{HKEY Myhkey;
    if (ui->comboBox_2->currentText() == "HKEY_CLASSES_ROOT")
    {
        Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000000);
    }
    else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_CONFIG")
    {
        Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000005);
    }
    else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_USER")
    {
        Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000001);
    }
    else if (ui->comboBox_2->currentText() == "HKEY_LOCAL_MACHINE")
    {
        Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000002);
    }
    else if (ui->comboBox_2->currentText() == "HKEY_USERS")
    {
        Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000003);
    }
    else
    {
        return;
    }


    HKEY hKey = NULL; //保存注册表的句柄
    DWORD dwIndexs = 0; //需要返回子项的索引
    TCHAR keyName[1024] = { 0 }; //保存子键的名称
    DWORD charLength = 256;  //想要读取多少字节并返回实际读取到的字符长度
    QString str;

    if (ui->lineEdit_2->text() == "")
    {
        str = item->text();
    }
    else
    {
        str = ui->lineEdit_2->text() + "\\\\" + item->text();
    }

    ui->lineEdit_2->setText(str);
    ui->listWidget_2->clear();

    if (RegOpenKeyExA(Myhkey, str.toLocal8Bit(), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        while (RegEnumKeyEx(hKey, dwIndexs, keyName, &charLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            QListWidgetItem *dropbox_item = new QListWidgetItem();
            dropbox_item->setText(QString::fromStdWString(keyName));
            ui->listWidget_2->addItem(dropbox_item);

            ++dwIndexs;
            charLength = sizeof(keyName);
        }
    }

    dwIndexs = 0;
    DWORD lpType = 0;
    wchar_t value[1024] = { 0 };
    DWORD dataSize;
    charLength = 256;
    keyName[0] = '\0';
    char keyValue[256];//键值数组
    QString valueMessage = "";//键值
    //清空所有行
    ui->tableWidget_3->setRowCount(0);


    while (::RegEnumValue(hKey, dwIndexs, keyName, &charLength, NULL, &lpType, (BYTE*)&keyValue, &dataSize) == 0)
    {

        //申请项对象
        QTableWidgetItem *item = new QTableWidgetItem();
        QTableWidgetItem *item2 = new QTableWidgetItem();
         QTableWidgetItem *item3 = new QTableWidgetItem();
         //插入一行
        ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());

        item->setText(QString::fromStdWString(keyName));

        if (lpType == REG_SZ)
        {
            item2->setText("REG_SZ");
        }
        else if (lpType == REG_DWORD)
        {
            item2->setText("REG_DWORD");

        }
        else if (lpType == REG_EXPAND_SZ)
        {
            item2->setText("REG_EXPAND_SZ");
        }

                valueMessage = "";
                //读取键值
                for(int j=0; j<dataSize; j++)
                {
                    if(keyValue[j] != 0x00)
                    {
                        valueMessage.append(keyValue[j]);
                    }
              }

               item3->setText(valueMessage);

        ui->tableWidget_3->setItem(ui->tableWidget_3->rowCount() - 1, 0, item);
        ui->tableWidget_3->setItem(ui->tableWidget_3->rowCount() - 1, 1, item2);
         ui->tableWidget_3->setItem(ui->tableWidget_3->rowCount() - 1, 2, item3);


        ui->tableWidget_3->setColumnWidth(0, 200);
        ui->tableWidget_3->setColumnWidth(1, 200);
         ui->tableWidget_3->setColumnWidth(2,100);

        ++dwIndexs;
        charLength = sizeof(keyName);
        dataSize = sizeof(value);
    }
    if (hKey != NULL)
    {
        RegCloseKey(hKey);
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    HKEY hKey = NULL; //保存注册表的句柄

        HKEY Myhkey;
        if (ui->comboBox_2->currentText() == "HKEY_CLASSES_ROOT")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000000);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_CONFIG")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000005);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_USER")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000001);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_LOCAL_MACHINE")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000002);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_USERS")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000003);
        }
        else
        {
            return;
        }

        QString str2(ui->lineEdit_2->text());

        if (RegOpenKeyA(Myhkey, (LPCSTR)str2.toLocal8Bit(), &hKey) == 0)
        {
            QString str(ui->lineEdit_3->text());
            RegSetValueExA(hKey, (LPCSTR)str.toLocal8Bit(), NULL, REG_SZ, NULL, NULL);

            int err = GetLastError();
        }
}

void MainWindow::on_pushButton_9_clicked()
{
    HKEY hKey = NULL; //保存注册表的句柄

        HKEY Myhkey;
        if (ui->comboBox_2->currentText() == "HKEY_CLASSES_ROOT")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000000);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_CONFIG")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000005);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_CURRENT_USER")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000001);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_LOCAL_MACHINE")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000002);
        }
        else if (ui->comboBox_2->currentText() == "HKEY_USERS")
        {
            Myhkey = (HKEY)(ULONG_PTR)((LONG)0x80000003);
        }
        else
        {
            return;
        }

        QString str2(ui->lineEdit_2->text());

        if (RegOpenKeyA(Myhkey, (LPCSTR)str2.toLocal8Bit(), &hKey) == 0)
        {
            QTableWidgetItem *item = ui->tableWidget_3->currentItem();
            QString str(item->text());
            RegDeleteValueA(hKey, (LPCSTR)str.toLocal8Bit());
        }
}


BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam)
{
    char title[100] = { 0 };
    GetWindowTextA(hwnd, title, 100);
    if (strlen(title) > 0)
    {
        QTreeWidgetItem* item = (QTreeWidgetItem*)lParam;

        //qDebug() << hwnd << "---" << title;
        // 在当前节点下添加子节点
        QTreeWidgetItem *item11 = new QTreeWidgetItem(item);

        CHAR szBuffer[256];
        sprintf(szBuffer, "0x%08p====%s", hwnd, title);
        QString strMessage = QString::fromLocal8Bit(szBuffer);

        item11->setText(0, strMessage);
    }
    return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char title[100] = { 0 };
    GetWindowTextA(hwnd, title, 100);

    QTreeWidgetItem* item = new QTreeWidgetItem();
    if (strlen(title) > 0)
    {

        CHAR szBuffer[256];
        sprintf(szBuffer, "0x%08p====%s", hwnd, title);
        QString strMessage = QString::fromLocal8Bit(szBuffer);
        item->setText(0, strMessage);
        Tui->treeWidget->addTopLevelItem(item);
    }
    EnumChildWindows(hwnd, EnumChildWindowsProc, (LPARAM)item);
    return true;
}

void MainWindow::on_pushButton_7_clicked()
{
        Tui = ui;

        EnumWindows(EnumWindowsProc, NULL);

        ui->treeWidget->expandAll(); //结点全部展开
}

HWND OldHwnd = NULL;

bool bSign = false;

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    bSign = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    //窗口查找标签页的序号
    if (ui->tabWidget->currentIndex() != 2)
    {
        return;
    }

    if (event->button() == Qt::LeftButton && bSign == true)
        {
            bSign = false;

            //画矩形
            HDC hdc;
            RECT rect;
            HPEN hPen;
            HBRUSH hBrush;

            GetWindowRect(OldHwnd, &rect);
            hdc = ::GetDC(GetDesktopWindow());//m_hWnd 是父类的成员变量,保存了窗口的句柄
            //设置系统色彩模式取反色
            ::SetROP2(hdc, R2_NOTXORPEN);

            // 创建画笔RGB(0x00, 0x00, 0xFF)
            hPen = ::CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0xFF));
            // 使用画笔
            ::SelectObject(hdc, hPen);

            //画刷
            hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
            ::SelectObject(hdc, hBrush);

            // 画矩形
            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
            ::ReleaseDC(OldHwnd, hdc);//释放申请的DC句柄,这里的申请与释放都是调用的SDK函数
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons()&Qt::LeftButton && bSign == true)
        {
            POINT pNow = { 0,0 };
            if (GetCursorPos(&pNow))  // 获取鼠标当前位置
            {
                HWND hwndPointNow = NULL;
                hwndPointNow = WindowFromPoint(pNow);  // 获取鼠标所在窗口的句柄

                if (hwndPointNow)
                {
                    int Tem = ui->lineEdit_4->text().toInt();
                    if (Tem != (int)hwndPointNow)
                    {

                        //界面
                        char szWindowTitle[256];
                        ::GetWindowTextA(hwndPointNow, szWindowTitle, sizeof(szWindowTitle));  // 获取窗口标题

                        CHAR szBuffer[256];
                        sprintf(szBuffer, "%d", hwndPointNow);
                        ui->lineEdit_4->setText(szBuffer);

                        ui->lineEdit_5->setText(QString::fromLocal8Bit(szWindowTitle));

                        ::GetClassNameA(hwndPointNow, szWindowTitle, sizeof(szWindowTitle));  // 获取窗口类名
                        ui->lineEdit_6->setText(szWindowTitle);

                        //画矩形
                        HDC hdc;
                        RECT rect;
                        HPEN hPen;
                        HBRUSH hBrush;

                        GetWindowRect(OldHwnd, &rect);
                        hdc = ::GetDC(GetDesktopWindow());//m_hWnd 是父类的成员变量,保存了窗口的句柄
                        //设置系统色彩模式取反色
                        ::SetROP2(hdc, R2_NOTXORPEN);

                        // 创建画笔RGB(0x00, 0x00, 0xFF)
                        hPen = ::CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0xFF));
                        // 使用画笔
                        ::SelectObject(hdc, hPen);

                        //画刷
                        hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                        ::SelectObject(hdc, hBrush);

                        // 画矩形
                        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
                        ::ReleaseDC(OldHwnd, hdc);//释放申请的DC句柄,这里的申请与释放都是调用的SDK函数


                        GetWindowRect(hwndPointNow, &rect);
                        hdc = ::GetDC(GetDesktopWindow());//m_hWnd 是父类的成员变量,保存了窗口的句柄
                        //设置系统色彩模式取反色
                        ::SetROP2(hdc, R2_NOTXORPEN);

                        // 创建画笔RGB(0x00, 0x00, 0xFF)
                        hPen = ::CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0xFF));
                        // 使用画笔
                        ::SelectObject(hdc, hPen);

                        //画刷
                        hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                        ::SelectObject(hdc, hBrush);

                        // 画矩形
                        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
                        ::ReleaseDC(hwndPointNow, hdc);//释放申请的DC句柄,这里的申请与释放都是调用的SDK函数
                        OldHwnd = hwndPointNow;
                    }

                }
            }
        }

}
