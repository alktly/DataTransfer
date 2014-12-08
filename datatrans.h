#ifndef DATATRANS_H
#define DATATRANS_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QtCore>
#include <QtGui>
#include <QProgressBar>
#include <QLabel>
#include <QTableView>
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
    void on_browseSourcePushButton_clicked();
    void on_browseTargetPushButton_clicked();

private:
    Ui::DataTrans *ui;

    QString sourceDBFile, targetDBFile;

    QProgressBar *progressBar;
    QLabel *completed;
    QTableView *tableView;
    bool connectSQLitePolo();
    bool connectSQLiteFinTrans();
    bool select_dbTableNames();
    void setModel(MyModel *model);
    void setCheckBoxes();
    QString chooseSourceDB();
    QString chooseTargetDB();
};

#endif // DATATRANS_H
