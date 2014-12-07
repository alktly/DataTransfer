#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QMainWindow>

namespace Ui {
class DataTransfer;
}

class DataTransfer : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataTransfer(QWidget *parent = 0);
    ~DataTransfer();

private:
    Ui::DataTransfer *ui;
    bool connectSQLite();
};

#endif // DATATRANSFER_H
