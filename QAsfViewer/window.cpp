#include "window.h"
#include <QtGui>


window::window(QWidget *parent) :
    QWidget(parent)
{
    asf = 0;
    btnOpen = new QPushButton("Open", this);
    chkScale = new QCheckBox("Scale image", this);
    chkScale->setDisabled(true);
    chkScale->setHidden(true);
    chkScale->setChecked(false);

    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);

    lblAboveView = new QLabel("", this);
    lblAboveSlider = new QLabel("Position:", this);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setEnabled(false);

    btnPlay = new QPushButton("Play", this);
    btnStop = new QPushButton("Stop", this);
    btnNextFrame = new QPushButton(">", this);
    btnPrevFrame = new QPushButton("<", this);

    this->btnPlay->setEnabled(false);
    this->btnStop->setEnabled(false);
    this->btnPrevFrame->setEnabled(false);
    this->btnNextFrame->setEnabled(false);

    lstView = new QTextEdit(this);
    lstView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    lblAboveList = new QLabel("File parameters:", this);
    lblAboveBtns = new QLabel("Operations:", this);

    // ------ Control buttons
    controlsLayout = new QHBoxLayout();
    controlsLayout->addStretch();
    controlsLayout->addWidget(btnPlay);
    controlsLayout->addWidget(btnStop);
    controlsLayout->addWidget(btnPrevFrame);
    controlsLayout->addWidget(btnNextFrame);
    controlsLayout->addStretch();


    // ------ Left side
    leftVLayout = new QVBoxLayout();
    leftVLayout->addWidget(lblAboveBtns);
    leftVLayout->addWidget(btnOpen);
    leftVLayout->addWidget(chkScale);
    leftVLayout->addWidget(lblAboveList);
    leftVLayout->addWidget(lstView);
    leftVLayout->addStretch();

    // ------ Right side
    rightVLayout = new QVBoxLayout();
    rightVLayout->addWidget(lblAboveView);
    rightVLayout->addWidget(view);
    rightVLayout->addWidget(lblAboveSlider);
    rightVLayout->addWidget(slider);
    rightVLayout->addLayout(controlsLayout);

    // ------ Main layout
    mainHLayout = new QHBoxLayout(this);
    mainHLayout->addLayout(leftVLayout);
    mainHLayout->addLayout(rightVLayout);

    this->setLayout(mainHLayout);

    actualFrame = 0;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(showFrame(int)));
    QObject::connect(btnOpen, SIGNAL(clicked()), this, SLOT(openFile()));
    QObject::connect(btnPlay, SIGNAL(clicked()), this, SLOT(play()));
    QObject::connect(btnPrevFrame, SIGNAL(clicked()), this, SLOT(prevFrame()));
    QObject::connect(btnNextFrame, SIGNAL(clicked()), this, SLOT(nextFrame()));
    QObject::connect(btnStop, SIGNAL(clicked()), this, SLOT(stop()));
    QObject::connect(chkScale, SIGNAL(toggled(bool)), this, SLOT(setScale(bool)));
}

window::~window()
{
    if(asf) delete asf;
}

void window::showFrame(int numFrame)
{
//    int tmp = numFrame-1;
    if(numFrame!=0 && actualFrame!=numFrame)
    {
        int rows = asf->getHeader("ROWS").toInt();
        int cols = asf->getHeader("COLS").toInt();

        slider->setMinimum(asf->getHeader("START_FRAME").toInt() - 1);
        slider->setMaximum(asf->getHeader("END_FRAME").toInt() - 1);

        QPixmap buffer(rows, cols);
        CFrame *frame = asf->frames.at(numFrame);

        QImage *img = frame->createImage();
        buffer.convertFromImage(*img, Qt::AutoColor);

        scene->addPixmap(buffer);

        if (img) delete img;
        view->setScene(scene);

        actualFrame = numFrame;
        lblAboveSlider->setText(QString("<b>Position:</b> %1").arg(actualFrame));
        //lblAboveView->setText(QString("<b>Frame info:</b> %1").arg(frame.getHeader()));
    }
}

void window::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                              "Open file", "", "ASF-files (*.asf)");
    if(!filePath.isEmpty())
    {
        if (asf) delete asf;
        asf = new casf;
        if (asf->readFile(filePath))
        {
            QMessageBox::critical(0, "QAsfViewer - Critical", "File read error!\n No file were opened!");
        } else
        {
            QMessageBox::information(0, "QAsfViewer - Information", "File was successfuly loaded!");
            // output to lstView all headers from ASF
            this->lstView->append(QString("<b>File:</b> %1").arg(filePath));
            QMap <QString, QString>::iterator mIter = asf->headers.begin();
            QMap <QString, QString>::iterator mEnd = asf->headers.end();
            // enable all controls
            this->btnPlay->setEnabled(true);
            this->btnStop->setEnabled(true);
            this->btnPrevFrame->setEnabled(true);
            this->btnNextFrame->setEnabled(true);
            this->slider->setEnabled(true);
            for (; mIter != mEnd; mIter++)
            {
                this->lstView->append(QString("<b>%1:</b> %2").arg(mIter.key()).arg(mIter.value()));
            }
        }
    } else
    {
        QMessageBox::information(0, "QAsfViewer - Information", "You must choose an ASF-file!");
        slider->setValue(0);
    }
}

void window::play()
{
    this->btnPlay->setDisabled(true);
    float playSpeed = this->asf->getHeader("SECONDS_PER_FRAME").toFloat();
    timer->start((int)1000*playSpeed);
}

void window::nextFrame()
{
    int tmp = this->slider->value();
    qDebug()<<tmp<<" ";
    this->slider->setValue(this->slider->value()+1);
    if(tmp == this->slider->value())
    {
        timer->stop();
        btnPlay->setEnabled(true);
        slider->setValue(0);

    }
}

void window::prevFrame()
{
    this->slider->setValue(this->slider->value()-1);
}

void window::stop()
{
    timer->stop();
    slider->setValue(0);
    lblAboveSlider->setText("<b>Position:</b>");
    btnPlay->setDisabled(false);
}

void window::setScale(bool x)
{
    if (x) view->scale(scaleFactorX, scaleFactorY);
    else view->scale(1/scaleFactorX, 1/scaleFactorY);
}
