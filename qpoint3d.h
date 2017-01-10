#ifndef QPOINT3D_H
#define QPOINT3D_H
#include <QtGui>

class QPoint3D:public QPoint
{
private:
    int z;
public:
    QPoint3D(int x_, int y_, int z_): QPoint(x_,y_),z(z_){}
    QPoint3D(): QPoint(), z(0) {}

//  void setX(int x_){this->setX(x_);}
//  void setY(int y_){this->setY(y_);}
    void setZ(int z_){z=z_;}
    int getX(){return this->x();}
    int getY(){return this->y();}
    int getZ(){return z;}

};

#endif // QPOINT3D_H

