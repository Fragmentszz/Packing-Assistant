#include"whereWidget.h"
whereWidget::whereWidget(QWidget* parent)
	:QDialog(parent),ui(new Ui::Form()),cindex(-1)
{
	ui->setupUi(this);
	connect(ui->pushButton, &QPushButton::clicked, this, &whereWidget::okButton);
}

void whereWidget::okButton()
{
	cindex = ui->comboBox->currentIndex();
	accept();
}

int whereWidget::getIndex() const
{
	return cindex;
}