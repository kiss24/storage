#include "edit.h"
#include "mainwindow.h"

#include <QDebug>

extern CommodityInfo globalCommodityInfo;

Edit::Edit(QWidget *parent) : QWidget(parent)
{
    this->setWindowModality(Qt::ApplicationModal);


    paint();
}

Edit::~Edit()
{
    delete m_Loop;
    delete gridLayout;
}

int Edit::exec()
{
    m_Result = 0;
    this->show();

    m_Loop = new QEventLoop(this);
    m_Loop->exec();

    return m_Result;
}

void Edit::paint()
{
    lblID = new QLabel();
    lblTime = new QLabel();
    lblType = new QLabel();
    lblCategory  = new QLabel();
    lblCompany = new QLabel();
    lblCount = new QLabel();
    lblPrice = new QLabel();
    lblTotalPrice = new QLabel();
    lblNote = new QLabel();

    lblID->setText(tr("ID: "));
    lblTime->setText(tr("Time: "));
    lblType->setText(tr("Type: "));
    lblCategory->setText(tr("Category: "));
    lblCompany->setText(tr("Company: "));
    lblCount->setText(tr("Count: "));
    lblPrice->setText(tr("Price: "));
    lblTotalPrice->setText(tr("TotalPrice: "));
    lblNote->setText(tr("Note: "));

    lineEditID = new QLineEdit();
    lineEditCategory = new QLineEdit();
    lineEditCompany = new QLineEdit();
    lineEditCount = new QLineEdit();
    lineEditPrice = new QLineEdit();
    lineEditTotalPrice = new QLineEdit();
    lineEditNote = new QLineEdit();

    dateTimeEdit = new QDateTimeEdit();

    comboBoxType = new QComboBox();

    comboBoxType->addItem(tr("Out"));
    comboBoxType->addItem(tr("In"));

    btnCancel = new QPushButton();
    btnOK = new QPushButton();

    btnCancel->setText(tr("Cancel"));
    btnOK->setText(tr("OK"));

    gridLayout = new QGridLayout(this);

    gridLayout->addWidget(lblID, 0, 0);
    gridLayout->addWidget(lineEditID, 0, 1);
    gridLayout->addWidget(lblTime, 0, 2);
    gridLayout->addWidget(dateTimeEdit, 0, 3);
    gridLayout->addWidget(lblType, 1, 0);
    gridLayout->addWidget(comboBoxType, 1, 1);
    gridLayout->addWidget(lblCategory, 1, 2);
    gridLayout->addWidget(lineEditCategory, 1, 3);
    gridLayout->addWidget(lblCompany, 2, 0);
    gridLayout->addWidget(lineEditCompany, 2, 1);
    gridLayout->addWidget(lblCount, 2, 2);
    gridLayout->addWidget(lineEditCount, 2, 3);
    gridLayout->addWidget(lblPrice, 3, 0);
    gridLayout->addWidget(lineEditPrice, 3, 1);
    gridLayout->addWidget(lblTotalPrice, 3, 2);
    gridLayout->addWidget(lineEditTotalPrice, 3, 3);
    gridLayout->addWidget(lblNote, 4, 0);
    gridLayout->addWidget(lineEditNote, 4, 1);
    gridLayout->addWidget(btnOK, 4, 2);
    gridLayout->addWidget(btnCancel, 4, 3);
}

void Edit::Connect()
{
//    connect(lineEditCategory, &QLineEdit::textChanged, this, on_lineEditCategory_changed);
//    connect(lineEditCompany, &QLineEdit::textChanged, this, on_lineEditCompany_changed);
//    connect(line)
}

void Edit::closeEvent(QCloseEvent *event)
{
    if(m_Loop != NULL)
    {
        m_Loop->exit();
    }

    event->accept();
}

//void Edit::on_lineEditCategory_changed(const QString &content)
//{

//}

//void Edit::on_lineEditCompany_changed(const QString &content)
//{

//}

//void Edit::on_lineEditCount_changed(const QString &content)
//{

//}
