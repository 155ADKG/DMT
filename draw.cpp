#include "draw.h"

Draw::Draw(QWidget *parent) :
    QWidget(parent)
{
}

void Draw::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin();

    painter.draw;
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

    for (int i=0;i<dtt.size();i++)
    {

        int x1 = dtt[i].getP1().getX();
        int y1 = dtt[i].getP1().getY();
        int x2 = dtt[i].getP2().getX();
        int y2 = dtt[i].getP2().getY();
        int x3 = dtt[i].getP3().getX();
        int y3 = dtt[i].getP3().getY();


        double gray = abs(dtt[i].getSlope() / 180);

        QPen pen;
        pen.setBrush(QColor(gray,gray,gray));

        painter.setPen(pen);

        QVector points;
        points.push_back(QPoint(x1,y1));
        points.push_back(QPoint(x2,y2));
        points.push_back(QPoint(x3,y3));

        QPolygon triangle(points);
        painter.drawPolygon(triangle);

    }
}
