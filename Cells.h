#pragma once
#include"_basic.h"
using namespace std;



class Cell
{
public:
	virtual void change();
};


class CheckBoxItem : public QTableWidgetItem {
public:
	CheckBoxItem(bool checked = false) {
		setCheckState(checked ? Qt::Checked : Qt::Unchecked);
	}

	void setChecked(bool checked) {
		setCheckState(checked ? Qt::Checked : Qt::Unchecked);
	}

	bool isChecked() const {
		return checkState() == Qt::Checked;
	}

	Qt::ItemFlags flags() const {
		return Qt::ItemFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
	}
};

class ComboCell
	:public QWidget
{
public:
	ComboCell(QWidget* parent = nullptr, QStringList stringlist = {}, int width = 0, int height = 0);
	int getIndex() const;
protected:
	QComboBox* combox;
};

class ToCell
	:public ComboCell,Cell
{
public:
	ToCell(QWidget* parent = nullptr, int where = -1,int width = 0, int height = 0);
	static QStringList ToItems;
};

class StringCell
	:public QTableWidgetItem,Cell
{
public:
	StringCell(string s = "");
protected:
	string mys;
};

class NoCell
	:public QTableWidgetItem,Cell
{
public:
	NoCell(QString s = "",int _where=0);
	void setNo(QString s);
	string getNo() const;
	static QString createNo(string _where);
protected:
	int where;
	string s;
};

class IntegerCell
	:public QTableWidgetItem
{
public:
	IntegerCell(QString s = "");
	IntegerCell(int _num);
	int getNum() const;
	void setNum(QString s);
protected:
	int num;
};

class FloatCell
	:public QTableWidgetItem
{
public:
	FloatCell(QString s = "");
	FloatCell(float);
	float getNum() const;
	void setNum(QString s);
protected:
	float num;
};
