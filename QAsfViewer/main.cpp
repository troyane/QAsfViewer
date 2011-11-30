#include <QtGui>
#include <QtCore>
#include <casf.h>
#include <cframe.h>
#include <functions.cpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *window = new QWidget;
    QPushButton *btnOpen = new QPushButton("Open", window);
    QPushButton *button2 = new QPushButton("Two", window);
// ------ graphics objects
    QGraphicsView *view = new QGraphicsView(window);
    QGraphicsScene *scene = new QGraphicsScene(window);
    QImage *image = new QImage();

    QLabel *lblAboveView = new QLabel("", window);
    QLabel *lblAboveSlider = new QLabel("Position:", window);
    QSlider *slider = new QSlider(Qt::Horizontal, window);

    QPushButton *btnPlay = new QPushButton("Play", window);
    QPushButton *btnPause = new QPushButton("Pause", window);
    QPushButton *btnStop = new QPushButton("Stop", window);
    QPushButton *btnNextFrame = new QPushButton(">", window);
    QPushButton *btnPrevFrame = new QPushButton("<", window);

    QListView *lstView = new QListView(window);
    lstView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QLabel *lblAboveList = new QLabel("File parameters:");
    QLabel *lblAboveBtns = new QLabel("Operations:");

// ------ Control buttons
    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addStretch();
    controlsLayout->addWidget(btnPlay);
    controlsLayout->addWidget(btnPause);
    controlsLayout->addWidget(btnStop);
    controlsLayout->addWidget(btnPrevFrame);
    controlsLayout->addWidget(btnNextFrame);
    controlsLayout->addStretch();

// ------ Left side
    QVBoxLayout *leftVLayout = new QVBoxLayout;
    leftVLayout->addWidget(lblAboveBtns);
    leftVLayout->addWidget(btnOpen);
    leftVLayout->addWidget(button2);
    leftVLayout->addWidget(lblAboveList);
    leftVLayout->addWidget(lstView);
    leftVLayout->addStretch();

// ------ Right side
    QVBoxLayout *rightVLayout = new QVBoxLayout;
    rightVLayout->addWidget(lblAboveView);
    rightVLayout->addWidget(view);
    rightVLayout->addWidget(lblAboveSlider);
    rightVLayout->addWidget(slider);
    rightVLayout->addLayout(controlsLayout);

// ------ Main layout
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    mainHLayout->addLayout(leftVLayout);
    mainHLayout->addLayout(rightVLayout);

    window->setLayout(mainHLayout);

// ------ Applaing functional
    QPixmap buffer(100, 100);
    QPainter painter(&buffer);
//    painter.drawLine(0,0,30,30);

    casf asf;


//    example3.asf

    painter.fillRect(buffer.rect(), QBrush(Qt::yellow));
    painter.setPen(Qt::red);
    painter.drawPoint(20, 20);

    scene->addPixmap(buffer);
    view->setScene(scene);

//    QObject::connect(btnOpen, SIGNAL(clicked()), asf, SLOT() )
    window->show();

    QString filePath = QFileDialog::getOpenFileName(window,
                                                  "Open file",
                                                  "",
                                                  "All (*.*)");
    if(!filePath.isEmpty())
    {
        readFile(filePath);
    }



    return a.exec();
}
