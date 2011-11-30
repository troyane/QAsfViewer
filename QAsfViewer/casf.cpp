#include "casf.h"
#include <map>

casf::casf()
{
}

casf::~casf()
{
    headers.clear();
    frames.clear();
}

void casf::includeHeader(QString name, QString val)
{
    headers.insert(name, val);
}

QString casf::getHeader(QString name)
{
    return (QString) headers.value(name);
}
