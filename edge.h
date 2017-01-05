#ifndef EDGE_H
#define EDGE_H
#include <QtGui>
#include "qpoint3d.h"


class Edge
{
private:


public:

    QPoint3D start;
    QPoint3D end;


    Edge(const QPoint3D &s, const QPoint3D &e): start(s), end(e)
    {
        start = s;
        end = e;
    }

    void switchOrientation();

    bool operator == (const Edge &e)
    {
//        if (e.start==e.start && e.end == e.end)
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }

        double eps = 1e-06;

        //Get coordinates differences between start points
        const double dxs = start.x() - e.start.x();
        const double dys = start.y() - e.start.y();

        //Get coordinates differences between end points
        const double dxe = end.x() - e.end.x();
        const double dye = end.y() - e.end.y();

        //Compute distance between start and end points
        const double ds = sqrt(dxs*dxs + dys*dys);
        const double de = sqrt(dxe*dxe + dye*dye);

        if (ds < eps && de < eps)
            return true;
        else
            return false;
    }
};

#endif // EDGE_H
