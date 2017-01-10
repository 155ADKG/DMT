#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "qpoint3d.h"

class Triangle
{
private:

    QPoint3D p1;
    QPoint3D p2;
    QPoint3D p3;

    double slope;
    double exposition;

public:
    Triangle(const QPoint3D &p1_,const QPoint3D &p2_,const QPoint3D &p3_, const double slope_, const double exposition_):p1(p1_),p2(p2_),p3(p3_)
    {
        p1 = p1_;
        p2 = p2_;
        p3 = p3_;
        analyzeSlope();
        analyzeExposition();
        //slope = slope_;
        //exposition = exposition_;

    }

    QPoint3D getP1(){return p1;}

    QPoint3D getP2(){return p2;}

    QPoint3D getP3(){return p3;}

    double getSlope(){return slope;}

    double getExposition(){return exposition;}

    void setP1(QPoint3D p1_){p1 = p1_;}

    void setP2(QPoint3D p2_){p2 = p2_;}

    void setP3(QPoint3D p3_){p3 = p3_;}

    void setSlope(double slope_){slope = slope_;}

    void setExposition(double exposition_){exposition = exposition_;}

    void analyzeSlope();

    void analyzeExposition();
};

#endif // TRIANGLE_H
