#include "mainwindow.h"

#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>

extern CommodityInfo globalCommodityInfo;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{   
    initPara();

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

void MainWindow::initPara()
{
    company = "";

    dateTimeBegin = QDateTime::currentDateTime().
            toString("yyyy-MM-dd HH：mm：ss");
    dateTimeEnd = QDateTime::currentDateTime().addMonths(1).
            toString("yyyy-MM-dd HH：mm：ss");
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
                "VALUES ('2019-08-24 09:32:44', '1', 'ball', 'CBA', '3', '40.0', '120', 'happy')";

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

    // info
    hLayoutInfo = new QHBoxLayout();

    lblRecordCount = new QLabel();
    lblRecordCountInfo = new QLabel();
    lblTotalPrice = new QLabel();
    lblTotalPriceInfo = new QLabel();

    lblRecordCount->setText(tr("Record Count: "));
    lblRecordCountInfo->setText(tr("0"));
    lblTotalPrice->setText(tr("Total Price: "));
    lblTotalPriceInfo->setText(tr("0"));

    hLayoutInfo->addWidget(lblRecordCount);
    hLayoutInfo->addWidget(lblRecordCountInfo);
    hLayoutInfo->addWidget(lblTotalPrice);
    hLayoutInfo->addWidget(lblTotalPriceInfo);

    // Main
    vLayoutMain = new QVBoxLayout(this);

    vLayoutMain->addLayout(hLayoutType);
    vLayoutMain->addLayout(hLayoutTime);
    vLayoutMain->addLayout(hLayoutView);
    vLayoutMain->addLayout(hLayoutInfo);

    // control init
    dateTimeEditBegin->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    dateTimeEditEnd->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    dateTimeEditBegin->setCalendarPopup(true);
    dateTimeEditEnd->setCalendarPopup(true);

    dateTimeEditBegin->setDateTime(QDateTime::currentDateTime());
    dateTimeEditEnd->setDateTime(QDateTime::currentDateTime().addMonths(1));
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

    connect(dateTimeEditBegin, &QDateTimeEdit::dateTimeChanged, this, &MainWindow::on_dateTimeEditBegin_changed);
    connect(dateTimeEditEnd, &QDateTimeEdit::dateTimeChanged, this, &MainWindow::on_dateTimeEditEnd_changed);

    connect(lineEditCompany, &QLineEdit::textChanged, this, &MainWindow::on_lineEditCompany_changed);

    connect(view, &QTableView::clicked, this, &MainWindow::on_view_select);

    connect(edit.btnOK, &QPushButton::clicked, this, &MainWindow::on_btnOK_clicked);
    connect(edit.btnCancel, &QPushButton::clicked, this, &MainWindow::on_btnCancel_clicked);
}

// type: -1:All 0：Out 1:In
void MainWindow::select(int type = -1)
{
    // view
    QString filter = "";
    QString filterTime= "";
    QString filterType = "";
    QString filterCompany = "";

    filterTime = "Time > '" + dateTimeBegin + "' AND Time < '" + dateTimeEnd + "'";

    switch (type)
    {
    case -1:
        filterType = "";
        break;
    case 0:
        filterType = "AND Type = '0'";
        break;
    case 1:
        filterType = "AND Type = '1'";
    default:
        break;
    }

    if(!QString(company).isEmpty())
        filterCompany = QString("AND Company = '%0'").arg(company);

    filter = QString("%0 %1 %2").arg(filterTime).arg(filterType).arg(filterCompany);

    qDebug() << filter;

    model->setFilter(filter);
    model->select();

    // info
    QString sqlCount = QString("SELECT Count(ID) FROM Commodity WHERE %0").arg(filter);
    QString count = "";
    QString sqlSum = QString("SELECT SUM(TotalPrice) FROM Commodity WHERE %0").arg(filter);
    QString sum = "";

    qDebug() << sqlCount;
    qDebug() << sqlSum;

    count = sqliteUtil->ExecuteString(sqlCount);
    sum = sqliteUtil->ExecuteString(sqlSum);

    qDebug() << count;
    qDebug() << sum;

    lblRecordCountInfo->setText(count);
    lblTotalPriceInfo->setText(sum);
}

void MainWindow::Insert(CommodityInfo info)
{
    sqlInsert = QString("INSERT INTO Commodity(Time, Type, Category, Company, Count, Price, TotalPrice, Note)"
                        "VALUES ('%0', '%1', '%2', '%3', '%4', '%5', '%6', '%7')")
            .arg(info.time).arg(info.type).arg(info.category).arg(info.company).arg(info.count).arg(info.price)
            .arg(info.totalPrice).arg(info.note);

    sqliteUtil->ExecuteRecord(sqlInsert);
}

void MainWindow::Update(CommodityInfo info)
{

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
    select(TypeAll);
}

void MainWindow::on_btnIn_clicked()
{
    select(TypeIn);
}

void MainWindow::on_btnOut_clicked()
{
    select(TypeOut);
}

void MainWindow::on_dateTimeEditBegin_changed(const QDateTime &dateTime)
{
    dateTimeBegin = dateTime.toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << dateTimeBegin;
}

void MainWindow::on_dateTimeEditEnd_changed(const QDateTime &dateTime)
{
    dateTimeEnd = dateTime.toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << dateTimeEnd;
}

void MainWindow::on_lineEditCompany_changed(const QString &content)
{
    company = content;
    qDebug() << company;
}

void MainWindow::on_btnSearch_clicked()
{
    model->setTable("Commodity");
    model->select();
}

void MainWindow::on_btnInsert_clicked()
{
    edit.InsertData = true;

    edit.exec();
}

void MainWindow::on_btnUpdate_clicked()
{
    QModelIndexList select = view->selectionModel()->selectedRows();

    if(!select.empty())
    {
        edit.InsertData = false;

        edit.exec();
    }
    else
    {
        QMessageBox::information(NULL, tr(""), tr("select one record."),
                                 QMessageBox::Yes, QMessageBox::Yes);
    }
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

    globalCommodityInfo = commodityInfo;
}

void MainWindow::on_btnOK_clicked()
{
    qDebug() << "OK";

    globalCommodityInfo.ID = edit.lineEditID->text().toInt();
    globalCommodityInfo.type = edit.comboBoxType->currentIndex();
    globalCommodityInfo.time = edit.dateTimeEdit->text();
    globalCommodityInfo.category = edit.lineEditCategory->text();
    globalCommodityInfo.company = edit.lineEditCompany->text();
    globalCommodityInfo.count = edit.lineEditCount->text().toInt();
    globalCommodityInfo.price = edit.lineEditPrice->text().toDouble();
    globalCommodityInfo.totalPrice = edit.lineEditTotalPrice->text().toDouble();
    globalCommodityInfo.note = edit.lineEditNote->text();

    qDebug() << "ID: " << globalCommodityInfo.ID;
    qDebug() << "type: " << globalCommodityInfo.type;
    qDebug() << "time: " << globalCommodityInfo.time;
    qDebug() << "category: " << globalCommodityInfo.category;
    qDebug() << "company: " << globalCommodityInfo.company;
    qDebug() << "count: " << globalCommodityInfo.count;
    qDebug() << "price: " << globalCommodityInfo.price;
    qDebug() << "totalPrice: " << globalCommodityInfo.totalPrice;
    qDebug() << "note: " << globalCommodityInfo.note;

    if(edit.InsertData)
        Insert(globalCommodityInfo);
    else
        Update(globalCommodityInfo);

    edit.close();
}

void MainWindow::on_btnCancel_clicked()
{
    qDebug() << "Cancel";

    edit.close();
}


















