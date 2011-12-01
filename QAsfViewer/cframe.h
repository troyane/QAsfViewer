#ifndef CFRAME_H
#define CFRAME_H

#include <QtCore>
#include <vector>
#include <QImage>

class CFrame {
public:
    CFrame(const int rows, const int cols);
    ~CFrame();
    QString getHeader(QString name);
    void includeHeader(QString name, QString val);

    int convert(int x, int y);
    int setPoint(const int x, const int y, const int val);
    int point(int x, int y);

    void fill();

    QImage* createImage();
private:
    QMap <QString, QString> headers;

    unsigned int *data;
    int nRows, nCols;
};

#endif // CFRAME_H
