#ifndef SORTBYXASC_H
#define SORTBYXASC_H
#include <QtGui>
#include "qpoint3d.h"

class sortByXAsc
{
public:
    sortByXAsc();

    bool operator() (const QPoint3D p1, const QPoint3D p2)
    {
        return p1.x() < p2.x();
    }
};

#endif // SORTBYXASC_H
