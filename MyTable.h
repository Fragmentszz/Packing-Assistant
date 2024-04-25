#pragma once
#include"_basic.h"
#include <QtWidgets/QMainWindow>
#include"Cells.h"
#include"Algorithm.h"
#include <QClipboard>
#include <QApplication>
#include <QTableWidgetItem>
#include<QKeyEvent>
#include<QMenu>
#include<QHeaderView>
#include<QAbstractItemModel>
// “编号”、“发往地点”、“长”、“宽”、“ 高”、“重量”、“数量”


class QTapp2;
class tabWidget;


class Row
{
public:
    string No;
    int where;
    double d[5];
};

class MyTable :
	public QTableWidget
{
public:
    MyTable(QWidget* parent = nullptr);
    //~MyTable();
public:
    vector<vector<Goods>> getGoods() const;
    friend class QTapp2;
    friend class tabWidget;
    void initTable(int row, int column = 7,int where=-1, QStringList header=QStringList(), QString _header_v = "");
    void setRow(Row row, int i);
    void addRow(int where = -1);
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void deleteRow(int);
    QMenu* contextMenu;
    int where;
protected slots:
    void newProject();
    void fillAllBlank();
    void fillAll();
    virtual void bindtb(QTableWidgetItem* item);
    void addRow_r();
    QString header_v;
    //void addColumn();
    pair<int,int> hasEmpty() const;
    void copySelectedCells();
    void pasteSelectedCells();
    void setupContextMenu();
//signals:
//    void NoChanged(NoCell*);
//    void ComboChanged(ComboCell*);
//    void IntegerChanged(IntegerCell*);
//    void FloatChanged(FloatCell*);
};

class MyHeaderView2;
class CartonTable
    :public QTableWidget
{
public:
    CartonTable(QWidget* parent = nullptr);
    void initFloat(int row, int column, QStringList header_h, QString _header_v, Solution& s);
protected:
    QString header_v;
    void bindtb();
    Solution solution;
    void plot(int row);
    MyHeaderView2* vheader;
    friend class MyHeaderView2;
};


class MyHeaderView
    :public QHeaderView
{
public:
    MyHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);
    void contextMenuEvent(QContextMenuEvent* event) override;
};

class MyHeaderView2
    :public QHeaderView
{
public:
    MyHeaderView2(Qt::Orientation orientation, QWidget* parent = nullptr);
    void contextMenuEvent(QContextMenuEvent* event) override;
    
};