#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QtGui>
#include "edge.h"
#include "sortbyxasc.h"
#include "triangle.h"
#include "qpoint3d.h"

class Algorithms
{
public:
    Algorithms();

    static double getCircleRadius(QPoint3D &p1, QPoint3D &p2, QPoint3D &p3);

    static int getDelauyPoint(Edge &e, std::vector<QPoint3D> points);

    static int getPointLinePosition(const QPoint3D &p, const QPoint3D &p1, const QPoint3D &p2);

    static int getNearestPoint(const QPoint3D &p, std::vector<QPoint3D> points);

    static std::vector<Edge> createDT(std::vector<QPoint3D> &points);

    static std::vector<Edge> createContours(const std::vector<Edge> &dt, const double z_min, const double z_max, const double dz);

    static QPoint3D contourPoint(QPoint3D &p1, QPoint3D &p2, double z);

    static std::vector<Triangle> convertDT(std::vector<Edge> &dt);


};

#endif // ALGORITHMS_H
