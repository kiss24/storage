#include "mainwindow.h"
//#include "sqliteutil.h"

#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    initDB();

    initModel();

    paint();

    Connect();
}

MainWindow::~MainWindow()
{
    delete vLayoutMain;
    delete m_Loop;
    delete sqliteUtil;
}

int MainWindow::exec()
{
    m_Result = 0;
    this->show();

    m_Loop = new QEventLoop(this);
    m_Loop->exec();

    return m_Result;
}

bool MainWindow::isFileExist(QString fullFilePath)
{
    QFile file(fullFilePath);
    if(file.exists())
    {
        return true;
    }
    return false;
}

void MainWindow::initDB()
{
    DBName = "Commodity.db";

    //    if(isFileExist(DBName))
    //        return;

    sqlCreate = "CREATE TABLE Commodity (ID INTEGER PRIMARY KEY AUTOINCREMENT, Time VARCHAR(32), Type VARCHAR(32), "
                "Category VARCHAR(32), Company VARCHAR(32), Count VARCHAR(32), Price VARCHAR(32), TotalPrice VARCHAR(32), Note VARCHAR(128))";

    sqlInsert = "INSERT INTO Commodity (Time, Type, Category, Company, Count, Price, TotalPrice, Note) "
                "VALUES ('2019-07-06 12:24', '1', 'ball', 'NBA Store', '3', '20.0', '60', 'happy')";

    SqliteUtil* sqliteUtil = new SqliteUtil(DBName);
    //sqliteUtil->ExecuteRecord(sqlCreate);
    sqliteUtil->ExecuteRecord(sqlInsert);
    delete sqliteUtil;
}

void MainWindow::initModel()
{
    sqliteUtil = new SqliteUtil(DBName);

    model = new QSqlTableModel(this, sqliteUtil->m_db);
    model->setTable("Commodity");
    model->select();
}

void MainWindow::paint()
{
    // view
    view = new QTableView();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setSortingEnabled(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setShowGrid(true);
    view->setModel(model);

    btnSearch = new QPushButton();
    btnInsert = new QPushButton();
    btnUpdate = new QPushButton();
    btnDelete = new QPushButton();

    btnSearch->setText(tr("Search"));
    btnInsert->setText(tr("Insert"));
    btnUpdate->setText(tr("Update"));
    btnDelete->setText(tr("Delete"));

    hLayoutView = new QHBoxLayout();
    vLayoutButtons = new QVBoxLayout();
    vLayoutView = new QVBoxLayout();

    vLayoutButtons->addWidget(btnSearch);
    vLayoutButtons->addWidget(btnInsert);
    vLayoutButtons->addWidget(btnUpdate);
    vLayoutButtons->addWidget(btnDelete);

    vLayoutView->addWidget(view);

    hLayoutView = new QHBoxLayout();
    hLayoutView->addLayout(vLayoutView);
    hLayoutView->addLayout(vLayoutButtons);

    // type
    btnAll = new QPushButton();
    btnIn = new QPushButton();
    btnOut = new QPushButton();

    btnAll->setText(tr("All"));
    btnIn->setText(tr("In"));
    btnOut->setText(tr("Out"));

    hLayoutType = new QHBoxLayout();

    hLayoutType->addWidget(btnAll);
    hLayoutType->addWidget(btnIn);
    hLayoutType->addWidget(btnOut);

    // time & company
    lblTimeBegin = new QLabel();
    lblTimeEnd = new QLabel();
    lblCompany = new QLabel();

    lblTimeBegin->setText(tr("Begin: "));
    lblTimeEnd->setText(tr("End: "));
    lblCompany->setText(tr("Company: "));

    dateTimeEditBegin = new QDateTimeEdit();
    dateTimeEditEnd = new QDateTimeEdit();

    lineEditCompany = new QLineEdit();

    hLayoutTime = new QHBoxLayout();

    hLayoutTime->addWidget(lblTimeBegin);
    hLayoutTime->addWidget(dateTimeEditBegin);
    hLayoutTime->addWidget(lblTimeEnd);
    hLayoutTime->addWidget(dateTimeEditEnd);
    hLayoutTime->addWidget(lblCompany);
    hLayoutTime->addWidget(lineEditCompany);

    // Main
    vLayoutMain = new QVBoxLayout(this);

    vLayoutMain->addLayout(hLayoutType);
    vLayoutMain->addLayout(hLayoutTime);
    vLayoutMain->addLayout(hLayoutView);

    // control init
    dateTimeEditBegin->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    dateTimeEditEnd->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    dateTimeEditBegin->setCalendarPopup(true);
    dateTimeEditEnd->setCalendarPopup(true);

    //dateTimeEditBegin->setDateTime(QDateTime.currentDateTime());
    //dateTimeEditEnd->setDateTime(QDateTime.currentDateTime());
}

void MainWindow::Connect()
{
    connect(btnSearch, &QPushButton::clicked, this, &MainWindow::on_btnSearch_clicked);
    connect(btnInsert, &QPushButton::clicked, this, &MainWindow::on_btnInsert_clicked);
    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::on_btnUpdate_clicked);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::on_btnDelete_clicked);

    connect(btnAll, &QPushButton::clicked, this, &MainWindow::on_btnAll_clicked);
    connect(btnIn, &QPushButton::clicked, this, &MainWindow::on_btnIn_clicked);
    connect(btnOut, &QPushButton::clicked, this, &MainWindow::on_btnOut_clicked);

    connect(view, &QTableView::clicked, this, &MainWindow::on_view_select);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_Loop != NULL)
    {
        m_Loop->exit();
    }

    event->accept();
}

void MainWindow::on_btnAll_clicked()
{
    model->select();
}

void MainWindow::on_btnIn_clicked()
{
    model->setFilter(QObject::tr("Type = '1'"));  // Type 1:In 0:Out
    model->select();
}

void MainWindow::on_btnOut_clicked()
{
    model->setFilter(QObject::tr("Type = '0'"));
    model->select();
}

void MainWindow::on_btnSearch_clicked()
{
    model->setTable("Commodity");
    model->select();
}

void MainWindow::on_btnInsert_clicked()
{

}

void MainWindow::on_btnUpdate_clicked()
{

}

void MainWindow::on_btnDelete_clicked()
{
    QModelIndexList select = view->selectionModel()->selectedRows();

    if(!select.empty())
    {
        QModelIndexList select = view->selectionModel()->selectedRows();
        QModelIndex idIndex = select.at(0);

        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("Delete"),
                                       QString(tr("Are you sure to delete information ID = %0 ?").arg(commodityInfo.ID)),
                                       QMessageBox::Yes|QMessageBox::No);
        if(button == QMessageBox::Yes)
        {
            model->removeRow(idIndex.row());
            model->submitAll();
            model->select();
        }
    }
}

void MainWindow::on_view_select(QModelIndex index)
{
    //    ( "ID", "Time", "Type", "Category", "Company", "Count",
    //    "Price", "TotalPrice", "Note" )
    QSqlRecord record = model->record(index.row());

    commodityInfo.ID = record.value("ID").toInt();
    commodityInfo.type = record.value("Type").toInt();
    commodityInfo.time = record.value("Time").toString();
    commodityInfo.category = record.value("Category").toString();
    commodityInfo.company = record.value("Company").toString();
    commodityInfo.count = record.value("Count").toInt();
    commodityInfo.price = record.value("Price").toDouble();
    commodityInfo.totalPrice = record.value("TotalPrice").toDouble();
    commodityInfo.note = record.value("Note").toString();

    qDebug() << "commodityInfo.ID: " << commodityInfo.ID;
    qDebug() << "commodityInfo.type: " << commodityInfo.type;
    qDebug() << "commodityInfo.time: " << commodityInfo.time;
    qDebug() << "commodityInfo.category: " << commodityInfo.category;
    qDebug() << "commodityInfo.company: " << commodityInfo.company;
    qDebug() << "commodityInfo.count: " << commodityInfo.count;
    qDebug() << "commodityInfo.price: " << commodityInfo.price;
    qDebug() << "commodityInfo.totalPrice: " << commodityInfo.totalPrice;
    qDebug() << "commodityInfo.note: " << commodityInfo.note;
}


















