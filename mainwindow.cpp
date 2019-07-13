#include "mainwindow.h"
#include "sqliteutil.h"

#include <QString>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

//    initDB();

    initModel();

    paint();
}

MainWindow::~MainWindow()
{
    delete hLayoutView;
    delete m_Loop;
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
    if(isFileExist("Commidity.db"))
    return;

    QString createTable = "CREATE TABLE Commodity (ID INTEGER PRIMARY KEY AUTOINCREMENT, Time VARCHAR(32), "
                          "Category VARCHAR(32), Company VARCHAR(32), Count INT, Price INT, TotalPrice INT, Note VARCHAR(128))";

    QString insert = "INSERT INTO Commodity (Time, Category, Company, Count, Price, TotalPrice, Note) "
                     "VALUES ('2019-07-06 12:24', 'ball', 'NBA Store', 3, 20.0, 60, 'happy')";

    SqliteUtil* sqliteUtil = new SqliteUtil("Commidity.db");
    sqliteUtil->ExecuteRecord(createTable);
//    sqliteUtil->ExecuteRecord(insert);
    delete sqliteUtil;
}

void MainWindow::initModel()
{
    SqliteUtil* sqliteUtil = new SqliteUtil("Commidity.db");

    model = new QSqlTableModel(this, sqliteUtil->m_db);
    model->setTable("Commodity");
    model->select();

    delete sqliteUtil;
}

void MainWindow::paint()
{
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

    hLayoutView = new QHBoxLayout(this);
    hLayoutView->addLayout(vLayoutView);
    hLayoutView->addLayout(vLayoutButtons);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_Loop != NULL)
    {
        m_Loop->exit();
    }

    event->accept();
}
