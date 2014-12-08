#include "datatrans.h"
#include "ui_datatrans.h"
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

DataTrans::DataTrans(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataTrans)
{
    ui->setupUi(this);

    progressBar = new QProgressBar(this);
    completed = new QLabel("completed");
    tableView = new QTableView();
    proxy = new QSortFilterProxyModel(this);

    progressBar->setValue(0);

    ui->statusBar->addPermanentWidget(progressBar, 1);
    ui->statusBar->addPermanentWidget(completed);

    //connectSQLitePolo();
    //connectSQLiteFinTrans();
    //select_dbTableNames();
}

DataTrans::~DataTrans()
{
    delete ui;
}

QString DataTrans::chooseSourceDB()
{
    return sourceDBFile;
}

QString DataTrans::chooseTargetDB()
{
    return targetDBFile;
}

bool DataTrans::connectSQLitePolo()
{
    if (pDBPolo){
        pDBPolo->release();
    }

    pDBPolo = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    //QString file = QFileDialog::getOpenFileName(this,"Open a database");
    if(!chooseSourceDB().isEmpty())

    if (!pDBPolo->connect(chooseSourceDB().toUtf8().constData()))
    //if (!pDBPolo->connect("C:/dbFiles/Polo.db"))
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

bool DataTrans::connectSQLiteFinTrans()
{
    if (pDBFinTrans){
        pDBFinTrans->release();
    }

    pDBFinTrans = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    //QString file = QFileDialog::getOpenFileName(this,"Open a database");
    if(!chooseTargetDB().isEmpty())

    if (!pDBFinTrans->connect(chooseTargetDB().toUtf8().constData()))
    //if (!pDBFinTrans->connect("C:/dbFiles/FinTrans.db"))
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

bool DataTrans::select_dbTableNames()
{
    if (!pDBPolo)
        return false;

    QString columnName = "table";
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

    setModel(model);
    setCheckBoxes();

    return true;
}

void DataTrans::setModel(MyModel *model)
{
    proxy->setSourceModel(model);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(0);

    tableView->setModel(proxy);
    tableView->resizeRowsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);

    for(int i = 0; i < tableView->model()->rowCount(); i++)
    {
        ui->listWidget->addItem(tableView->model()->data(tableView->model()->index(i, 0)).toString());
    }
}

void DataTrans::setCheckBoxes()
{
    for(int i=0;i<ui->listWidget->count();i++)
    {
            ui->listWidget->item(i)->setFlags(ui->listWidget->item(i)->flags() |Qt::ItemIsUserCheckable);
            ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
    }
}

void DataTrans::on_filterLineEdit_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);

    ui->listWidget->clear();

    for(int i = 0; i < tableView->model()->rowCount(); i++)
    {
        ui->listWidget->addItem(tableView->model()->data(tableView->model()->index(i, 0)).toString());
    }

    setCheckBoxes();
}

void DataTrans::on_selectAllCheckBox_clicked(bool checked)
{
    if(checked == true)
    {
        for(int i=0;i<ui->listWidget->count();i++)
        {
                ui->listWidget->item(i)->setCheckState(Qt::Checked);
        }
    }

    else
    {
        for(int i=0;i<ui->listWidget->count();i++)
        {
                ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
        }
    }
}


void DataTrans::on_browseSourcePushButton_clicked()
{
     sourceDBFile = QFileDialog::getOpenFileName(this,"Choose source database");
     ui->label->setText("Source Database: Polo.db");
     connectSQLitePolo();
     select_dbTableNames();
}

void DataTrans::on_browseTargetPushButton_clicked()
{
    targetDBFile = QFileDialog::getOpenFileName(this,"Choose target database");
    ui->label_2->setText("Target Database: FinTrans.db");
    connectSQLiteFinTrans();
}
