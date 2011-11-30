#include <QtCore>
#include <cframe.h>
#include <casf.h>


casf readFile(QString filePath);

casf readFile(QString filePath)
{
    casf asf;
    QFile f(filePath);
    if(f.open(QIODevice::ReadOnly))
    {
        QTextStream t( &f );   // use a text stream
        QString s;
        bool flag = false;
        // READING HEADER
        while (!flag) {        // until end of header
            s = t.readLine();       // line of text excluding '\n'
            int firstSpaceIndx = s.indexOf(" ");
            QString headName = s.left(firstSpaceIndx);
            QString headVal = s.right(s.length()-firstSpaceIndx-1);
            if(!(headName=="ASCII_DATA" && headVal=="@@"))
            {
                qDebug() << headName<<" "<<headVal;
                asf.includeHeader(headName, headVal);
            } else {
                // end of headers
                flag = true;
            }
        }
        s = t.readLine();// read null line
        const int rows = asf.getHeader("ROWS").toInt(); // num of rows
        const int cols = asf.getHeader("COLS").toInt(); // num of cols
        const int maxNumOfFrames = asf.getHeader("END_FRAME").toInt(); // num of frames
        //        int frameCount = 1;                             // actual num of frame

        // READING FRAMES
        for(int frameCount = 1; frameCount <= maxNumOfFrames; frameCount++){
            //            while(!t.atEnd()){
            // TODO: PROCESS FRAME HEADER
            s = t.readLine(); // frame header
            qDebug()<<"Frame "<<frameCount;
            //create empty frame
            CFrame tempFrame(rows, cols);

            for(int i=0; i<rows; i++)
            {
                // read all rows of frame
                s = t.readLine();
                QStringList tempList = s.split(",");    // get list of values
                for(int j=0; j<cols; j++)
                {  // filling i-row
                    //= asf.frames[frameCount-1];
                    tempFrame.setPoint(i, j, tempList.at(j).toInt());
                    qDebug() << "Point at ["<<i<<", "<<j<<"] = "<<tempFrame.point(i, j);
                }
            }
            //end of frame
            asf.frames.append(tempFrame);
            s = t.readLine();// read null line
            //            }
        }
        f.close();
    }

    return asf;
}
