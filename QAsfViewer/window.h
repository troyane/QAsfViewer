#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QtGui>
#include <casf.h>
#include <cframe.h>


class window : public QWidget
{
    Q_OBJECT
public:
    explicit window(QWidget *parent = 0);
    ~window();

    QSlider *slider;
    // ------ graphics objects
    QGraphicsView *view;
    QGraphicsScene *scene;
    casf *asf;
    int actualFrame;
    bool isScaled;
    qreal scaleFactorX;
    qreal scaleFactorY;

//    view->scale(scaleFactorX, scaleFactorY);
//    qreal scaleFactorX = view->width() / rows - 0.5;
//    qreal scaleFactorY = view->height() / cols - 0.5;


signals:

public slots:
    void showFrame(int numFrame);
    void openFile();
    void play();
    void nextFrame();
    void prevFrame();
    void stop();
    void setScale(bool x);

private:
    QPushButton *btnOpen;
    // ------ graphics objects
    QLabel *lblAboveView;
    QLabel *lblAboveSlider;
    QCheckBox *chkScale;
    QPushButton *btnPlay;
    QPushButton *btnStop;
    QPushButton *btnNextFrame;
    QPushButton *btnPrevFrame;
    QTextEdit *lstView;
    QLabel *lblAboveList;
    QLabel *lblAboveBtns;
    // ------ Control buttons
    QHBoxLayout *controlsLayout;
    // ------ Left side
    QVBoxLayout *leftVLayout;
    // ------ Right side
    QVBoxLayout *rightVLayout;
    // ------ Main layout
    QHBoxLayout *mainHLayout;

    QTimer *timer;
};

#endif // WINDOW_H
