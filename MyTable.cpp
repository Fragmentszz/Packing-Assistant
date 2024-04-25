#include"MyTable.h"
string toLocation[5] = { "AU","US","UK","DE","JP" };

MyTable::MyTable(QWidget* parent)
    :QTableWidget(parent)
{
    connect(this, &QTableWidget::itemChanged, this, &MyTable::bindtb);
    setupContextMenu();
    
}

void MyTable::fillAllBlank()         //填充全部空白
{
    for (int i = 0; i < this->rowCount(); i++)
    {
        for (int j = 0; j < this->columnCount(); j++)
        {
            if (this->item(i, j) == nullptr || this->item(i,j)->text() == "")
            {
                int rd = randint(0, 100);
                this->setItem(i, j, new QTableWidgetItem(N2S(rd)));
            }
        }
    }
}

void MyTable::fillAll()          //填充全部
{
    
    for (int i = 0; i < this->rowCount(); i++)
    {
        QString str = NoCell::createNo(toLocation[where]);
        if (this->item(i, 0) == nullptr)
            this->setItem(i, 0, new NoCell(str,where));
        else this->item(i, 0)->setText(str);
        for (int j = 2; j < this->columnCount()-2; j++)
        {
            double rd = 1.0*rand() / RAND_MAX*60;
            if (this->item(i, j) == nullptr)
                this->setItem(i, j, new FloatCell(F2S(rd)));
            else this->item(i, j)->setText(F2S(rd));
        }
        double rdw = 1.0 * rand() / RAND_MAX * 3;
        if (this->item(i, 5) == nullptr)
            this->setItem(i, 6, new IntegerCell(F2S(rdw)));
        else this->item(i, 5)->setText(F2S(rdw));
        int rd = randint(1, 10);
        if (this->item(i, 6) == nullptr)
            this->setItem(i, 6, new IntegerCell(N2S(rd)));
        else this->item(i, 6)->setText(N2S(rd));
    }
}
bool flag = 0;
void MyTable::bindtb(QTableWidgetItem* item)
{
    
    int i = item->row(), j = item->column();
    if (j == 0)
    {
        
        NoCell* noitem = (NoCell*)(void*)item;
        if (noitem->getNo() != item->text().toStdString() || item->text().length() == 0)
        {
            noitem->setNo(item->text());
            // cout << noitem->getNo() << endl;
        }
    }
    else if (j == 1)
    {
        ComboCell* comitem = (ComboCell*)(void*)item;
        // cout << comitem << endl;
    }
    else if (j == 6)
    {
        IntegerCell* integeritem = (IntegerCell*)(void*)item;
        if (fabs(integeritem->getNum() - S2N(item->text())) > 1e-8 || item->text().length() == 0) {
            integeritem->setNum(item->text());
        }
    }
    else
    {
        FloatCell* floatitem = (FloatCell*)(void*)item;
        if (fabs((double)floatitem->getNum() - S2F(item->text())) > 1e-8 || item->text().length() == 0) {
            floatitem->setNum(item->text());
        }
    }

}


void MyTable::initTable(int row,int column,int _where,QStringList header_h,QString _header_v)
{
    header_v = _header_v;
    this->clearContents();
    where = _where;
    this->setRowCount(row);
    this->setColumnCount(column);
    this->setHorizontalHeaderLabels(header_h);

    //this->setColumnWidth(7, 20);
    this->setVerticalHeader(new MyHeaderView(Qt::Vertical, this));
    for (int i = 0; i < row; i++) {
        this->setItem(i, 0, new NoCell("",where));
        this->setCellWidget(i, 1, new ToCell(nullptr,where));
        this->setItem(i, 6, new IntegerCell());
        for (int j = 2; j < 6; j++) {
            this->setItem(i, j, new FloatCell());
        }
        //QTableWidgetItem* cb = new QTableWidgetItem();
        //cb->setCheckState(Qt::Checked);
        //this->setItem(i, 7, cb);
        //cout << cb->isChecked() << endl;
        QString s = header_v;
        s.append(N2S(i + 1));
        auto tmpItem = new QTableWidgetItem(s);
        this->setVerticalHeaderItem(i, tmpItem);

    }

}
void MyTable::setRow(Row row,int i)
{
    if (i >= this->rowCount())   return;
	this->setItem(i, 0, new NoCell(QString::fromStdString(row.No),where));
	this->setCellWidget(i, 1, new ToCell(nullptr,row.where));
	this->setItem(i, 6, new IntegerCell(row.d[4]));
	this->setItem(i, 2, new FloatCell(row.d[0]));
	this->setItem(i, 3, new FloatCell(row.d[1]));
	this->setItem(i, 4, new FloatCell(row.d[2]));
	this->setItem(i, 5, new FloatCell(row.d[3]));
	QString s = header_v;
	s.append(N2S(i + 1));
	auto tmpItem = new QTableWidgetItem(s);
	this->setVerticalHeaderItem(i, tmpItem);
}


//void MyTable::initTable(int row)
//{
//    this->clearContents();
//
//    this->setRowCount(row);
//    this->setColumnCount(7);
//    this->setHorizontalHeaderLabels(header1);
//
//
//    
//    for (int i = 0; i < row; i++) {
//        this->setItem(i, 0, new NoCell());
//        this->setCellWidget(i, 1, new ToCell());
//        this->setItem(i, 6, new IntegerCell());
//        for (int j = 2; j < 6; j++) {
//            this->setItem(i, j, new FloatCell());
//        }
//        QString s = "货物";
//        s.append(N2S(i+1));
//        auto tmpItem = new QTableWidgetItem(s);
//        this->setVerticalHeaderItem(i, tmpItem);
//    }
//    
//}

vector<vector<Goods>> MyTable::getGoods() const
{
    vector<vector<Goods>> ans;
    ans.resize(5);
    for (int i = 0; i < this->rowCount(); i++)
    {
        string identifier = ((NoCell*)(void*)(this->item(i, 0)))->getNo();
        int id = ((ToCell*)(void*)(this->cellWidget(i, 1)))->getIndex();
        double l = ((FloatCell*)(void*)(this->item(i,2)))->getNum(),w = ((FloatCell*)(void*)(this->item(i, 3)))->getNum(), h = ((FloatCell*)(void*)(this->item(i, 4)))->getNum();
        double weight = ((FloatCell*)(void*)(this->item(i, 5)))->getNum();
        int k = ((IntegerCell*)(void*)(this->item(i, 6)))->getNum();
        for (int j = 0; j < k; j++)
        {
            ans[id].push_back(Goods(identifier, { 0,0,0 }, { l, w, h }, weight));
            // ans[id].back().print();
        }
    }
    return ans;
}


void MyTable::addRow(int where)
{
    
    int nowrow = this->rowCount();
    this->setRowCount(nowrow + 1);
    this->setItem(nowrow, 0, new NoCell("",where));
    this->setCellWidget(nowrow, 1, new ToCell(nullptr,where));
    this->setItem(nowrow, 6, new IntegerCell());
    for (int j = 2; j < 6; j++) {
        this->setItem(nowrow, j, new FloatCell());
    }
 /*   QTableWidgetItem* cb = new QTableWidgetItem();
    cb->setCheckState(Qt::Checked);
    this->setItem(nowrow, 7, cb);*/
    nowrow++;
    QString s = header_v;
    s.append(N2S(nowrow));
    
    auto tmpItem = new QTableWidgetItem(s);
    this->setVerticalHeaderItem(nowrow - 1, tmpItem);
    
}

void MyTable::keyPressEvent(QKeyEvent* event)
{
    if (event->matches(QKeySequence::Copy)) {
        copySelectedCells();
    }
    else if(event->matches(QKeySequence::Paste)) {
        pasteSelectedCells();
    }
    else {
        QTableWidget::keyPressEvent(event);
    }
}

void MyTable::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (index.row() == -1) { 
            int rowToBeDeleted = index.row();
            contextMenu->exec(event->globalPos());
        }
    }
    else {
        QTableWidget::mousePressEvent(event);
    }
}






void MyTable::addRow_r()
{
    addRow();
    int nowrow = this->rowCount();
    for (int j = 0; j < this->columnCount(); j++)
    {
        int rd = randint(0, 100);
        this->setItem(nowrow-1, j, new QTableWidgetItem(N2S(rd)));
    }
}
int cnt = 0;



pair<int,int> MyTable::hasEmpty()    const
{
    for (int i = 0; i < this->rowCount(); i++)
    {
        for (int j = 0; j < this->columnCount(); j++)
        {
            if (j == 1)  continue;
            if (this->item(i, j) == nullptr)
            {
                return { i,j };
            }
            else if (this->item(i, j)->text() == "")
            {
                return { i,j };
            }
        }
    }
    return { -1,-1 };
}

void MyTable::copySelectedCells()
{
    QList<QTableWidgetItem*> selectedItems = this->selectedItems();
    if (selectedItems.isEmpty()) {
        return;
    }

    // 构造 CSV 数据
    QString csvData;
    for (QTableWidgetItem* item : selectedItems) {
        csvData.append(item->text());
        csvData.append(",");
    }
    csvData.chop(1); // 移除最后一个逗号

    // 将数据复制到剪贴板
    QApplication::clipboard()->setText(csvData);
}

void MyTable::pasteSelectedCells()
{
    QString csvData = QApplication::clipboard()->text();
	QStringList rows = csvData.split("\n",Qt::SkipEmptyParts);
    if (rows.isEmpty()) {
		return;
	}

	int row = this->currentRow();
	int column = this->currentColumn();
    for (int i = 0; i < rows.size(); i++) {
		QStringList columns = rows[i].split(",", Qt::SkipEmptyParts);
        for (int j = 0; j < columns.size(); j++) {
            if (row + i < this->rowCount() && column + j < this->columnCount()) {
				this->setItem(row + i, column + j, new QTableWidgetItem(columns[j]));
			}
		}
	}
}

void MyTable::deleteRow(int rowToBeDeleted)
{
    if (rowToBeDeleted < 0 || rowToBeDeleted >= this->rowCount()) {
		return;
	}

	this->removeRow(rowToBeDeleted);
    for (int i = rowToBeDeleted; i < this->rowCount(); i++) {
		QString s = header_v;
		s.append(N2S(i + 1));
		auto tmpItem = new QTableWidgetItem(s);
		this->setVerticalHeaderItem(i, tmpItem);
	}
}

void MyTable::setupContextMenu()
{
    contextMenu = new QMenu(this);
    //QAction* addRowAction = contextMenu->addAction("添加货物");
    //QAction* fillAllAction = contextMenu->addAction("填充全部");
    //QAction* FFAction = contextMenu->addAction("FF");
}



//MyTable::~MyTable()
//{
//
//}

CartonTable::CartonTable(QWidget* parent)
    :QTableWidget(parent)
{
    vheader = new MyHeaderView2(Qt::Vertical, this);
    this->setVerticalHeader(vheader);
}

void CartonTable::initFloat(int row, int column, QStringList header_h, QString _header_v, Solution& s)
{
    solution = s;
    vector<vector<double>> sj;
    for (int i = 0; i < s.s_cartons.size(); i++)
    {
        sj.push_back({ s.s_cartons[i].shape.length,s.s_cartons[i].shape.width,s.s_cartons[i].shape.height,s.s_cartons[i].weight,s.s_cartons[i].rate_v,s.s_cartons[i].rate_w });
    }
    header_v = _header_v;
    this->clearContents();

    this->setRowCount(row);
    this->setColumnCount(column);
    this->setHorizontalHeaderLabels(header_h);
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column-2; j++)
        {
            this->setItem(i, j, new FloatCell(sj[i][j]));
        }
        this->setItem(i, column - 2, new QTableWidgetItem(F2Percentage(sj[i][column - 2], 2)));
        this->setItem(i, column - 1, new QTableWidgetItem(F2Percentage(sj[i][column - 1], 2))); 
        QString s = header_v;
        s.append(N2S(i + 1));
        auto tmpItem = new QTableWidgetItem(s);
        this->setVerticalHeaderItem(i, tmpItem);
    }
}

void CartonTable::bindtb()
{

}

void CartonTable::plot(int i)
{
    solution.plot("/subplot/plot" + N2S(i).toStdString() + ".txt", i);
}

MyHeaderView::MyHeaderView(Qt::Orientation orientation, QWidget* parent)
    :QHeaderView(orientation, parent)
{
    
}

void MyHeaderView::contextMenuEvent(QContextMenuEvent* event)
{
    // 获取点击的行索引
    int row = logicalIndexAt(event->pos().y());
    // 创建上下文菜单
    QMenu menu(this);
    
    // 添加菜单项
    QAction* deleteAction = menu.addAction("删除行");
    // ... 可以添加更多的菜单项

    MyTable* parentTable = (MyTable*)(void*)this->parent();
    parentTable->selectRow(row);

    // 连接菜单项的槽函数
    connect(deleteAction, &QAction::triggered,this,(
        [=]() {
            parentTable->deleteRow(row);
        }));
    // 在鼠标点击位置显示菜单
    menu.exec(event->globalPos());
}

MyHeaderView2::MyHeaderView2(Qt::Orientation orientation, QWidget* parent)
    :QHeaderView(orientation, parent)
{

}

void MyHeaderView2::contextMenuEvent(QContextMenuEvent* event)
{
    // 获取点击的行索引
    int row = logicalIndexAt(event->pos().y());
    // 创建上下文菜单
    QMenu menu(this);
    // 添加菜单项
    QAction* showAction = menu.addAction("显示三维方案");
    // ... 可以添加更多的菜单项

    CartonTable* parentTable = (CartonTable*)(void*)this->parent();
    parentTable->selectRow(row);

    // 连接菜单项的槽函数
    connect(showAction, &QAction::triggered, this, (
        [=]() {
            parentTable->plot(row);
        }));
    // 在鼠标点击位置显示菜单
    menu.exec(event->globalPos());
}
