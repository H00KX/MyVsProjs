#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtimer.h"
#include "qdebug.h"
//#include "WinUser.h"
#include "Windows.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hwnd = (HWND)ui->centralWidget->winId();
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    if (ui->tabWidget->currentIndex() != 2)
    {
        return;
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Test()));
    timer->start(1000);


    int a = event->globalPos().x();
    a = event->globalPos().y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() != Qt::LeftButton)
    {
        return;
    }

    //窗口查找标签页的序号
    if (ui->tabWidget->currentIndex() != 2)
    {
        return;
    }

    int a = event->globalPos().x();
    a = event->globalPos().y();

    if (timer->isActive())
    {
        timer->stop();
    }

    qDebug() << "end" << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Test()
{
    POINT  pt;

    GetCursorPos(&pt);

    HWND hwd = WindowFromPoint(pt);



    qDebug() << "test" << hwd << endl;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "click" << endl;
}
