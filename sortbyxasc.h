#ifndef SORTBYXASC_H
#define SORTBYXASC_H
#include <QtGui>

class sortByXAsc
{
public:
    sortByXAsc();

    bool operator() (const QPoint p1, const QPoint p2)
    {
        return p1.x() < p2.x();
    }
};

#endif // SORTBYXASC_H
