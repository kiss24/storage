#include "login.h"
#include "edit.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDialog>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // load language
    QTranslator translator;
    translator.load("cn.qm");

    a.installTranslator(&translator);

    //    Login login;
    //    if(login.exec() == 1)
    //        return 1;

    MainWindow *m = new MainWindow();
    m->setMinimumHeight(500);
    m->setMinimumWidth(1100);
    m->exec();
    delete m;

    //    Edit edit;
    //        if(edit.exec() == 1)
    //            return 1;

    return a.exec();
}
