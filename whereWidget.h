#pragma once
#include <QtWidgets/QMainWindow>
#include"ui_whereWidget.h"
#include<QtWidgets/qdialog.h>
class whereWidget:
    public QDialog
{
    Q_OBJECT
public:
    whereWidget(QWidget* parent = nullptr);
    int getIndex() const;
private:
    Ui::Form* ui;
    int cindex;

private slots:
    void okButton();

};
