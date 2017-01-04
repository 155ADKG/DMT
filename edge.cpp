#include "edge.h"

Edge::Edge(const QPoint3D &s, const QPoint3D &e)
{
    start = s;
    end = e;
}

void Edge::switchOrientation()
{
   QPoint3D p = start;
   start = end;
   end = p;
}
