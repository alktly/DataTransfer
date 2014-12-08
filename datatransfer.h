#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "mymodel.h"

namespace Ui {
class DataTransfer;
}

class DataTransfer : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataTransfer(QWidget *parent = 0);
    ~DataTransfer();

    QSortFilterProxyModel *proxy;
    QString columnName;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_checkBox_clicked(bool checked);

private:
    Ui::DataTransfer *ui;
    bool connectSQLitePolo();
    bool connectSQLiteFinTrans();
    bool select_dbTableNames();
};

#endif // DATATRANSFER_H
