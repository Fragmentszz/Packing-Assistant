#include "QTapp2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    float t1 = 12.35955666;
    float t2 = S2F("12A.f");
    float t3 = S2F(".11");
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;
    cout << (F2S(t1,3)).toStdString() << endl;
    cout << (F2Percentage(t1, 2)).toStdString() << endl;
    QApplication a(argc, argv);
    QTapp2 w;
    w.show();
    return a.exec();
}
