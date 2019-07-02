#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QEventLoop>
#include <QCloseEvent>

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    int exec();

private:
    void paint();

private:
    int m_Result; // 1:登录成功 0：登录失败
    QEventLoop* m_Loop;

    QHBoxLayout* hLayoutUser;
    QHBoxLayout* hLayoutPwd;
    QHBoxLayout* hLayoutBtn;
    QVBoxLayout* vLayoutLogin;

    QLabel* lblUser;
    QLabel* lblPwd;

    QLineEdit* txtUser;
    QLineEdit* txtPwd;

    QPushButton* btnLogin;
    QPushButton* btnCancel;

protected:
    void closeEvent(QCloseEvent* event);

signals:

public slots:
    void on_btnLogin_clicked();
    void on_btnCancel_clicked();
};

#endif // LOGIN_H
