#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
    if(!w)w=new Widget;
    w->show();
    return a.exec();
}
