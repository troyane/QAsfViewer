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

private:
    QMap <QString, QString> headers;

};

#endif // CASF_H
