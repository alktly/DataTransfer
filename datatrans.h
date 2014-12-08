#ifndef DATATRANS_H
#define DATATRANS_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QtCore>
#include <QtGui>
#include <QProgressBar>
#include <QLabel>
#include "mymodel.h"

namespace Ui {
class DataTrans;
}

class DataTrans : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataTrans(QWidget *parent = 0);
    ~DataTrans();

    QSortFilterProxyModel *proxy;

private slots:
    void on_filterLineEdit_textChanged(const QString &arg1);
    void on_selectAllCheckBox_clicked(bool checked);

private:
    Ui::DataTrans *ui;

    QProgressBar *progressBar;
    QLabel *completed;
    bool connectSQLitePolo();
    bool connectSQLiteFinTrans();
    bool select_dbTableNames();
    void setModel(MyModel *model);
};

#endif // DATATRANS_H
