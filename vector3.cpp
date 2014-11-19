/********************************************************************
         @filename:  vector3.cpp
         @author:    ChenYang
         @date:      2014/11/18   19:59
         @brief:     
 ********************************************************************/

#include <math.h>
#include "vector3.h"
#include "point3.h"

Vector3::Vector3(): x(0.0), y(0.0), z(0.0)
{

}

Vector3::Vector3(double _x, double _y, double _z): x(_x), y(_y), z(_z)
{

}

Vector3::Vector3(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3::Vector3(const Point3& p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

Vector3::Vector3(const Point3& f, const Point3& l)
{
    x = l.x - f.x; y = l.y - f.y; z = l.z - l.z;
}


Vector3::~Vector3()
{

}

void Vector3::normalize()
{
    double len = sqrt(x*x+y*y+z*z);
    x /= len;
    y /= len;
    z /= len;
}

double Vector3::length() const
{
    return sqrt(x*x + y*y + z*z);
}

double Vector3::lenSquared() const
{
    return (x*x+ y*y + z*z);
}

Vector3 operator*(const Matrix& mat, const Vector3& v)
{
    return (Point3(mat.m[0][0]*v.x + mat.m[0][1]*v.y + mat.m[0][2]*v.z,
        mat.m[1][0]*v.x + mat.m[1][1]*v.y + mat.m[1][2]*v.z,
        mat.m[2][0]*v.x + mat.m[2][1]*v.y + mat.m[2][2]*v.z));
}

Vector3 Vector3::operator^ (const Vector3 &rhs) const
{
    return (Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x));
}

