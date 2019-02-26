#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~MainWindow();



private slots:

     void Test();
     void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    HWND hwnd;
    QTimer *timer;
};

#endif // MAINWINDOW_H
