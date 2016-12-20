#include "algorithms.h"

Algorithms::Algorithms()
{
}

double Algorithms::getCircleRadius(QPoint &p1, QPoint &p2, QPoint &p3)
{
    const double x1 = p1.x();
    const double x2 = p2.x();
    const double x3 = p3.x();
    const double y1 = p1.y();
    const double y2 = p2.y();
    const double y3 = p3.y();

    const double k1 = x1*x1 + y1*y1;
    const double k2 = x2*x2 + y2*y2;
    const double k3 = x3*x3 + y3*y3;
    const double k4 = y1 - y2;
    const double k5 = y1 - y3;
    const double k6 = y2 - y3;
    const double k7 = x1 - x2;
    const double k8 = x1 - x3;
    const double k9 = x2 - x3;
    const double k10 = x1*x1;
    const double k11 = x2*x2;
    const double k12 = x3*x3;

    const double m = 0.5*((k12*(-k4)+k11*k5-(k10+k4*k5)*k6)/(x3*(-k4)+x2*k5+x1*(-k6)));
    const double n = 0.5*((k1*(-k9)+k2*k8+k3*(-k7))/(y1*(-k9)+y2*k8+y3*(-k7)));
    const double r = sqrt((x1-m)*(x1-m)+(y1-n)*(y1-n));

    return r;
}

int Algorithms::getDelauyPoint(Edge &e, std::vector<QPoint> points)
{
    double r_max = 0;
    int i_max = -1;

    for (int i=0;i<points.size();i++)
    {
        if (getPointLinePosition(points[i],e.start,e.end)==1)
        {
            double r = getCircleRadius(points[i],e.start,e.end);
            if (r>r_max)
            {
                r_max = r;
                i_max = i;
            }
        }
    }
}

std::vector<Edge> Algorithms::createDT(std::vector<QPoint> &points)
{

    //Sort points by x
    std::list<Edge> ael;
    std::sort(points.begin(),points.end(),sortByXAsc());

    //Pivot and its nearest point
    QPoint q = points[0];
    int ind = getNearestPoint(q,points);
    QPoint p = points[ind];

    Edge e(q,p);

    //Find nearest Delaunay point to (q,p), switch orientation if not
    int d_ind = getDelauyPoint(e,points);
    if (d_ind == -1)
    {
        e.switchOrientation();
        d_ind = getDelauyPoint(e,points);
        QPoint temp=q;
        q=p;
        p=temp;
    }

    //Create Delaunay triangle
    Edge e2(p,points[d_ind]);
    Edge e3(points[d_ind],q);
    std::vector<Edge> dt;
    dt.push_back(e);
    dt.push_back(e2);
    dt.push_back(e3);

    //Add edges to AEL
    ael.push_back(e);
    ael.push_back(e2);
    ael.push_back(e3);

    //Proces ael until is empty
    while(!ael.empty())
    {

        //Remove the first edge
        Edge e = ael.pop_front();

        //Switch orientation
        e.switchOrientation();

        //Find nearest point
        d_ind = getDelauyPoint(e,points);

        if (d_ind !=-1)
        {
            //Create new edges
            Edge e4(e.end,points[d_ind]);
            Edge e5(points[d_ind],e.start);

            //Add points to edge
            dt.push_back(e);
            dt.push_back(e4);
            dt.push_back(e5);

            //Swiutch orientation
            e4.switchOrientation();
            e5.switchOrientation();

            //Find edge in AEL
            std::list<Edge>::iterator ie4 = std::find(ael.begin(),ael.end(),e4);
            std::list<Edge>::iterator ie5 = std::find(ael.begin(),ael.end(),e5);

            //There is no edge opposite orientation
            if (ie4 == ael.end())
            {
                e4.switchOrientation();
                ael.push_back(e4);
            }

            if (ie5 == ael.end())
            {
                e5.switchOrientation();
                ael.push_back(e5);
            }
        }
    }

}

std::vector<Edge> Algorithms::createContours(const std::vector<Edge> &dt, const double z_min, const double z_max, const double dz)
{
    double eps = 1e-03;

    std::vector<Edge> contours;

    //Process a triplet of edges
    for (i=0;i<dt.size()-2;i+=3)
    {

        //Get triangle of vertices
        QPoint p1 = dt[i].start;
        QPoint p2 = dt[i].end;
        QPoint p3 = dt[i+1].end;

        for (double z = z_min;z<=z_max;z+=dz)
        {
            double dz1 = z - p1.z();
            double dz2 = z - p2.z();
            double dz3 = z - p3.z();

            bool b12 = (abs(dz1) < eps) && (abs(dz2) < eps);
            bool b23 = (abs(dz2) < eps) && (abs(dz3) < eps);
            bool b31 = (abs(dz3) < eps) && (abs(dz1) < eps);

            //Case 1: Triangle coplanar with the horizontal plane
            if (b12 && b23 && b31)
                continue;

            //Case 2: Edge of the triangle is in the horizontal plane
            if (b12 || b23 || b31)
            {
                if (b12)
                    contours.push_back(dt[i]);
                if (b23)
                    contours.push_back(dt[i+1]);
                if (b31)
                    contours.push_back(dt[i+2]);
            }
        }
    }
}

QPoint Algorithms::contourPoint(const QPoint &p1, const QPoint &p2, double z)
{
    double xa = (((p2.x() - p1.x())/(p2.z() - p1.z()))*(z - p1.z()))+p1.x();
    double ya = (((p2.y() - p1.y())/(p2.z() - p1.z()))*(z - p1.z()))+p1.y();

    QPoint p(xa,ya);
    return p;
}

int Algorithms::getNearestPoint(const QPoint &p, std::vector<QPoint> points)
{
    int i_min = -1;
    double d_min = 9e10;
    for (int i=0;i<points.size();i++)
    {
        if (p != points[i])
        {
            double dx = points[i].x() - p.x();
            double dy = points[i].y() - p.y();
            double d = sqrt(dx*dx + dy*dy);

            if (d<d_min)
            {
                d_min = d;
                i_min = i;
            }
        }
    }
    return i_min;
}

int Algorithms::getPointLinePosition(const QPointF &p, const QPointF &p1, const QPointF &p2)
{
    //Vector u = p2-p1 and v = p2-p
    const double ux = p2.x() - p1.x();
    const double uy = p2.y() - p1.y();
    const double vx = p.x() - p1.x();
    const double vy = p.y() - p1.y();

    //Test criterion
    const double t = ux*vy - vx*uy;

    //P is in the left halfplpane
    if (t<0)
        return 1;

    //P is in the right halfplpane
    if (t>0)
        return 0;

    //P is on the edge
    return -1;
}