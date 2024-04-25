#pragma once
#pragma once
#include <QtWidgets/QMainWindow>
#include"ui_add_Goods.h"
#include<QtWidgets/qdialog.h>
class add_Goods_dialog :
    public QDialog
{
    Q_OBJECT
public:
    add_Goods_dialog(QWidget* parent = nullptr);
    int getNum()const;
private:
    Ui::Dialog* ui;
    int addnum;
    
private slots:
    void okButton();
    
};
