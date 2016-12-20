#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QtGui>
#include "edge.h"
#include "sortbyxasc.h"

class Algorithms
{
public:
    Algorithms();

    static double getCircleRadius(QPoint &p1, QPoint &p2, QPoint &p3);

    static int getDelauyPoint(Edge &e, std::vector<QPoint> points);

    static int getPointLinePosition(const QPointF &p, const QPointF &p1, const QPointF &p2);

    static int getNearestPoint(const QPoint &p, std::vector<QPoint> points);

    static std::vector<Edge> createDT(std::vector<QPoint> &points);

    static std::vector<Edge> createContours(const std::vector<Edge> &dt, const double z_min, const double z_max, const double dz);

    static QPoint contourPoint(const QPoint &p1, const QPoint &p2, double z);
};

#endif // ALGORITHMS_H
