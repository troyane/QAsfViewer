#include "casf.h"
#include <map>

casf::casf()
{
}

casf::~casf()
{
    if (!frames.isEmpty())
    for (int i = 0; i < frames.size(); i++)
    {
        delete frames[i];
    }
}

void casf::includeHeader(QString name, QString val)
{
    headers.insert(name, val);
}

QString casf::getHeader(QString name)
{
    return (QString) headers.value(name);
}

int casf::readFile(QString filePath)
{
    QFile f(filePath);
    if(f.open(QIODevice::ReadOnly))
    {
        bool firstString = true;
        QTextStream t( &f );   // use a text stream
        QString s;
        bool flag = false;
        // READING HEADER
        while (!flag)
        {        // until end of header
            s = t.readLine();       // line of text excluding '\n'

            int firstSpaceIndx = s.indexOf(" ");

            QString headName = s.left(firstSpaceIndx);
            QString headVal = s.right(s.length()-firstSpaceIndx-1);

            if(firstString)
            {   // Check if file is ASF-MOVIE
                if(headName=="DATA_TYPE" && headVal=="MOVIE")
                {
                    firstString = false;
                }
                else
                {
                    return 1;
                }
            }

            if(!(headName=="ASCII_DATA" && headVal=="@@"))
            {
//                qDebug() << headName<<" "<<headVal;
                this->includeHeader(headName, headVal);
            } else {
                // end of headers
                flag = true;
            }
        }
        s = t.readLine();// read null line

        const int rows = this->getHeader("ROWS").toInt(); // num of rows
        const int cols = this->getHeader("COLS").toInt(); // num of cols

        const int maxNumOfFrames = this->getHeader("END_FRAME").toInt(); // num of frames

        // READING FRAMES
        for(int frameCount = 1; frameCount <= maxNumOfFrames; frameCount++)
        {
            // TODO: PROCESS FRAME HEADER
            s = t.readLine(); // frame header
//            qDebug()<<"Frame "<<frameCount;
            //create empty frame
            CFrame *tempFrame = new CFrame(rows, cols);

            for(int i=0; i<rows; i++)
            {
                // read all rows of frame
                s = t.readLine();

                QStringList tempList = s.split(",");    // get list of values

                for(int j=0; j<cols; j++)
                {  // filling i-row
                    tempFrame->setPoint(i, j, tempList.at(j).toInt());
                }
            }
            //end of frame
            this->frames.append(tempFrame);
            s = t.readLine();// read null line
            //            }
        }
        f.close();
    }
    return 0;
}
