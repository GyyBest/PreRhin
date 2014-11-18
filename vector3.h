/********************************************************************
         @filename:  vector3.h
         @author:    ChenYang
         @date:      2014/11/18   19:51
         @brief:     
 ********************************************************************/
#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3 {
public:
    Vector3();
    Vector3(double x, double y, double z);
    Vector3(const Vector3& v);
    ~Vector3();

    void normalize();
    
    Vector3& operator= (const Vector3 v);
    Vector3 operator+ (const Vector3& rhs)const;
    Vector3 operator- (const Vector3& rhs)const;

public:
    double x, y, z;
};

inline Vector3& Vector3::operator= (const Vector3 v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

inline Vector3 Vector3::operator +(const Vector3& rhs) const
{
    return Vector3(x+rhs.x,y+rhs.y,z+rhs.z);
}

inline Vector3 Vector3::operator -(const Vector3& rhs) const
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}
#endif // __VECTOR3_H__
