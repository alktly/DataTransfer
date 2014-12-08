#include "datatrans.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataTrans w;
    w.show();

    return a.exec();
}
