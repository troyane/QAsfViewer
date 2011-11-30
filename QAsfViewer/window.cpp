#include "window.h"
#include <QtGui>


window::window(QWidget *parent) :
    QWidget(parent)
{
    btnOpen = new QPushButton("Open", this);
    button2 = new QPushButton("Two", this);

    //    QImage *image = new QImage();
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    lblAboveView = new QLabel("", this);
    lblAboveSlider = new QLabel("Position:", this);
    slider = new QSlider(Qt::Horizontal, this);

    btnPlay = new QPushButton("Play", this);
    btnPause = new QPushButton("Pause", this);
    btnStop = new QPushButton("Stop", this);
    btnNextFrame = new QPushButton(">", this);
    btnPrevFrame = new QPushButton("<", this);

    lstView = new QTextEdit(this);
    lstView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    lblAboveList = new QLabel("File parameters:");
    lblAboveBtns = new QLabel("Operations:");

    // ------ Control buttons
    controlsLayout = new QHBoxLayout;
    controlsLayout->addStretch();
    controlsLayout->addWidget(btnPlay);
    controlsLayout->addWidget(btnPause);
    controlsLayout->addWidget(btnStop);
    controlsLayout->addWidget(btnPrevFrame);
    controlsLayout->addWidget(btnNextFrame);
    controlsLayout->addStretch();

    // ------ Left side
    leftVLayout = new QVBoxLayout;
    leftVLayout->addWidget(lblAboveBtns);
    leftVLayout->addWidget(btnOpen);
    leftVLayout->addWidget(button2);
    leftVLayout->addWidget(lblAboveList);
    leftVLayout->addWidget(lstView);
    leftVLayout->addStretch();

    // ------ Right side
    rightVLayout = new QVBoxLayout;
    rightVLayout->addWidget(lblAboveView);
    rightVLayout->addWidget(view);
    rightVLayout->addWidget(lblAboveSlider);
    rightVLayout->addWidget(slider);
    rightVLayout->addLayout(controlsLayout);

    // ------ Main layout
    mainHLayout = new QHBoxLayout;
    mainHLayout->addLayout(leftVLayout);
    mainHLayout->addLayout(rightVLayout);

    this->setLayout(mainHLayout);

    actualFrame = -1;

    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(showFrame(int)));
    QObject::connect(btnOpen, SIGNAL(clicked()), this, SLOT(openFile()));
}

void window::showFrame(int numFrame)
{
//    int tmp = numFrame-1;
    if(numFrame!=-1 && actualFrame!=numFrame)
    {
        int rows = asf->getHeader("ROWS").toInt();
        int cols = asf->getHeader("COLS").toInt();
        qreal scaleFactorX = view->width() / rows - 0.5;
        qreal scaleFactorY = view->height() / cols - 0.5;

        slider->setMinimum(asf->getHeader("START_FRAME").toInt() - 1);
        slider->setMaximum(asf->getHeader("END_FRAME").toInt() - 1);

        QPixmap buffer(rows, cols);
        CFrame frame = asf->frames.at(numFrame);

        QImage *img = frame.createImage(rows, cols);
        buffer.convertFromImage(*img, Qt::AutoColor);

        scene->addPixmap(buffer);


        if (img) delete img;
        view->setScene(scene);

//        view->scale(scaleFactorX, scaleFactorY);

        actualFrame = numFrame;
        lblAboveSlider->setText(QString("<b>Position:</b> %1").arg(actualFrame));
    }

}

void window::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                              "Open file", "", "ASF-files (*.asf)");
    if(!filePath.isEmpty())
    {
        this->asf = new casf;
        if(this->asf->readFile(filePath)!=0)
        {
            QMessageBox::critical(0, "QAsfViewer - Critical", "File read error!.\n");
        } else {
            QMessageBox::information(0, "QAsfViewer - Information", "File was successfuly loaded!");
            // output to lstView all headers from ASF
            this->lstView->append(QString("<b>File:</b> %1").arg(filePath));
            QMap <QString, QString>::iterator mIter = this->asf->headers.begin();
            QMap <QString, QString>::iterator mEnd = this->asf->headers.end();

            for (; mIter != mEnd; mIter++)
            {
                this->lstView->append(QString("<b>%1:</b> %2").arg(mIter.key()).arg(mIter.value()));
            }

        }
    } else {
        QMessageBox::information(0, "QAsfViewer - Information","You must chose an ASF-file!");
    }
}
