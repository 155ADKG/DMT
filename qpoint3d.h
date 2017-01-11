#ifndef QPOINT3D_H
#define QPOINT3D_H
#include <QtGui>

class QPoint3D:public QPointF
{
private:
    float z;
public:
    QPoint3D(float x_, float y_, float z_): QPointF(x_,y_),z(z_){}
    QPoint3D(): QPointF(), z(0) {}

//  void setX(int x_){this->setX(x_);}
//  void setY(int y_){this->setY(y_);}
    void setZ(float z_){z=z_;}
    float getX(){return this->x();}
    float getY(){return this->y();}
    float getZ(){return z;}

};

#endif // QPOINT3D_H

