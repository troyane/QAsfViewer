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


    QSlider *slider;
    // ------ graphics objects
    QGraphicsView *view;
    QGraphicsScene *scene;
    casf *asf;
    int actualFrame;

signals:

public slots:
    void showFrame(int numFrame);
    void openFile();

private:
    QPushButton *btnOpen;
    QPushButton *button2;
    // ------ graphics objects

    QLabel *lblAboveView;
    QLabel *lblAboveSlider;

    QPushButton *btnPlay;
    QPushButton *btnPause;
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
};

#endif // WINDOW_H
