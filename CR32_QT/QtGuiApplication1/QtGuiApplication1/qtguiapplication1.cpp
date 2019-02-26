#include "qtguiapplication1.h"
#include <windows.h>
#include <qdebug.h>

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //ui.treeWidget->expandAll();
}

void QtGuiApplication1::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH]=L"C:\\\*";
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;

    hFind = FindFirstFile(szDir, &ffd);
    int a = GetLastError();
    if (INVALID_HANDLE_VALUE == hFind)
        {
            //DisplayErrorBox(TEXT("FindFirstFile"));
            //return dwError;
        }

        // List all the files in the directory with some info about them.

        do
        {
            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                current->addChild(new QTreeWidgetItem(QStringList(QString::fromWCharArray(ffd.cFileName))));
                //_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);

            }
            else
            {
                filesize.LowPart = ffd.nFileSizeLow;
                filesize.HighPart = ffd.nFileSizeHigh;
                //_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
            }
        }
        while (FindNextFile(hFind, &ffd) != 0);

    qDebug() << "test" << endl;
}

void QtGuiApplication1::on_treeWidget_itemExpanded(QTreeWidgetItem *item)
{
    QTreeWidgetItem *it = new QTreeWidgetItem(ui.treeWidget);
    it->setText(0, "fdsa");
    //it->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *son = new QTreeWidgetItem(it);
    son->setText(0, "TTTTT");

    qDebug() << "test" << endl;
}

void QtGuiApplication1::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //QString  s=  item->text(0);
    //ui.treeWidget->expandAll();
    qDebug() << "test" << endl;
}
