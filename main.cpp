#include "datatransfer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataTransfer w;
    w.show();

    return a.exec();
}
