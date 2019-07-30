#include "login.h"

#include <QMessageBox>

Login::Login(QWidget *parent) : QWidget(parent)
{   
    this->setWindowModality(Qt::ApplicationModal);

    paint();

    connect(btnLogin, &QPushButton::clicked, this, &Login::on_btnLogin_clicked);
    connect(btnCancel, &QPushButton::clicked, this, &Login::on_btnCancel_clicked);
}

Login::~Login()
{
    delete vLayoutLogin;
    delete m_Loop;
}

int Login::exec()
{
    m_Result = 0;
    this->show();

    m_Loop = new QEventLoop(this);
    m_Loop->exec();

    return m_Result;
}

void Login::paint()
{
    lblUser = new QLabel(tr("User"));
    lblPwd = new QLabel(tr("Password"));

    txtUser = new QLineEdit();
    txtPwd = new QLineEdit();

    btnLogin = new QPushButton("Login");
    btnCancel = new QPushButton("Canel");

    hLayoutUser = new QHBoxLayout();
    hLayoutUser->addWidget(lblUser);
    hLayoutUser->addWidget(txtUser);

    hLayoutPwd = new QHBoxLayout();
    hLayoutPwd->addWidget(lblPwd);
    hLayoutPwd->addWidget(txtPwd);

    hLayoutBtn = new QHBoxLayout();
    hLayoutBtn->addWidget(btnLogin);
    hLayoutBtn->addWidget(btnCancel);

    vLayoutLogin = new QVBoxLayout(this);
    vLayoutLogin->addLayout(hLayoutUser);
    vLayoutLogin->addLayout(hLayoutPwd);
    vLayoutLogin->addLayout(hLayoutBtn);
}

void Login::closeEvent(QCloseEvent *event)
{
    if(m_Loop != NULL)
    {
        m_Loop->exit();
    }

    event->accept();
}

void Login::on_btnLogin_clicked()
{
    if(this->txtUser->text().trimmed()== tr("1") && this->txtPwd->text().trimmed()==tr("1"))
    {
        m_Result = 1;

        close();
    }
    else
    {
        QMessageBox::warning(this,tr("warring"),tr("Incorrect username or password"),QMessageBox::Yes);

        this->txtUser->clear();
        this->txtPwd->clear();
        this->txtUser->setFocus();
    }
}

void Login::on_btnCancel_clicked()
{
    this->close();
}
