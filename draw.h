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
    std::vector<Edge> mainContours;
    std::vector<Triangle> dtt;
    std::vector<QPoint3D> points;
    std::vector<double> draw_slope;
    std::vector<QColor> draw_expos;

public:
    explicit Draw(QWidget *parent = 0);

    void setContours(const std::vector<Edge> &contours_){contours = contours_;}
    void setMainContours(const std::vector<Edge> &main_contours_){ mainContours = main_contours_; }
    void setTriangle(const std::vector<Triangle> &dtt_){dtt = dtt_;}
    void setLoadPoints(std::vector<QPoint3D> points_){ points = points_; }
    void setDrawSlope(std::vector<double> draw_slope_){ draw_slope = draw_slope_; }
    void setDrawExpos(std::vector<QColor> draw_expos_){ draw_expos = draw_expos_; }

    void paintEvent(QPaintEvent *e);
signals:

public slots:

};

#endif // DRAW_H
