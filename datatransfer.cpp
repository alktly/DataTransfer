#include "datatransfer.h"
#include "ui_datatransfer.h"
#include "db/ISQLDataProvider.h"
#include "db/Recordset.h"
#include "td/Variant.h"
#include "mu/TxtOutFile.h"
#include "DebugTrace.h"
#include <QFileDialog>
#include <QtGui>
#include <QtCore>

db::ISQLDatabase *pDBPolo = 0;
db::ISQLDatabase *pDBFinTrans = 0;

DataTransfer::DataTransfer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataTransfer)
{
    ui->setupUi(this);

    proxy = new QSortFilterProxyModel(this);

    connectSQLitePolo();
    connectSQLiteFinTrans();

    select_dbTableNames();
}

DataTransfer::~DataTransfer()
{
    delete ui;
}

bool DataTransfer::connectSQLitePolo()
{
    if (pDBPolo){
        pDBPolo->release();
    }

    pDBPolo = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    //QString file = QFileDialog::getOpenFileName(this,"Open a database");
    //if(!file.isEmpty())

    //if (!pDB->connect(file.toUtf8().constData()))
    if (!pDBPolo->connect("C:/dbFiles/Polo.db"))
    {
        std::cout << "Cannot connect to database" << std::endl;
        td::String err;
        pDBPolo->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDBPolo->release();
        pDBPolo = 0;

        return false;
    }
    std::cout << "Connection OK! (POLO)" << std::endl;
    return true;
}

bool DataTransfer::connectSQLiteFinTrans()
{
    if (pDBFinTrans){
        pDBFinTrans->release();
    }

    pDBFinTrans = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    //QString file = QFileDialog::getOpenFileName(this,"Open a database");
    //if(!file.isEmpty())

    //if (!pDB->connect(file.toUtf8().constData()))
    if (!pDBFinTrans->connect("C:/dbFiles/FinTrans.db"))
    {
        std::cout << "Cannot connect to database" << std::endl;
        td::String err;
        pDBFinTrans->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDBFinTrans->release();
        pDBFinTrans = 0;

        return false;
    }
    std::cout << "Connection OK! (FinTrans)" << std::endl;
    return true;
}

bool DataTransfer::select_dbTableNames()
{
    if (!pDBPolo)
        return false;

    columnName = "table";
    td::String td_type = columnName.toUtf8();
    db::Ref<td::String> refType(32);
    refType = td_type;

    mem::PointerReleaser<db::IStatement> pStat(pDBPolo->createStatement(db::IStatement::DBS_SELECT, "SELECT name FROM sqlite_master WHERE type = ?"));

    //allocate parameters and bind them to the statement
    db::Params params(pStat->allocParams());

    //bind params
    params << refType;

    cnt::SafeFullVector<db::CPPColumnDesc> columns;

    columns.reserve(1);

    columns[0].name = "Name";
    columns[0].tdType = td::nch;
    columns[0].len = 32;

    db::Recordset* rs = new db::Recordset(columns);

    if (!rs->load(pStat.getPtr()))
        return false;

    // true for stripes
    MyModel *model = new MyModel(this, rs, false);

    proxy->setSourceModel(model);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(0);

    ui->tableView->setModel(proxy);
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    /*for(int p = 0; p < model->rowCount(); p++)
    {
        ui->tableView->setIndexWidget(model->index(p, 0),new QCheckBox());
    }*/

    return true;
}

void DataTransfer::on_lineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}

void DataTransfer::on_checkBox_clicked(bool checked)
{
    if(checked == true)
    {
        for(int i = 0; i < ui->tableView->model()->rowCount(); i++)
        {
            QModelIndex index = ui->tableView->model()->index(i, 0);
            ui->tableView->selectionModel()->select(index, QItemSelectionModel::Select);
        }
    }

    else
    {
        for(int i = 0; i < ui->tableView->model()->rowCount(); i++)
        {
            QModelIndex index = ui->tableView->model()->index(i, 0);
            ui->tableView->selectionModel()->select(index, QItemSelectionModel::Deselect);
        }
    }
}
