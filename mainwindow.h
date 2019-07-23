#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QEventLoop>
#include <QCloseEvent>
#include <QSqlTableModel>
#include <QTableView>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTimeEdit>
#include <QLineEdit>

#include "common.h"
#include "sqliteutil.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int exec();

private:
    int m_Result;
    QEventLoop* m_Loop;

    QHBoxLayout* hLayoutType;
    QHBoxLayout* hLayoutTime;
    QHBoxLayout* hLayoutView;
    QHBoxLayout* hLayoutInfo;

    QVBoxLayout* vLayoutMain;
    QVBoxLayout* vLayoutButtons;
    QVBoxLayout* vLayoutView;

    QTableView* view;
    QSqlTableModel* model;

    QPushButton* btnSearch;
    QPushButton* btnInsert;
    QPushButton* btnUpdate;
    QPushButton* btnDelete;

    QPushButton* btnAll;
    QPushButton* btnIn;
    QPushButton* btnOut;

    QLabel* lblTimeBegin;
    QLabel* lblTimeEnd;
    QLabel* lblRecordCount;
    QLabel* lblRecordCountInfo;
    QLabel* lblTotalPrice;
    QLabel* lblTotalPriceInfo;

    QDateTimeEdit* dateTimeEditBegin;
    QDateTimeEdit* dateTimeEditEnd;

    QLabel* lblCompany;

    QLineEdit* lineEditCompany;

private:
    QString DBName;
    CommodityInfo commodityInfo;
    SqliteUtil* sqliteUtil;

    QString sqlCreate;
    QString sqlSearch;
    QString sqlInsert;
    QString sqlUpdate;
    QString sqlDelete;

    QString company;
    QString dateTimeBegin;
    QString dateTimeEnd;

    const int TypeAll = -1;
    const int TypeIn = 1;
    const int TypeOut = 0;

private:
    void initPara();
    void initDB();
    void initModel();
    void paint();
    void Connect();
    void select(int type);

    bool isFileExist(QString fullFilePath);

protected:
    void closeEvent(QCloseEvent* event);

signals:

public slots:
    void on_btnSearch_clicked();
    void on_btnInsert_clicked();
    void on_btnUpdate_clicked();
    void on_btnDelete_clicked();

    void on_btnAll_clicked();
    void on_btnIn_clicked();
    void on_btnOut_clicked();

    void on_dateTimeEditBegin_changed(const QDateTime &dateTime);
    void on_dateTimeEditEnd_changed(const QDateTime &dateTime);

    void on_lineEditCompany_changed(const QString &content);

    void on_view_select(QModelIndex index);
};

#endif // MAINWINDOW_H
