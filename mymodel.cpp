#include "mymodel.h"
#include <iostream>
#include <QBrush>
#include <QTableView>
#include "db/Recordset.h"


MyModel::MyModel(QObject *parent, db::Recordset *rs, bool stripe)
    :QAbstractTableModel(parent)
    ,_rs(rs)
    ,_stripe(stripe)

{
    _backColor.setColor(203,233,242);
}

// mymodel.cpp
QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    switch(role)
    {
    case Qt::DisplayRole:
    {
            return QString::fromUtf8(_rs->getUTF8(row, col));
    }
        break;
    case Qt::TextAlignmentRole:
    {
        td::DataType colType = _rs->getColDesc()[col].tdType;

        if ((colType >= td::ch && colType <= td::nchFix) ||
                (colType >= td::date && colType <= td::dateTime))
            return Qt::AlignLeft + Qt::AlignVCenter;
        else
            return Qt::AlignRight + Qt::AlignVCenter;
    }
        break;
    case Qt::BackgroundRole:
    {
        if (_stripe && row % 2 == 1)
        {
            QBrush backColor( QColor::fromRgb(_backColor.blue(), _backColor.green(), _backColor.red()) ); // zamjena red i blue zbog td/Color Color klase
            return backColor;
        }
    }
        break;

    }
    return QVariant();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    return _rs->rowCount();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    return _rs->getColDesc().size();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return QString::fromUtf8(_rs->getColDesc()[section].name.c_str());

        if(orientation == Qt::Vertical)
            return QString::number( ++section ); // section starts from 0
    }
    return QVariant();
}

MyModel::~MyModel()
{
    if(_rs)
        delete _rs;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractTableModel::flags(index);
    if (index.isValid())
        theFlags |= Qt::ItemIsSelectable;
    return theFlags;
}

void MyModel::setStripeColor(td::Color color)
{
   _backColor = color;
}

