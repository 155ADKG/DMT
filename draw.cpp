#include "draw.h"
#include <QDebug>

Draw::Draw(QWidget *parent) :
    QWidget(parent)
{
}

void Draw::paintEvent(QPaintEvent *e)
{
    const unsigned int r = 4;
    QPainter painter(this);
    painter.begin(this);
    painter.setPen(QPen(Qt::black,1));

    // Draw points from XML file
    for(int i=0; i<points.size(); i++){
        painter.drawEllipse(points[i].x()-r/2, points[i].y()-r/2, r, r);
    }

    // Draw TIN
    for (int i=0;i<dtt.size();i++)
    {
        int x1 = dtt[i].getP1().getX();
        int y1 = dtt[i].getP1().getY();
        int x2 = dtt[i].getP2().getX();
        int y2 = dtt[i].getP2().getY();
        int x3 = dtt[i].getP3().getX();
        int y3 = dtt[i].getP3().getY();

        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
        painter.drawLine(QPoint(x1, y1), QPoint(x3, y3));
        painter.drawLine(QPoint(x3, y3), QPoint(x2, y2));
    }    

    // Draw slope
    for (int i=0;i<draw_slope.size();i++)
    {
        int x1 = dtt[i].getP1().getX();
        int y1 = dtt[i].getP1().getY();
        int x2 = dtt[i].getP2().getX();
        int y2 = dtt[i].getP2().getY();
        int x3 = dtt[i].getP3().getX();
        int y3 = dtt[i].getP3().getY();

        painter.setBrush(QColor(draw_slope[i],draw_slope[i],draw_slope[i]));

        QVector<QPoint> points;
        points.push_back(QPoint(x1,y1));
        points.push_back(QPoint(x2,y2));
        points.push_back(QPoint(x3,y3));

        QPolygon triangle(points);
        painter.drawPolygon(triangle);
    }

    // Draw expos
    for (int i=0;i<draw_expos.size();i++)
    {
        int x1 = dtt[i].getP1().getX();
        int y1 = dtt[i].getP1().getY();
        int x2 = dtt[i].getP2().getX();
        int y2 = dtt[i].getP2().getY();
        int x3 = dtt[i].getP3().getX();
        int y3 = dtt[i].getP3().getY();

        painter.setBrush(draw_expos[i]);

        QVector<QPoint> points;
        points.push_back(QPoint(x1,y1));
        points.push_back(QPoint(x2,y2));
        points.push_back(QPoint(x3,y3));

        QPolygon triangle(points);
        painter.drawPolygon(triangle);
    }

    // Draw contours
    for (int i=0;i<contours.size();i++)
    {
        int x1 = contours[i].start.getX();
        int y1 = contours[i].start.getY();
        int x2 = contours[i].end.getX();
        int y2 = contours[i].end.getY();

        painter.setPen(QPen(Qt::darkRed,1));
        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
    }

    // Draw main contours
    //if (!mainContours.empty()){
//    int zet=-1;
//    int k=0;
    std::vector<int> conmain;
    if (!mainContours.empty()){
    conmain.push_back(mainContours[0].start.getZ());
    painter.setFont(QFont("Arial",18,QFont::Bold));
    painter.setPen(QPen(Qt::darkGreen));
    painter.drawText(mainContours[0].start.getX(), mainContours[0].start.getY(), QString::number(mainContours[0].start.getZ()));
    }
    for (int i=0;i<mainContours.size();i++)
    {
        int zet = mainContours[i].start.getZ();



        int x1 = mainContours[i].start.getX();
        int y1 = mainContours[i].start.getY();
        int x2 = mainContours[i].end.getX();
        int y2 = mainContours[i].end.getY();

        painter.setPen(QPen(Qt::darkRed,3));
        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));

        std::vector<int>::iterator icon = std::find(conmain.begin(),conmain.end(),zet);
        if(icon == conmain.end())
        {
            painter.setFont(QFont("Arial",18,QFont::Bold));
            painter.setPen(QPen(Qt::darkGreen));
            painter.drawText(x1, y1, QString::number(zet));
            conmain.push_back(zet);
        }

    }
}
