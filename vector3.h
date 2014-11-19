/********************************************************************
         @filename:  vector3.h
         @author:    ChenYang
         @date:      2014/11/18   19:51
         @brief:     
 ********************************************************************/
#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Matrix;
class Point3;

class Vector3 {
public:
    Vector3();
    Vector3(double _x, double _y, double _z);
    Vector3(const Vector3& v);
    Vector3(const Point3& p);
    Vector3(const Point3& f, const Point3& l);
    ~Vector3();

    void normalize();
    
    Vector3 operator-() const;
    Vector3& operator= (const Vector3 v);
    Vector3 operator+ (const Vector3& rhs) const;
    Vector3 operator- (const Vector3& rhs) const;
    Vector3 operator/ (const double& a) const;
    // dot product
    double operator* (const Vector3& b) const;
    // cross product
    Vector3 operator^ (const Vector3& rhs) const;
    
    double length() const;
    double lenSquared() const;

public:
    double x, y, z;
};

inline Vector3 Vector3::operator-()const
{
    return Vector3(-x, -y, -z);
}

inline Vector3& Vector3::operator= (const Vector3 v)
{
    x = v.x; y = v.y; z = v.z;
    return *this;
}

inline Vector3 Vector3::operator+ (const Vector3& rhs) const
{
    return Vector3(x+rhs.x,y+rhs.y,z+rhs.z);
}

inline Vector3 Vector3::operator- (const Vector3& rhs) const
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline Vector3 Vector3::operator/ (const double& a)const
{
    return Vector3(x/a, y/a, z/a);
}

inline double Vector3::operator* (const Vector3& b) const 
{
    return (x * b.x + y * b.y + z * b.z);
}

// non-member function
Vector3 operator*(const double a,const Vector3& v); 

inline Vector3 operator*(const double a,const Vector3& v)
{
    return Vector3(a*v.x,a*v.y,a*v.z);
}

Vector3 operator* (const Matrix& mat, const Vector3& v);

#endif // __VECTOR3_H__
