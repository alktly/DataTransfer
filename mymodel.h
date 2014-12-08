#ifndef MyModel_H
#define MyModel_H

#include <QAbstractTableModel>
#include "td/Color.h"

namespace db
{
    class Recordset;
}

class MyModel : public QAbstractTableModel
{

private:
    db::Recordset *_rs;
    bool _rsOK;
    bool _stripe;
    td::Color _backColor;
    Q_OBJECT

public:
    MyModel(QObject *parent, db::Recordset *rs, bool stripe = 0);
    ~MyModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setStripeColor(td::Color color);


};

#endif // MyModel_H
