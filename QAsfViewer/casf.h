#ifndef CASF_H
#define CASF_H

#include <QtCore>
#include <vector>
#include <cframe.h>

class casf
{
public:

    casf();
    ~casf();
    QString getHeader(QString name);
    void includeHeader(QString name, QString val);
    QList <CFrame> frames;
    int readFile(QString filePath);
    QMap <QString, QString> headers;

private:
};

#endif // CASF_H
