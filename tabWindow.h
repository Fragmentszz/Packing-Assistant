#include<qtabWidget>
#include<QMessageBox>
#include<QFileDialog>
#include"MyTable.h"
#include <QPushButton> // 这将包含 QAbstractButton 的子类 QPushButton

#include<QtWidgets/qdialog.h>


class QTapp2;
class tabWidget
	: public QWidget
{
public:
	tabWidget(QWidget* parent,int _where,int rowCount = 0);
	void addRow();
	void FF();
	void fillAll();
	friend class QTapp2;
private:
	MyTable* goods;
	CartonTable* cartons;
	QLabel* title,*title2;
	int where;
};