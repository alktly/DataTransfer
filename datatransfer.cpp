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

db::ISQLDatabase *pDB = 0;

DataTransfer::DataTransfer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataTransfer)
{
    ui->setupUi(this);
    connectSQLite();
}

DataTransfer::~DataTransfer()
{
    delete ui;
}

bool DataTransfer::connectSQLite()
{
    if (pDB){
        pDB->release();
    }

    pDB = createSQLDatabase(db::ISQLDatabase::DB_SQLITE, db::ISQLDatabase::SER_SQLITE3);

    //QString file = QFileDialog::getOpenFileName(this,"Open a database");
    //if(!file.isEmpty())

    //if (!pDB->connect(file.toUtf8().constData()))
    if (!pDB->connect("D:/project.db3"))
    {
        std::cout << "Cannot connect to database" << std::endl;
        td::String err;
        pDB->getErrorStr(err);
        std::cout << err.c_str() << std::endl;
        pDB->release();
        pDB = 0;
        //messageBox noC(3, this);
        //noC.show();
        //noC.exec();
        return false;
    }
    std::cout << "Connection OK!" << std::endl;
    return true;
}
