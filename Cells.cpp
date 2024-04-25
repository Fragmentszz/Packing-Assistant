#include"Cells.h"
const string maxlens = "changduhencahngaaa";

string Location[5] = { "AU","US","UK","DE","JP" };

StringCell::StringCell(string s)
	:QTableWidgetItem(QString::fromStdString(s))
{

}


QStringList ToCell::ToItems = {"澳洲","美国","英国","德国","日本"};
ComboCell::ComboCell(QWidget* parent, QStringList stringlist,int width,int height)
{
    combox = new QComboBox(this);
    combox->addItems(stringlist);
    if(height)  combox->setFixedHeight(height);
    if (width)   combox->setFixedWidth(width);
    QVBoxLayout* layout = new QVBoxLayout(this);
    //layout->addWidget(combox, 0, Qt::AlignCenter);	//居中
    this->setLayout(layout);
}

int ComboCell::getIndex() const
{
    return combox->currentIndex();
}

ToCell::ToCell(QWidget* parent, int where, int width, int height)
    :ComboCell(parent,ToItems,width,height)
{
    if (where >= 0)
    {
        this->combox->setCurrentIndex(where);
        this->setDisabled(true);
    }
    
}

NoCell::NoCell(QString _s,int _where)
{
    where = _where;
    this->setNo(_s);
    
}


void NoCell::setNo(QString _s)
{
    this->setBackground(QColor(255, 255, 255));
    if (_s.length() != 0)
    {
        s = _s.toStdString();
        for (int i = 0; i < Location[where].length(); i++)
        {
            if (i >= _s.length() || _s[i] != Location[where][i])
            {
                this->setBackground(QColor(200, 0, 0));
                QMessageBox::warning(nullptr, "输入错误!", "编号必须以" + QString::fromStdString(Location[where]) + "开头");
                return;
            }
        }
    }

    this->setText(_s);

}

string NoCell::getNo() const
{
    return s;
}

QString NoCell::createNo(string _where)
{
    int maxlens = randint(1, 1000000);
    if (_where == "AU")
    {
		return "AU-" + QString::number(1 + maxlens);
	}
    else if (_where == "US")
    {
		return "US-" + QString::number(1 + maxlens);
	}
    else if (_where == "UK")
    {
		return "UK-" + QString::number((1 + maxlens));
	}
    else if (_where == "DE")
    {
		return "DE-" + QString::number(1 + maxlens);
	}
    else if (_where == "JP")
    {
		return "JP-" + QString::number(1 + maxlens);
	}
    return QString();
}



IntegerCell::IntegerCell(QString s)
{
    this->setNum(s);
}

IntegerCell::IntegerCell(int _num)
{
    QString num = QString::number(_num);
	this->setText(num);
}

int IntegerCell::getNum() const
{
    return num;
}

void IntegerCell::setNum(QString s)
{
    if (s.length() == 0) {
        num = 0;
        return;
    }
    num = S2N(s);
    this->setBackground(QColor(255, 255, 255));
    if (num <= 0)
    {
        this->setText("");
        num = 0;
        // 发出警告
        QMessageBox::warning(nullptr, "输入错误!", "此处必须填写一个正整数值");
        this->setBackground(QColor(200, 0, 0));
    }
}




FloatCell::FloatCell(QString s)
{
    this->setNum(s);
}

FloatCell::FloatCell(float _a)
{
    QString num = F2S(_a, 2);
    this->setText(num);
}

float FloatCell::getNum() const
{
    return num;
}

void FloatCell::setNum(QString s)
{
    if (s.length() == 0) {
        num = 0;
        return;
    }
    num = S2F(s);

    this->setBackground(QColor(255, 255, 255));
    if (num <= 0)
    {
        this->setText("");
        num = 0;
        // 发出警告
        QMessageBox::warning(nullptr, "输入错误!", "此处必须填写一个正浮点数值");
        this->setBackground(QColor(200, 0, 0));
    }
    
}


void Cell::change()
{
    ;
}

