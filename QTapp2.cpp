#include "QTapp2.h"
#include<libxl.h>

QTapp2::QTapp2(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::QTapp2Class())
{
    ui->setupUi(this);
    
    connect(ui->newProject, &QAction::triggered, this, &QTapp2::newProject);
    connect(ui->add_Goods, &QAction::triggered, this, &QTapp2::add_Goods);
    connect(ui->FirstFit, &QAction::triggered, this, &QTapp2::FF);
    connect(ui->fillAll, &QAction::triggered, this, &QTapp2::fillTab);
    connect(ui->fromExcel, &QAction::triggered, this, &QTapp2::fromExcel);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    tabs.resize(ToCell::ToItems.size(), 0);
    connect(ui->help, &QAction::triggered, this, &QTapp2::Help);
    helpw = new QWidget(nullptr);
    helpw->setWindowTitle("帮助文档");
    helpw->hide();

    QWebEngineView* helpPage = new QWebEngineView(helpw);
    helpw->setGeometry(100, 100, 1080, 720);
    helpPage->setGeometry(0, 0, 1080, 720);
    helpPage->load(QString("file:///./docs/help.html"));
}

void QTapp2::newProject()
{
    whereWidget* w = new whereWidget(this);
    if (w->exec() == QDialog::Accepted)
    {
        int cindex = w->getIndex();
        tabWidget* newtab = new tabWidget(nullptr, cindex);
        tabs[cindex]++;
        ui->tabWidget->addTab(newtab,ToCell::ToItems[cindex] + "_" + N2S(tabs[cindex]));
    }
}
void QTapp2::Help()
{
    helpw->show();
}

QTapp2::~QTapp2()
{
    
}

void QTapp2::add_Goods()
{
    add_Goods_dialog* w = new add_Goods_dialog(this);
    if (w->exec() == QDialog::Accepted)
    {
        int addnum = w->getNum();
        tabWidget* tab = (tabWidget*)(void *)ui->tabWidget->currentWidget();
        for (int i = 0; i < addnum; i++)
        {
            tab->addRow();
        }
        stringstream ss;
        ss << "生成了" << addnum << "个货物" << endl;
        QMessageBox message(QMessageBox::Information, QString("货物添加成功"), QString::fromStdString(stringFromSS(ss)), QMessageBox::Yes);
        int Ret = message.exec();
    }
}

void QTapp2::FF()
{
    tabWidget* tab = (tabWidget*)(void*)ui->tabWidget->currentWidget();
    tab->FF();
}

void QTapp2::fillTab()
{
    tabWidget* tab = (tabWidget*)(void*)ui->tabWidget->currentWidget();
    tab->fillAll();
}

map<string, int> Location2ID = {
    {"au",0},{"us",1},{"uk",2}, {"de",3},{"jp",4}
};

void QTapp2::fromExcel()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "选择excel文件",
        "./",
        "excel files(*.xlsx *.xls)");

    wchar_t str[1000] = { 0 };
    using namespace libxl;
    Book* book = xlCreateXMLBookW();
    book->setKey(libxl_cracked_name, libxl_cracked_key);
    int len = filename.toWCharArray(str);
    cout << filename.toStdString() << endl;
    if (book)
    {
        book->load(str);
        if (book)
        {
            int sheetcount = book->sheetCount();
            for (int i = 0; i < sheetcount; i++)
            {
                const wchar_t* ss = book->getSheetName(i);
                string location = wstring2string(wstring(ss));
                if (Location2ID.find(location) == Location2ID.end())
                {
                    stringstream ss;
                    ss << "名为" << location << "的Sheet无效！\n不是有效的目的地！" << endl;
                    QMessageBox message(QMessageBox::Information, QString("Sheet") + N2S(i) + "导入失败", QString::fromStdString(stringFromSS(ss)), QMessageBox::Yes);
                    message.button(QMessageBox::Yes)->setText("确认");
                    int Ret = message.exec();
                    continue;
                }
                Sheet* sheet = book->getSheet(i);
                if (sheet)
                {
                    int n = sheet->lastRow(), m = sheet->lastCol();
                    if (n < 2)   continue;
                    auto newtabWidget = new tabWidget(nullptr, Location2ID[location],n-1);
                    tabs[Location2ID[location]]++;
                    ui->tabWidget->addTab(newtabWidget, ToCell::ToItems[Location2ID[location]] + "_" + N2S(tabs[Location2ID[location]]));
                    MyTable* table = newtabWidget->goods;
                    Row r;
                    for (int i = sheet->firstRow() + 1; i < n; i++)
                    {
                        for (int j = sheet->firstCol(); j < m; j++)
                        {
                            if (j == 0) {
                                wstring location = wstring(sheet->readStr(i, j));
                                string l = wstring2string(location);
                                r.No = l;
                            }
                            else if (j == 1) {
                                wstring lw = wstring(sheet->readStr(i, j));
                                string l = wstring2string(lw);
                                r.where = Location2ID[location];
                            }
                            else {
                                r.d[j- 2] = sheet->readNum(i, j);
                            }
                        }
                        table->setRow(r, i - 1);
                    }
                    stringstream ss;
                    ss << "打包往" << location << "的货物导入成功！" << endl << "共包含" << n - 1 << "个货物" << endl;
                    QMessageBox message(QMessageBox::Information, QString("Sheet") + N2S(i) + "导入成功！", QString::fromStdString(stringFromSS(ss)), QMessageBox::Yes);
                    message.button(QMessageBox::Yes)->setText("好耶！");
                    int Ret = message.exec();
                }
            }
            book->release();
        }
        else {
            cout << "没打开啊" << endl;
        }
    }

}

