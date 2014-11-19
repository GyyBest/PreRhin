/********************************************************************
         @filename:  matrix.h
         @author:    ChenYang
         @date:      2014/11/19   18:29
         @brief:     
 ********************************************************************/

#ifndef __MATRIX_H__
#define __MATRIX_H__

class Matrix {
public:
    Matrix();
    Matrix(const Matrix& mat);
    ~Matrix();

    Matrix& operator= (const Matrix& rhs);
    Matrix operator* (const Matrix& mat) const;
    Matrix operator/ (const double d);
    
    void setIdentity();

public:
    double m[4][4];
};

#endif // __MATRIX_H__
