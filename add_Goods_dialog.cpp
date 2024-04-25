#include "add_Goods_dialog.h"

add_Goods_dialog::add_Goods_dialog(QWidget* parent)
	:QDialog(parent),ui(new Ui::Dialog())
{
	ui->setupUi(this);
	addnum = 0;
	connect(ui->pushButton, &QPushButton::clicked, this, &add_Goods_dialog::okButton);
}

int add_Goods_dialog::getNum() const
{
	return this->addnum;
}


void add_Goods_dialog::okButton()
{
	this->addnum = ui->spinBox->value();
	accept();
}