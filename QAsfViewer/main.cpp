#include <QtGui>
#include <QtCore>
#include <casf.h>
#include <window.h>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window *w = new window();

    w->show();

    return a.exec();
}
