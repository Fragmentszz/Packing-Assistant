#include"tabWindow.h"


QStringList header1 = { "编号","发往地点","长","宽","高","重量","数量"};
QStringList header2 = { "长","宽","高","总质量","体积利用率","质量利用率" };
tabWidget::tabWidget(QWidget* parent, int _where, int rowCount)
	:QWidget(parent),where(_where)
{
	goods = new MyTable(this);
	goods->setGeometry(0, 30, 1000, 400);
	goods->initTable(rowCount,header1.size(), _where, header1, "货物");

	title = new QLabel(this);
	title->setText("待装配货物：");
	title->setGeometry(0, 10, 101, 16);


    title2 = new QLabel(this);
    title2->setText("总体积利用率： 总质量利用率：");
    title2->hide();
    title2->setGeometry(0, 420, 1000,40);
    
    cartons = new CartonTable(this);
    //cartons->hide();
    cartons->setGeometry(0, 460, 1000, 390);
}


void tabWidget::addRow()
{
	goods->addRow(where);
}


void tabWidget::FF()
{
    pair<int, int> pair = goods->hasEmpty();
    if (pair.first != -1)
    {
        stringstream ss;
        ss << "第" << pair.first + 1 << "个货物的" << header1[pair.second].toStdString() << "未填！！" << endl;
        QMessageBox message(QMessageBox::Information, QString("货物表有空值未填！"), QString::fromStdString(stringFromSS(ss)), QMessageBox::Yes);
        int Ret = message.exec();
        return;
    }

    vector<Goods> inputGoods = (goods->getGoods())[where];
    Solve solve(where, inputGoods);
    Solution s = solve.getSolution();
    cartons->initFloat(s.num, header2.size(), header2, "箱子", s);
    stringstream ss;
    
    ss << "共"<<s.num << "个箱子," << "总体积利用率：" << s.totr_V*100 << "%, 总质量利用率：" << s.totr_W*100 << "%"<< endl;
    title2->setText(QString::fromStdString(stringFromSS(ss)));
    title2->show();
    s.plot("plot" + N2S(where).toStdString() + ".txt");
    ss.clear();
    ss << ("完全装箱方案已经导出到./docs/plot" + N2S(where).toStdString() + ".txt") << "文件中" << endl;
    QMessageBox message(QMessageBox::Information,  "装箱方案导出成功！", QString::fromStdString(stringFromSS(ss)), QMessageBox::Yes);
    message.button(QMessageBox::Yes)->setText("收到！");
    int Ret = message.exec();
}

void tabWidget::fillAll()
{
    goods->fillAll();
}
