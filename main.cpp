#include "login.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

//    Login login;
//    if(login.exec() == 1)
//        return 1;

    MainWindow m;
    m.exec();

    return a.exec();
}
