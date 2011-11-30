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

    int setPoint(const int x, const int y, const int val);
    int point(int x, int y) const;

    QImage* frameToImage(const int numRows, const int numCols);
private:
    QMap <QString, QString> headers;
    int **data;
};

#endif // CFRAME_H
