#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTapp2.h"
#include<QMessageBox>
#include"whereWidget.h"
#include"add_Goods_dialog.h"
#include<QWebEngineView>
#include"tabWindow.h"
#include<QFileDialog>

class QTapp2 : public QMainWindow
{
    Q_OBJECT

public:
    QTapp2(QWidget *parent = nullptr);
    ~QTapp2();
    
private:
    Ui::QTapp2Class* ui;
    vector<int> tabs;
    QWidget* helpw;
private slots:
    void newProject();
    void add_Goods();
    void FF();
    void fillTab();
    void fromExcel();
    void Help();
};
