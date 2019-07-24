#include "login.h"
#include "edit.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    Login login;
    //    if(login.exec() == 1)
    //        return 1;

    MainWindow m;
    m.exec();

    //    Edit edit;
    //        if(edit.exec() == 1)
    //            return 1;

    return a.exec();
}
