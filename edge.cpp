#include "edge.h"

Edge::Edge(const QPoint &s, const QPoint &e)
{
    start = s;
    end = e;
}

void Edge::switchOrientation()
{
   QPoint p = start;
   start = end;
   end = p;
}
