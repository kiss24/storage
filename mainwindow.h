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
#include <QWidget>

#include "common.h"

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

    QHBoxLayout* hLayoutTop;
    QHBoxLayout* hLayoutView;
    QHBoxLayout* hLayoutBottom;

    QVBoxLayout* vLayoutButtons;
    QVBoxLayout* vLayoutView;

    QTableView* view;
    QSqlTableModel* model;

    QPushButton* btnSearch;
    QPushButton* btnInsert;
    QPushButton* btnUpdate;
    QPushButton* btnDelete;

private:
    CommodityInfo commodityInfo;

    QString sqlCreate;
    QString sqlSearch;
    QString sqlInsert;
    QString sqlUpdate;
    QString sqlDelete;

private:
    void initDB();
    void initModel();
    void paint();
    void Connect();

    bool isFileExist(QString fullFilePath);

protected:
    void closeEvent(QCloseEvent* event);

signals:

public slots:
    on_btnSearch_clicked();
    on_btnInsert_clicked();
    on_btnUpdate_clicked();
    on_btnDelete_clicked();

    on_view_select(QModelIndex index);
};

#endif // MAINWINDOW_H
