#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include "edge.h"
#include "triangle.h"
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector<Edge> contours;
    std::vector<Triangle> dtt;

public:
    explicit Draw(QWidget *parent = 0);

    void setContours(const std::vector<Edge> &contours_){contours = contours_;}
    void setTriangle(const std::vector<Triangle> &dtt_){dtt = dtt_;}

    void paintEvent(QPaintEvent *e);
signals:

public slots:

};

#endif // DRAW_H
