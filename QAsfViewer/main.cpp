#include <QtGui>
#include <QtCore>
#include <casf.h>
#include <window.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window *w = new window();

    w->show();

    QString filePath = QFileDialog::getOpenFileName(w,
                              "Open file", "", "All (*.*)");

    if(!filePath.isEmpty())
    {
        w->asf = new casf;

        w->asf->readFile(filePath);
    }
    return a.exec();
}
