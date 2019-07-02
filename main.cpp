#include "widget.h"
#include "login.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    Login login;
    if(login.exec() == 1)
        return 1;

    return a.exec();
}
