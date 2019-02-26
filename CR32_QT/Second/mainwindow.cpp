#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <TlHelp32.h>
#include <string.h>
#include <Qdir>
#include <QListWidget>
#include <QFile>
#include <QFileIconProvider>
#include "mydialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t = new CCDialog(this);
    t->show();
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

BOOL ListProcessModules(DWORD dwPID)
{
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        //printError(TEXT("CreateToolhelp32Snapshot (of modules)"));
        return(FALSE);
    }

    // Set the size of the structure before using it.
    me32.dwSize = sizeof(MODULEENTRY32);

    // Retrieve information about the first module,
    // and exit if unsuccessful
    if (!Module32First(hModuleSnap, &me32))
    {
        //printError(TEXT("Module32First"));  // show cause of failure
        CloseHandle(hModuleSnap);           // clean the snapshot object
        return(FALSE);
    }

    // Now walk the module list of the process,
    // and display information about each module
    do
    {
        QTableWidgetItem *item = new QTableWidgetItem();


    }
    while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return(TRUE);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    updateFile(ui->comboBox->currentText(), ui);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    updateFile(item->text(), ui);
}

void MainWindow::on_pushButton_clicked()
{
    EnumProcess(ui);
}

void MainWindow::on_pushButton_2_clicked()
{

}
