#include "triangle.h"

void Triangle::analyzeSlope()
{
    double ux = p2.getX() - p1.getX();
    double uy = p2.getY() - p1.getY();
    double uz = p2.getZ() - p1.getZ();

    double vx = p3.getX() - p1.getX();
    double vy = p3.getY() - p1.getY();
    double vz = p3.getZ() - p1.getZ();

    double nx = uy*vz - vy*uz;
    double ny = uz*vx - vz*ux;
    double nz = ux*vy - vx*uy;

    slope = acos(nz/(sqrt(nx*nx+ny*ny+nz*nz))) * (180/3.1415);
}

void Triangle::analyzeExposition()
{
    double ux = p2.getX() - p1.getX();
    double uy = p2.getY() - p1.getY();
    double uz = p2.getZ() - p1.getZ();

    double vx = p3.getX() - p1.getX();
    double vy = p3.getY() - p1.getY();
    double vz = p3.getZ() - p1.getZ();

    double nx = uy*vz - vy*uz;
    double ny = uz*vx - vz*ux;


    exposition = atan2(ny,nx) * (180/3.1415);

}
