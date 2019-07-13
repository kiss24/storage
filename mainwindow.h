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
    void initDB();
    void initModel();
    void paint();
    bool isFileExist(QString fullFilePath);

protected:
    void closeEvent(QCloseEvent* event);

signals:

public slots:
};

#endif // MAINWINDOW_H
