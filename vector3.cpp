/********************************************************************
         @filename:  vector3.cpp
         @author:    ChenYang
         @date:      2014/11/18   19:59
         @brief:     
 ********************************************************************/

#include <math.h>
#include "vector3.h"

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