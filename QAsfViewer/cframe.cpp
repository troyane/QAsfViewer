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

int CFrame::point(int x, int y) const
{
    return data[x][y];
}

int CFrame::setPoint(const int x, const int y, const int val)
{    
    if((data[x][y] = val))
    {
        return 0;
    }
    else { return 1;}
}

CFrame::CFrame(const int numRows, const int numCols)
{
    data = new int*[numRows];

    for (int row = 0; row < numRows; row++)
    {
           data[row] = new int[numCols];
    }
}

CFrame::~CFrame(){}


QImage* CFrame::createImage(const int numRows, const int numCols)
{
    QImage *img = new QImage(numRows, numCols, QImage::Format_RGB32);
    QRgb val;    
    for(int i=0; i<numRows; i++)
    {
        for(int j=0; j<numCols; j++)
        {
            int t = data[i][j];
            val = qRgb(t, t, t);
            img->setPixel(i, j, val);
        }
    }
    return img;
}


