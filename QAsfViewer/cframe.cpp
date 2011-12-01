#include "cframe.h"
#include <vector>
#include <QtCore>
#include <QImage>


QString CFrame::getHeader(QString name)
{// returns value of header else ""
    return headers.value(name, "");
}

void CFrame::includeHeader(QString name, QString val)
{
    headers.insert(name, val);
}

int CFrame::point(int x, int y)
{
    return (int) data[convert(x, y)];
}

int CFrame::setPoint(const int x, const int y, const int val)
{    
    data[convert(x, y)] = val;
    return 0;
}

CFrame::CFrame(const int numRows, const int numCols)
{
    qDebug("CFrame created");
    nRows = numRows;
    nCols = numCols;

    data = (unsigned int*) malloc (sizeof(int) * nCols * nRows);

    qDebug()<<"Size = "<<sizeof(int) * nCols * nRows;
    qDebug()<<"numR = "<<numRows;
    qDebug()<<"numC = "<<numCols;
}

CFrame::~CFrame()
{
    if (data) free(data);
}


QImage* CFrame::createImage()
{
    QImage *img = new QImage(nRows, nCols, QImage::Format_RGB32);
    QRgb val;    
    for(int i=0; i<nRows; i++)
    {
        for(int j=0; j<nCols; j++)
        {
            int t = data[convert(i, j)];
            val = qRgb(t, t, t);
            img->setPixel(i, j, val);
        }
    }
    return img;
}

int CFrame::convert(int x, int y)
{
//    qDebug()<<"x="<<x<<" y="<<y<<" f="<<y + x*nCols;
    return (x + y*nRows);
}

void CFrame::fill()
{
    for(int i=0; i<nRows*nCols; i++)
    {
        data[i] = i;
    }
}


