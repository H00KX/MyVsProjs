#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtguiapplication1.h"
#include <qtreewidget.h>

class QtGuiApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtGuiApplication1(QWidget *parent = Q_NULLPTR);

    private slots:

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::QtGuiApplication1Class ui;
};
