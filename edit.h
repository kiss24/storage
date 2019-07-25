#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include <QEventLoop>
#include <QCloseEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

class Edit : public QWidget
{
    Q_OBJECT
public:
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
    int exec();

private:
    void paint();
    void Connect();
    void calculateTotalPrice();

public:
    QGridLayout* gridLayout;

    QLabel* lblID;
    QLabel* lblTime;
    QLabel* lblType;
    QLabel* lblCategory;
    QLabel* lblCompany;
    QLabel* lblCount;
    QLabel* lblPrice;
    QLabel* lblTotalPrice;
    QLabel* lblNote;

    QLineEdit* lineEditID;
    QLineEdit* lineEditCategory;
    QLineEdit* lineEditCompany;
    QLineEdit* lineEditCount;
    QLineEdit* lineEditPrice;
    QLineEdit* lineEditTotalPrice;
    QLineEdit* lineEditNote;

    QDateTimeEdit* dateTimeEdit;
    QComboBox* comboBoxType;

public:
    QPushButton* btnOK;
    QPushButton* btnCancel;

protected:
    void closeEvent(QCloseEvent* event);

private:
    int m_Result; // 1:登录成功 0：登录失败
    QEventLoop* m_Loop;

signals:

public slots:
//    void on_lineEditCategory_changed(const QString &content);
//    void on_lineEditCompany_changed(const QString &content);
    void on_lineEditCount_changed(const QString &content);
    void on_lineEditPrice_changed(const QString &content);
//    void on_lineEditTotalPrice_changed(const QString &content);
//    void on_lineEditNote_changed(const QString &content);
//    void on_dateTimeEdit_changed(const QDateTime &dateTime);
    void on_comboBoxType_changed(const QString &content);
};

#endif // EDIT_H
